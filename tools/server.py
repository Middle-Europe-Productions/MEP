from flask import Flask, flash, redirect, render_template, request, session, url_for, jsonify
import sqlite3
app = Flask(__name__)

@app.route("/", methods=["GET"])
def index():
    return render_template("/main-page.html")

def run_server(database):
    global db
    db = database.cursor()
    
    app.run()