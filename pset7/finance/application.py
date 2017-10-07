from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    # if user reached route via POST
    if request.method == "POST":
        add_cash = float(request.form.get("add_cash"))
        current_cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]["cash"]
        total_cash = current_cash + add_cash
        db.execute("UPDATE users SET cash = :cash WHERE id = :user_id", cash=total_cash, user_id=session["user_id"])
        
        return redirect(url_for("index"))
        
    # else if user reached route via GET
    else:
        # get user's current balance
        user = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]
        
        # get stocks currently owned by user
        stocks = db.execute("SELECT symbol, SUM(shares), price FROM transactions WHERE user_id = :user_id GROUP BY symbol", user_id=session["user_id"])
        for stock in stocks:
            stock["current_price"] = lookup(stock["symbol"])["price"]
            stock["current_value"] = stock["current_price"] * stock["SUM(shares)"]
            
        # get sum of invested funds for user
        invested_funds = 0.0
        for stock in stocks:
            invested_funds += stock["current_price"] * stock["SUM(shares)"]
        user["invested_funds"] = invested_funds
        user["total_funds"] = user["invested_funds"] + user["cash"]
        
        # format values as USD
        for stock in stocks:
            stock["price"] = usd(stock["price"])
            stock["current_price"] = usd(stock["current_price"])
            stock["current_value"] = usd(stock["current_value"])
        for key in user:
            user[key] = usd(user[key])
        
        return render_template("index.html", stocks=stocks, user=user)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    
    # if user reached route via POST
    if request.method == "POST":
        
        # check if user has sufficient funds
        price = lookup(request.form.get("symbol"))["price"]
        shares = int(request.form.get("num_shares"))
        quote = shares * price
        user_funds = float(db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]["cash"])
        if quote > user_funds:
            return apology("Insufficient funds")
        
        # if sufficient funds, log transaction
        db.execute("INSERT INTO transactions (user_id, buy, symbol, shares, price) VALUES(:user_id, 1, :symbol, :shares, :price)", user_id=session["user_id"], symbol=request.form.get("symbol"), shares=shares, price=price)
        
        # decrement users funds
        remaining_funds = user_funds - quote
        db.execute("UPDATE users SET cash = :remaining_funds WHERE id = :user_id", remaining_funds=remaining_funds, user_id=session["user_id"])
        
        # redirect user to index
        return redirect(url_for("index"))
        
    # else if user reached route via GET
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
    # get list of transactions
    transactions = db.execute("SELECT buy, symbol, shares, price, timestamp FROM transactions WHERE user_id = :user_id", user_id=session["user_id"])
    
    # format information for table
    for transaction in transactions:
        transaction["shares"] = abs(transaction["shares"])
        transaction["price"] = usd(transaction["price"])
        if transaction["buy"] == 1:
            transaction["action"] = "Purchase"
        elif transaction["buy"] == 0:
            transaction["action"] = "Sale"
            transaction["price"] = '-' + transaction["price"]
        
    return render_template("history.html", transactions=transactions)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # If user reached route via POST
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))
        
        # ensure stock symbol is valid
        if not quote:
            return apology("That stock does not exist")
        
        # else display stock price
        else:
            return render_template("quoted.html", name=quote["name"], symbol=quote["symbol"], price=quote["price"])
    
    # else if user reached route via GET
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""
    
    # forget any user_id
    session.clear()
    
    # if user reached route via POST
    if request.method == "POST":
        
        # ensure username provided
        if not request.form.get("username"):
            return apology("must provide username")
            
        # ensure both password fields are filled in
        elif not request.form.get("password") or not request.form.get("password-confirm"):
            return apology("must provide password twice")
            
        # ensure passwords match
        elif request.form.get("password") != request.form.get("password-confirm"):
            return apology("passwords must match")
        
        # insert new user into database
        else:
            username = request.form.get("username")
            password = request.form.get("password")
            pwd_hash = pwd_context.hash(password)
            result = db.execute("INSERT INTO users(username, hash) VALUES(:username, :hash)", username=username, hash=pwd_hash)
            if not result:
                return apology("That username already exists")
            session["user_id"] = db.execute("SELECT id FROM users WHERE username = :username", username=username)
            return redirect(url_for("index"))
    
    # else if user reached route via GET
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    # get symbols of stocks user owns
    # stocks = db.execute("SELECT symbol FROM transactions WHERE user_id = :user_id GROUP BY symbol", user_id=session["user_id"])
    
    # if user reached route via POST
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("num_shares"))
        sell_shares = shares * -1
        sale_price = lookup(symbol)["price"]
        cash = float(db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])[0]["cash"])
        
        # ensure user owns sufficient shares of that stock
        user_stocks = db.execute("SELECT symbol, SUM(shares) FROM transactions WHERE user_id = :user_id and symbol = :symbol GROUP BY symbol", user_id=session["user_id"], symbol=symbol)
        if not user_stocks or user_stocks[0]["SUM(shares)"] < shares:
            return apology("You don't own enough of that stock")
            
        # else log transaction and add funds to user's cash
        new_cash = cash + (shares * sale_price)
        db.execute("INSERT INTO transactions (user_id, buy, symbol, shares, price) VALUES(:user_id, 0, :symbol, :shares, :price)", user_id=session["user_id"], symbol=symbol, shares=sell_shares, price=sale_price)
        db.execute("UPDATE users SET cash = :cash WHERE id = :user_id", cash=new_cash, user_id=session["user_id"])
        
        # redirect user to index
        return redirect(url_for("index"))
        
        
    # else if user reached route via GET
    if request.method == "GET":
        return render_template("sell.html")
