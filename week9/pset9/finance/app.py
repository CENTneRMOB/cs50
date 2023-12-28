import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    current_user = session["user_id"]

    owns = db.execute(
        "SELECT name,symbol,quantity FROM users JOIN stock_balance ON users.id = stock_balance.user_id JOIN stocks ON stock_balance.stock_id = stocks.id WHERE users.id = ?",
        current_user,
    )

    cash = db.execute("SELECT cash FROM users WHERE id = ?", current_user)

    user_cash = cash[0]["cash"]
    grand_total = user_cash
    stocks = []

    for stock in owns:
        stock_info = {}
        stock_info["name"] = stock["name"]
        current_price = lookup(stock["symbol"])

        stock_info["price"] = current_price["price"]
        stock_info["position_price"] = round(
            current_price["price"] * stock["quantity"], 2
        )
        stock_info["count"] = stock["quantity"]

        grand_total += stock_info["position_price"]

        stocks.append(stock_info)

    return render_template(
        "index.html",
        current_cash=user_cash,
        grand_total=round(grand_total, 2),
        stocks=stocks,
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol")
        quantity = request.form.get("shares")
        stock_info = lookup(symbol)

        if not symbol or stock_info == None:
            return apology("THIS STOCK DOES NOT EXIST")

        try:
            quantity = int(quantity)
        except ValueError:
            return apology("TYPE A NUMBER")

        if quantity < 0:
            return apology("TYPE A POSITIVE NUMBER")

        current_user = session["user_id"]
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?;", current_user)[0][
            "cash"
        ]

        stock_fullprice = round(float(stock_info["price"]) * float(quantity), 2)

        if stock_fullprice > float(user_cash):
            return apology("YOU DON'T HAVE ENOUGH CASH FOR THIS PURCHASE")

        db.execute(
            "INSERT or IGNORE INTO stocks (name, symbol) VALUES (?, ?)",
            stock_info["name"],
            stock_info["symbol"],
        )

        stock_id = db.execute(
            "SELECT id FROM stocks WHERE symbol = ?", stock_info["symbol"]
        )[0]["id"]

        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?",
            round(float(user_cash) - stock_fullprice, 2),
            current_user,
        )

        db.execute(
            "INSERT INTO purchases (user_id, stock_id, stock_price, stock_count, purchase_date, type) VALUES (?, ?, ?, ?, ?, ?)",
            current_user,
            stock_id,
            float(stock_info["price"]),
            quantity,
            datetime.datetime.now(),
            "buy",
        )

        existing_stocks = db.execute(
            "SELECT * FROM stock_balance WHERE user_id = ? AND stock_id = ?",
            current_user,
            stock_id,
        )

        if len(existing_stocks) == 0:
            db.execute(
                "INSERT INTO stock_balance (user_id, stock_id, quantity) VALUES (?, ?, ?)",
                current_user,
                stock_id,
                quantity,
            )
        else:
            existing_quantity = existing_stocks[0]["quantity"]
            db.execute(
                "UPDATE stock_balance SET quantity = ? WHERE user_id = ? AND stock_id = ?",
                existing_quantity + quantity,
                current_user,
                stock_id,
            )

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    current_user = session["user_id"]

    user_purchases = db.execute(
        "SELECT stock_price, stock_count, purchase_date, type, symbol FROM purchases JOIN stocks ON stocks.id = purchases.stock_id WHERE user_id = ? ORDER BY purchase_date",
        current_user,
    )

    return render_template("history.html", purchases=user_purchases)


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
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("INPUT SOME STOCK SYMBOL")

        stock_info = lookup(symbol)

        if stock_info == None:
            return apology("INCORRECT STOCK SYMBOL", 400)

        return render_template("quoted.html", item=stock_info)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")

    else:
        username = request.form.get("username")
        if not username:
            return apology("INPUT YOUR USERNAME", 400)

        users = db.execute("SELECT username FROM users;")

        for exist_user in users:
            if exist_user["username"] == username:
                return apology("USERNAME ALREADY EXISTS", 400)

        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not password:
            return apology("INPUT PASSWORD", 400)

        if password != confirmation:
            return apology("PASSWORD AND CONFIRMATION DO NOT MATCH", 400)

        db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            username,
            generate_password_hash(password),
        )

        return redirect("/login")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    current_user = session["user_id"]

    user_stocks = db.execute(
        "SELECT symbol, quantity FROM stocks JOIN stock_balance ON stocks.id = stock_balance.stock_id WHERE stock_balance.user_id = ?",
        current_user,
    )

    if request.method == "GET":
        return render_template("sell.html", stocks=user_stocks)

    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        user_symbols = list(map(lambda x: x["symbol"], user_stocks))

        if not symbol:
            return apology("CHOOSE STOCK FOR SELL")
        if symbol not in user_symbols:
            return apology("YOU DON'T HAVE THIS TYPE OF STOCKS")

        try:
            shares = int(shares)
        except ValueError:
            return apology("TYPE A NUMBER")

        if shares < 0:
            return apology("TYPE A POSITIVE NUMBER")

        stocks_by_symbol = db.execute(
            "SELECT quantity FROM stock_balance WHERE user_id = ? AND stock_id = (SELECT id FROM stocks WHERE symbol = ?)",
            current_user,
            symbol,
        )[0]["quantity"]

        if shares > stocks_by_symbol:
            return apology("YOU DON'T HAVE ENOUGH STOCKS")

        current_stock_price = lookup(symbol)["price"]
        stock_id = db.execute("SELECT id FROM stocks WHERE symbol = ?", symbol)[0]["id"]

        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", current_user)[0][
            "cash"
        ]

        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?",
            round(user_cash + (current_stock_price * shares), 2),
            current_user,
        )

        if stocks_by_symbol == shares:
            db.execute(
                "DELETE FROM stock_balance WHERE user_id = ? AND stock_id = ?",
                current_user,
                stock_id,
            )
        elif stocks_by_symbol > shares:
            existing_quantity = stocks_by_symbol
            db.execute(
                "UPDATE stock_balance SET quantity = ? WHERE user_id = ? AND stock_id = ?",
                existing_quantity - shares,
                current_user,
                stock_id,
            )

        db.execute(
            "INSERT INTO purchases (user_id, stock_id, stock_price, stock_count, purchase_date, type) VALUES (?, ?, ?, ?, ?, ?)",
            current_user,
            stock_id,
            current_stock_price,
            shares,
            datetime.datetime.now(),
            "sell",
        )

        return redirect("/")


@app.route("/cashin", methods=["GET", "POST"])
@login_required
def cashin():
    """Add cash to account"""
    current_user = session["user_id"]

    if request.method == "GET":
        return render_template("cashin.html")
    else:
        quantity = request.form.get("quantity")

        try:
            quantity = int(quantity)
        except ValueError:
            return apology("TYPE A NUMBER")

        if quantity < 0:
            return apology("TYPE A POSITIVE NUMBER")

        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", current_user)[0][
            "cash"
        ]

        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?",
            round(user_cash + quantity, 2),
            current_user,
        )

        return redirect("/")
