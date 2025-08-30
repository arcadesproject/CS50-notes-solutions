import os

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
    user = session["user_id"]

    # Get user's stocks
    stocks = db.execute("""SELECT symbol, SUM(shares) AS total_shares
                            FROM transactions WHERE user_id = ?
                            GROUP BY symbol HAVING SUM(shares) > 0""", user)
    print(stocks)

    # Get users's cash
    rows = db.execute("SELECT cash FROM users WHERE id = ?", user)
    cash = rows[0]["cash"]

    # create portfolio array with dict for each entry with info
    portfolio = []
    total_holdings = cash
    for stock in stocks:
        symbol = stock["symbol"]
        quote = lookup(stock["symbol"])
        if quote is None:
            return apology("stock lookup failed")

        current_price = quote["price"]
        total_shares = int(stock["total_shares"])
        total_value = current_price * total_shares
        total_holdings += total_value

        portfolio.append({
            "symbol": symbol,
            "shares": total_shares,
            "price": current_price,
            "total": total_value
        })

    return render_template("index.html", portfolio=portfolio, cash=cash, total_holdings=total_holdings)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """
    Ensure symbol and shares number positive
    Ensure user has cash to pay for amount of stock
    Update transactions history
    Update users cash balance
    """
    if request.method == "POST":
        # ensure symbol submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
        if not request.form.get("shares"):
            return apology("must provide number of shares", 400)

        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        if not shares.isdigit() or int(shares) <= 0:
            return apology("number of shares must be a positive integer", 400)

        shares_int = int(shares)
        stock_quote = lookup(symbol)

        if stock_quote is None:
            return apology("invalid symbol", 400)

        rows = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        if not rows:
            return apology("user not found", 400)

        user_cash = rows[0]["cash"]

        if (stock_quote["price"] * int(shares) > user_cash):
            return apology("not enough cash", 400)

        # Insert into DB with try/except
        try:
            db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)", session["user_id"], symbol, shares, stock_quote["price"])
        except Exception as e:
            return apology("failed to complete purchase", 400)

        # update user's cash balance
        try:
            total_price = shares_int * stock_quote["price"]
            db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_price, session["user_id"])
        except Exception as e:
            return apology("failed to complete purchase", 400)

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions
    Symbol / Shares / Sell price / Transacted
    """
    user = session["user_id"]

    transactions = db.execute("SELECT * FROM transactions where user_id = ? ORDER BY transacted DESC", user)
    transactions_list = []
    for t in transactions:
        transactions_list.append({
            "symbol": t["symbol"],
            "shares": t["shares"],
            "price": t["price"],
            "transacted": t["transacted"]
        })

    return render_template("history.html", transactions_list=transactions_list)


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
        flash("Logged in successfully!", "success")
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
    """
    Get symbol user enters on quote.html
    Lookup symbol, get quote (name/symbol/price)
    Error if nothing returned
    Render on quoted.html
    """
    if request.method == "POST":
        # ensure symbol submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        symbol = request.form.get("symbol").upper()

        stock_quote = lookup(symbol)

        if stock_quote is None:
            return apology("invalid symbol", 400)

        return render_template("quoted.html", stock=stock_quote)

    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """
    Registers user
    Makes sure username, password, confirmation exist
    Checks password and confirmation match
    Inserts user into users db with hashed password
    Try/except for db error
    Redirects to home on success
    """

    if request.method == "POST":
        # ensure username submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)
        # ensure password submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        # ensure password confirmation submitted
        elif not request.form.get("confirmation"):
            return apology("must repeat password", 400)
        # ensure password and confirmation match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords don't match", 400)

        # Query database for username
        if db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        ):
            return apology("username already exists", 400)
        else:
            # username
            username = request.form.get("username")
            # hash password
            password_hash = generate_password_hash(request.form.get("password"))

            # Insert into DB with try/except
            try:
                db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, password_hash)
            except Exception as e:
                flash(f"An error occurred while registering: {e}", "danger")
                return apology("failed to register user", 400)

            # TODO: fix flashing appearance
            # successful redirect
            flash("Registered successfully!", "success")
            return redirect("/login")

    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Get user
    user = session["user_id"]

    # Get user's stocks
    stocks = db.execute("""SELECT symbol, SUM(shares) AS total_shares
                            FROM transactions WHERE user_id = ?
                            GROUP BY symbol HAVING SUM(shares) > 0""", user)

    stocks_list = []
    owned_stocks = []
    for stock in stocks:
        symbol = stock["symbol"]
        total_shares = stock["total_shares"]

        stocks_list.append({
            "symbol": symbol,
            "shares": total_shares
        })

        owned_stocks.append(symbol)

    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("need to enter a stock symbol", 400)

        if not request.form.get("shares"):
            return apology("need number of shares", 400)

        shares = int(request.form.get("shares"))
        negative_shares = -shares
        symbol = request.form.get("symbol")

        if shares <= 0:
            return apology("need positive number of shares", 400)

        if symbol not in owned_stocks:
            return apology("you don't own the selected stock", 400)

        stock_owned = next(s for s in stocks_list if s["symbol"] == symbol)
        if stock_owned["shares"] < shares:
            return apology("you do not have that many shares", 400)

        try:
            stock_quote = lookup(symbol)
        except Exception as e:
            return apology("could not find stock price", 400)

        # Insert into DB with try/except
        try:
            db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)", user, symbol, negative_shares, stock_quote["price"])
        except Exception as e:
            return apology("failed to complete purchase", 403)

        # update user's cash balance
        try:
            db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", stock_quote["price"] * shares, user)
        except Exception as e:
            return apology("failed to complete purchase", 403)

        return redirect("/")

    else:
        return render_template("sell.html", stocks_list=stocks_list)
