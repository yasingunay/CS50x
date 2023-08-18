import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd, validate_password

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session.get("user_id")

    # Fetch portfolio data (symbol, name, total_shares) for the logged-in user from the database
    rows = db.execute(
        "SELECT symbol, name, total_shares FROM portfolio WHERE user_id = ?", user_id
    )

    # Fetch user's cash amount from the database
    cash_row = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = cash_row[0]["cash"]

    # Initialize variables for total value calculation
    sum = 0  # Sum of individual stock values
    TOTAL = 0  # Total portfolio value including cash

    # Iterate through each stock in the portfolio
    for row in rows:
        # Get stock information using lookup function
        look = lookup(row["symbol"])

        # Update stock details with data from lookup
        row["symbol"] = look["symbol"]
        row["name"] = look["name"]
        row["price"] = look["price"]

        # Calculate total value of each stock (price * total_shares)
        row["total"] = row["price"] * row["total_shares"]

        # Accumulate the total value of all stocks
        sum += row["total"]

    # Calculate the total portfolio value (cash + sum of individual stock values)
    TOTAL = cash + sum

    # Render the index template with portfolio data and calculated values
    return render_template("index.html", rows=rows, cash=cash, TOTAL=TOTAL)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        # Get symbol and shares from the form
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if symbol == "":
            return apology("MISSING SYMBOL")
        elif shares.isdigit() == False:
            return apology("INVALID NUMBER OF SHARES")
        else:
            # Get stock information using lookup function
            look = lookup(symbol)
            if look == None:
                return apology("INVALID SYMBOL")
            else:
                # Extract stock details
                symbol = look["symbol"]
                name = look["name"]
                price = look["price"]

                # Get user ID and available cash from session
                user_id = session.get("user_id")
                cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

                total_amount = float(shares) * price

                # Check if user can afford the purchase
                if float(cash[0]["cash"]) >= total_amount:
                    new_cash = float(cash[0]["cash"]) - total_amount

                    # Insert transaction record
                    db.execute(
                        "INSERT INTO transactions(user_id, symbol,name,type,shares,price,transaction_date) VALUES (?,?,?,?,?,?,?)",
                        user_id,
                        symbol,
                        name,
                        "buy",
                        shares,
                        price,
                        datetime.now(),
                    )

                    # Check if the stock is already in the portfolio
                    row = db.execute(
                        "SELECT symbol FROM portfolio WHERE user_id = ? AND symbol = ?",
                        user_id,
                        symbol,
                    )

                    # Update or insert portfolio record
                    if len(row) != 1:
                        db.execute(
                            "INSERT INTO portfolio(user_id, symbol,name, total_shares) VALUES (?,?,?,?)",
                            user_id,
                            symbol,
                            name,
                            shares,
                        )
                    else:
                        row = db.execute(
                            "SELECT total_shares FROM portfolio WHERE user_id = ? AND symbol = ?",
                            user_id,
                            symbol,
                        )
                        old_shares = row[0]["total_shares"]
                        new_shares = old_shares + int(shares)
                        db.execute(
                            "UPDATE portfolio SET total_shares = ? WHERE user_id = ? AND symbol = ?",
                            new_shares,
                            user_id,
                            symbol,
                        )

                    # Update user's cash
                    db.execute(
                        "UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id
                    )

                    # Flash success message and redirect to homepage
                    flash("Bought!", "success")
                    return redirect("/")
                else:
                    # If user can't afford, display an apology
                    return apology("CAN'T AFFORD")


@app.route("/history", methods=["GET"])
@login_required
def history():
    """Show history of transactions"""
    user_id = session.get("user_id")

    # Fetch transaction history data from the database for the logged-in user
    stocks = db.execute(
        "SELECT symbol,shares,price,transaction_date FROM transactions WHERE user_id = ?",
        user_id,
    )

    # Render the history template with the transaction data
    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        # Display the quote form for GET requests
        return render_template("quote.html")
    else:
        # Handle stock quote retrieval for POST requests

        # Get symbol from the form
        symbol = request.form.get("symbol")

        # Check for missing symbol
        if symbol == "":
            return apology("MISSING SYMBOL")
        else:
            # Look up the stock quote using the lookup function
            quote = lookup(symbol)

            # Check if the symbol is invalid
            if quote == None:
                return apology("INVALID SYMBOL")
            else:
                # Display the stock quote using a template
                return render_template(
                    "quoted.html",
                    name=quote["name"],
                    symbol=quote["symbol"],
                    price=usd(quote["price"]),
                )


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Display registration form
    if request.method == "GET":
        return render_template("register.html")
    else:
        # Access form data
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Check for errors
        existing_user = db.execute(
            "SELECT username FROM users WHERE username = ?", username
        )

        # Validate user registration data
        if username == "" or existing_user:
            return apology("Username is not available")
        elif password == "":
            return apology("MISSING PASSWORD")
        elif validate_password(password) == False:
            return apology("PASSWORD IS NOT VALID")
        elif confirmation == "" or (password != confirmation):
            return apology("PASSWORDS DON'T MATCH")

        # Generate a hasf of the password
        password_hash = generate_password_hash(
            password, method="pbkdf2", salt_length=16
        )

        # Add user to database
        result = db.execute(
            "INSERT INTO users(username, hash) VALUES (?, ?)", username, password_hash
        )

        if result:
            # Log the user in
            user_data = db.execute("SELECT id FROM users WHERE username = ?", username)
            if user_data:
                user_id = user_data[0]["id"]
                session["user_id"] = user_id

                # Redirect to the index page
                return redirect("/")

        # If registration fails for some reason, return an apology
        return apology("Registration failed")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session.get("user_id")

    # Get the list of symbols from the user's portfolio
    quotes = db.execute("SELECT symbol FROM portfolio WHERE user_id = ? ", user_id)
    if request.method == "GET":
        # Display the sell form for GET requests, passing available symbols to template
        return render_template("sell.html", quotes=quotes)
    else:
        # Handle selling process for POST requests

        # Get symbol, shares to sell, and stock details from the form
        symbol = request.form.get("symbol")
        look = lookup(symbol)
        price = look["price"]
        name = look["name"]
        shares_sell = request.form.get("shares")

        # Check for invalid number of shares (non-numeric input)
        if shares_sell.isdigit() == False:
            return apology("INVALID NUMBER OF SHARES")

        # Get current total shares of the selected symbol from the user's portfolio
        rows = db.execute(
            "SELECT total_shares FROM portfolio WHERE user_id = ? and symbol = ?",
            user_id,
            symbol,
        )
        total_shares = rows[0]["total_shares"]

        # Check if the user is trying to sell more shares than they own
        if int(shares_sell) > total_shares:
            return apology("TOO MANY SHARES")
        else:
            # Calculate new shares after the sale
            new_shares = total_shares - int(shares_sell)

            # If remaining shares are zero, delete the symbol from the user's portfolio
            if new_shares == 0:
                db.execute(
                    "DELETE FROM portfolio WHERE user_id =? AND symbol =?",
                    user_id,
                    symbol,
                )

            # Update the user's portfolio with new share count
            db.execute(
                "UPDATE portfolio SET total_shares = ? WHERE user_id = ? and symbol = ?",
                new_shares,
                user_id,
                symbol,
            )

            # Update user's cash after the sale
            cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
            new_cash = float(cash[0]["cash"]) - int(shares_sell) * price
            db.execute(
                "UPDATE portfolio SET total_shares = ? WHERE user_id = ? and symbol = ?",
                new_shares,
                user_id,
                symbol,
            )

            # Insert a transaction record for the sale
            db.execute(
                "INSERT INTO transactions(user_id, symbol,name,type,shares,price,transaction_date) VALUES (?,?,?,?,?,?,?)",
                user_id,
                symbol,
                name,
                "sell",
                -int(shares_sell),
                price,
                datetime.now(),
            )

            # Flash success message and redirect to homepage
            flash("Sold!", "success")
            return redirect("/")
