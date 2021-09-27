from flask import Flask, flash, redirect, render_template, request, session, url_for, jsonify
from flask_socketio import SocketIO, send
from apscheduler.schedulers.background import BackgroundScheduler
import sqlite3
import json
from time import sleep
app = Flask(__name__)
socketio = SocketIO(app)

static = 10;
@app.route("/")
def index():
    return render_template("main-page.html")

def query_db(query, args=(), one=False):
    db.execute(query, args)
    r = [dict((db.description[i][0], value) \
               for i, value in enumerate(row)) for row in db.fetchall()]
    return (r[0] if r else None) if one else r

def getData():
    check = db.execute("SELECT * FROM Frame").fetchall()
    json_output = dict()
    it = 0;
    for x in check:
        my_query = query_db("SELECT * FROM Package WHERE frameID = ?", (x[0],))
        json_output[it] = json.dumps(my_query)
        it += 1
    return json_output

def job():
    json = getData()
    obj = [json, len(json)];
    socketio.emit('update', obj, broadcast=True)

#schedule job
scheduler = BackgroundScheduler()
running_job = scheduler.add_job(job, 'interval', seconds=1, max_instances=1)
scheduler.start()


def run_server(database):
    global db
    db = database.cursor()
    socketio.run(app)