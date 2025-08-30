# Server-Side Web Development with Flask

## Topics Covered

- [Client vs Server](#client-vs-server)
- [Flask Framework](#flask-framework)
- [Templates & Jinja](#templates--jinja)
- [Static Files](#static-files)
- [GET vs POST](#get-vs-post)
- [Database Integration](#database-integration)
- [MVC Architecture](#mvc-architecture)
- [JavaScript & Server Interaction](#javascript--server-interaction)
- [Login & Sessions](#login--sessions)
- [JSON Responses](#json-responses)
- [AJAX & Asynchronous Requests](#ajax--asynchronous-requests)
- [Next Topics to Study](#next-topics-to-study)

---

## Client vs Server

Web applications are split into:

- **Frontend**: What users see and interact with (HTML, CSS, JavaScript).
- **Backend**: Logic, data handling, and server-side operations (Flask, databases).

Dynamic websites use server-side code to generate content based on user input or stored data.

**Summary:**  
The frontend handles user interaction, while the backend processes data and serves dynamic content.

---

## Flask Framework

Flask is a lightweight Python web framework used to build server-side applications.

### Basic Setup

```python
from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/", methods=["GET"])
def index():
    name = request.args.get("name", "world")
    return render_template("index.html", name=name)
```

- `@app.route` is a decorator that maps URLs to functions.
- `__name__` is a special variable that refers to the current module.
- Templates are stored in a `templates/` folder.
- Common development ports: `5000` (Flask default), `8080`.

### Installation

Create a `requirements.txt` file:

```
Flask
```

Then install dependencies:

```bash
pip install -r requirements.txt
```

**Summary:**  
Flask simplifies backend development by providing routing, templating, and request handling out of the box.

---

## Templates & Jinja

Flask uses Jinja2 for templating. Templates allow dynamic content to be inserted into HTML.

### Example

```html
<!-- index.html -->
<h1>Hello, {{ name }}</h1>
```

### Layouts

Use `layout.html` for shared structure:

```html
<!-- layout.html -->
<!DOCTYPE html>
<html>
  <head><title>My Site</title></head>
  <body>
    {% block body %}{% endblock %}
  </body>
</html>
```

Extend layout in other templates:

```html
{% extends "layout.html" %}
{% block body %}
  <p>Welcome, {{ name }}</p>
{% endblock %}
```

**Summary:**  
Templates allow separation of logic and presentation. Jinja syntax supports conditionals, loops, and inheritance.

---

## Static Files

Static assets like images, CSS, and JavaScript are stored in a `static/` folder.

Example structure:

```
static/
  style.css
  script.js
  logo.png
```

**Summary:**  
Static files are served directly to the browser and are not processed by Flask.

---

## GET vs POST

- **GET**: Sends data via URL parameters. Stored in `request.args`.
- **POST**: Sends data in the request body. Stored in `request.form`.

### Example

```python
@app.route("/submit", methods=["POST"])
def submit():
    name = request.form.get("name")
```

Use POST for sensitive or form-submitted data.

**Summary:**  
GET is used for retrieving data; POST is used for submitting data securely.

---

## Database Integration

To persist data across sessions, use a database like SQLite.

### Example

```python
db.execute("INSERT INTO registrants (name, sport) VALUES (?, ?)", name, sport)

query = "%" + request.args.get("q") + "%"
shows = db.execute("SELECT * FROM shows WHERE title LIKE ?", query)
return render_template("search.html", shows=shows)
```

**Summary:**  
Databases store and retrieve structured data, enabling persistent and dynamic web applications.

---

## MVC Architecture

MVC separates concerns:

- **Model**: Database and data logic.
- **View**: HTML templates.
- **Controller**: Flask routes and business logic.

**Summary:**  
MVC improves code organization and scalability by separating data, logic, and presentation.

---

## JavaScript & Server Interaction

JavaScript can send requests to the server without reloading the page.

### Example

```javascript
let input = document.querySelector('input');
input.addEventListener('input', async function() {
    let response = await fetch('/search?q=' + input.value);
    let shows = await response.text();
    document.querySelector('ul').innerHTML = shows;
});
```

**Summary:**  
JavaScript enables dynamic client-side behavior and asynchronous communication with the server.

---

## Login & Sessions

Sessions track user state across requests.

### Example

```python
from flask import Flask, session
from flask_session import Session

app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)
```

- Add `Flask-Session` to `requirements.txt`.
- Sessions are stored per user and can hold login state.

**Summary:**  
Sessions allow persistent user authentication and personalization across requests.

---

## JSON Responses

Instead of returning HTML, APIs often return JSON.

### Example

```python
from flask import jsonify

@app.route("/data")
def data():
    return jsonify({"name": "Alice", "sport": "Soccer"})
```

**Summary:**  
JSON is the standard format for data exchange between client and server in modern web applications.

---

## AJAX & Asynchronous Requests

AJAX allows web pages to update without full reloads.

- `fetch()` is the modern way to make AJAX requests.
- `XMLHttpRequest` is the older method.
- Libraries like Axios simplify AJAX and integrate well with frameworks like React.

**Summary:**  
AJAX enables seamless user experiences by asynchronously fetching and updating data.

---

## Next Topics to Study

To deepen your understanding of server-side development, consider exploring:

- RESTful API design and routing
- Flask Blueprints for modular apps
- SQLAlchemy ORM for database abstraction
- Authentication and authorization (OAuth, JWT)
- WebSockets for real-time communication
- Deployment with Docker, Gunicorn, and cloud platforms
- Testing Flask apps with pytest
- Rate limiting and request throttling
- CSRF protection and secure form handling