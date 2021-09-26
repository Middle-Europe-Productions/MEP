from flask import Flask, flash, redirect, render_template, request, session, url_for, jsonify
import sqlite3
from time import sleep
app = Flask(__name__)

@app.route("/", methods=["GET"])
def index():
    return render_template("/main-page.html")

@app.route("/update-frames", methods=['POST'])
def update_frames():
    check = db.execute("SELECT * FROM Frame").fetchall()
    for x in check:
        print(x)
    return jsonify({"success"})

@app.route("/update", method=['POST'])
def update():
    return jsonify({"success"})


def run_server(database):
    global db
    db = database.cursor()
    app.run()
    
    while True:
        print("Get")
        check = db.execute("SELECT * FROM Things").fetchall()
        for x in check:
            print(x)
        print(f"---{len(check)}---")
        sleep(1)