# Servers

going from client-side then on server so can interact with things like databases

using dynamically generated webpages etc 

For the backend, the part programmer touches
frontend for the user

## Flask

Use a framework/library to solve common problems and save time

use flask run on cs50.dev

app.py
requirements.txt

from flask import Flask, render_template, request
app = Flask(__name__)

@app.route("/", methods=["GET"])
def index():
    if "name" in request.args:
        name = request.args("name")
    else:
        name = "world"
    return render_template("index.html", name=name)

With index.html in a templates folder

__name__ is special variable referencing name of the file
@ - python decorator, wrap a function into another

in requirements.txt put Flask
then pip install -r requirements.txt

:8080 common port for dev
:5000 Flask default

SPORTS = {
    "Basketball",
    "Soccer",
}

if not request.form.get("name") or request.form.get("sport")
    return render_template("failure.html", message"Missing sport")
if sport not in SPORTS:
    return render_template("failure.html", message="Invalid sport")

so now have server side validation, so even if something on client side changes then it will still be correct and block incorrect or malicious behaviour

REGISTRANTS[name]= sport

def registrants():
    return render_template("registrants.html", registrants=REGISTRANTS)

then can show them in table etc in template, but would really use a db

# Template

{{ placeholder }} in the html, when using with flask
so {{ name }} to get the name from Flask / what user put in url

request.args stores key value pairs of args from http message etc

in meta viewport ad width=device-width for responsive resizing

Use layout.html to reuse all of the common strucutre of webpage that all template pages then use

{% block body %}{% endblock % }

{% extends "layout.html" %}
{% block body %}
extra unused html {{ name }}
{% endblock %}


# Jinja

templating library used by Flask
has its own templates and common features

hello, 
{% if name %}
    {{ name }}
{% else %}
    world
{% endif %}

{% for sport in sports %}
    <option value="{{ sport }}">{{ sport }}</option>
{% endfor %}

# Static

static/
for images, js, css files

# POST

get for user stuff, e.g. to show url bars etc
POST for sending more 'private' or hidden data etc with forms

methods=["POST"] can also have GET add in app.route line

GET is stored in request.args, POST is in request.form (for Flask)

Payload - keyname for what you're sending to server

if request.method == "POST"

request.form.get("name")

# DB

If referesh server would lose all prev data
So use e.g. SQL database to have data persist across sessions

sqlit3

db.execute("INSERT INTO registrants (name, sport) VALUES(? , ?)", name sport)

query = "%" + request.args.get("q") + "%"
shows = db.execute("SELECT * FROM shows WHERE title LIKE ?", request.args.get("q"))
return render_template("search.html", shows=shows)

# MVC

Model, View, Controller

the app.py, flask business logic is Controller

The templated are the View

The DB is the Model

Can use javascript to produce some code client side too, so don't need server to generate it all

let input = document.querySelector('input');
input.addEventListener('input', async function() {
    let response = await fetch('/search?q=' + input.value);
    let shows = await response.text();
    document.querySelector('ul').textContent.trim() = shows;
})

request from js to the server, without human clicking submit

# Login

server in response includes key value pair Set-Cookie: session=value

where value usually random string, then there's also json tokens

next login browser then sends cookie header to server so logs in without needing to reauthenticate

But cookies do get tracked, servers plant them and your browser/computer is unique enough and build a profile of you.

from flask import Flask, session
from flask_session import Session

app.config("SESSION_PERMANENT") = False
app.config("SESSOIN_TYPE") = "filesystem"
Session(app)

and add Flask-Session to requirements.txt

session is per user variable

# JSON

don't sent back HTML, should really send dictionary style data

from flask import Flask, jsonify

# AJAX

asynchronous javascript (and xml, but now lots of json)
so update page, have server request without updating/refreshing whole webpage
e.g. sports scores on website, or new email in inbow

onreadystatechange - anon function when async http has completed

its what fetch() does, XMLHttpRequest also does

Axios library is an implementation to make it easier and then works very well with e.g. useEffect() or useState() in React