from flask import Flask, flash, redirect, render_template, request, session, url_for, jsonify
from flask_socketio import SocketIO, send
from apscheduler.schedulers.background import BackgroundScheduler
import sqlite3
from time import sleep
app = Flask(__name__)
socketio = SocketIO(app)

static = 10;
@app.route("/")
def index():
    return render_template("main-page.html")

#defines the job
def job():
    check = db.execute("SELECT * FROM Frame").fetchall()
    for x in check:
        print(x)
        db.execute("SELECT * FROM Package HERE frameID == ?", x).fetchall()
    #job emits on websocket
    print(check)
    socketio.emit('update', check, broadcast=True)

#schedule job
scheduler = BackgroundScheduler()
running_job = scheduler.add_job(job, 'interval', seconds=1, max_instances=1)
scheduler.start()


def run_server(database):
    global db
    db = database.cursor()
    socketio.run(app)