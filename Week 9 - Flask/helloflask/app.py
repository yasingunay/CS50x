from flask import Flask, render_template, request

app = Flask(__name__)

COLORS = [
    "red",
    "blue"
]


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "GET":
        return render_template("index.html", colors=COLORS)
    else:
        print("Form submitted!")
        color = request.form.get("color")
        
        # Ensure the colors we receive are valid colors
        if color not in COLORS:
            return render_template("failure.html")
        return render_template("color.html", color=color)