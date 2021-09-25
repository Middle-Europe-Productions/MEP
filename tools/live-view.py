from flask import Flask, flash, redirect, render_template, request, session, url_for, jsonify
from sqlite3 import sqlite3

app = Flask(__name__)
database = sqlite3.connect("C:/Users/Piotr/Desktop/Documentation Generator/data.db", check_same_thread=False)
db = database.cursor()


@app.route("/", methods=["GET"])
def index():
    return render_template("/main-page.html")

if __name__ == "__main__":
    app.run()
    db.close()