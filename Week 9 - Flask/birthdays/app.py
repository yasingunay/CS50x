import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

MONTHS=[]
for month in range(1,13):
    MONTHS.append(month)

DAYS = []
for day in range(1, 32):
    DAYS.append(day)


# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # TODO: Add the user's entry into the database
        message = ""
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        if int(month) not in MONTHS:
            message = "Month is not correct"
        elif int(day) not in DAYS:
             message = "Day is not correct"
        else:
            db.execute("INSERT INTO birthdays(name, month, day) VALUES (?, ?,?)",name, month, day)
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", message=message, birthdays=birthdays)
    else:
        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)



@app.route("/delete", methods=["POST"])
def delete():
    id = request.form.get("id")
    if id:
         db.execute("DELETE FROM birthdays WHERE id = ?", id)
    return redirect("/")


