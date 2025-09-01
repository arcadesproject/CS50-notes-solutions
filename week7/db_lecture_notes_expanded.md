# Databases: A Structured Overview

## Topics Covered

- [Flat-File Databases](#flat-file-databases)
- [CSV Files](#csv-files)
- [Relational Databases & SQL](#relational-databases--sql)
- [SQL Queries & Clauses](#sql-queries--clauses)
- [Table Relationships](#table-relationships)
- [JOIN Operations](#join-operations)
- [Indexes](#indexes)
- [Using SQL with Python](#using-sql-with-python)
- [Race Conditions](#race-conditions)
- [SQL Injection Attacks](#sql-injection-attacks)
- [Next Topics to Study](#next-topics-to-study)

---

## Flat-File Databases

Flat-file databases store data in plain text formats such as `.txt` or `.csv`. They are simple and easy to use but lack the structure, scalability, and querying capabilities of relational databases.

**Summary:**  
Best suited for small datasets and simple applications. Not ideal for complex relationships or large-scale querying.

---

## CSV Files

CSV (Comma-Separated Values) is a common flat-file format:

- Each line represents a row.
- Commas separate columns.
- The first row typically contains headers.

### Python Example: Reading CSV

```python
import csv

with open("filename.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        favorite = row["language"]
        print(favorite)
```

### Counting Occurrences

```python
counts = {}
with open("filename.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        favorite = row["language"]
        counts[favorite] = counts.get(favorite, 0) + 1

for favorite in sorted(counts, key=counts.get, reverse=True):
    print(f"{favorite}: {counts[favorite]}")
```

### Notes

- `csv.reader` returns rows as lists.
- `csv.DictReader` returns rows as dictionaries.
- `next(reader)` skips the header row (not needed with `DictReader`).
- Use `row[1]` for list-based access; use `row["column_name"]` for dictionary-based access.

**Summary:**  
CSV files are widely used for data exchange and are easily parsed in Python. They are ideal for simple tabular data but lack built-in validation or relationships.

---

## Relational Databases & SQL

SQL (Structured Query Language) is used to manage relational databases, which store data in structured tables with defined relationships.

### CRUD Operations

| Operation | SQL Command |
|-----------|-------------|
| Create    | `INSERT`    |
| Read      | `SELECT`    |
| Update    | `UPDATE`    |
| Delete    | `DELETE`    |

### Common SQL Engines

- SQLite
- PostgreSQL
- MySQL
- Oracle

### SQLite CLI Commands

```sql
.mode csv
.import favorites.csv favorites0
.schema table_name
.timer ON
```

**Summary:**  
Relational databases are powerful tools for managing structured data. SQL provides a standardized way to interact with them, though syntax may vary slightly between implementations.

---

## SQL Queries & Clauses

SQL queries allow you to retrieve, filter, and manipulate data.

### Examples

```sql
SELECT COUNT(*) FROM favorites;
SELECT DISTINCT language FROM favorites;
SELECT COUNT(DISTINCT language) FROM favorites;
SELECT COUNT(*) FROM favorites WHERE language = 'C';
SELECT language, COUNT(*) AS n FROM favorites GROUP BY language ORDER BY n DESC LIMIT 1;
```

### Clauses and Functions

- `WHERE`, `AND`, `OR`
- `GROUP BY`, `ORDER BY`, `LIMIT`
- Aliasing with `AS`
- Aggregate functions: `AVG`, `COUNT`, `MAX`, `MIN`, `LOWER`, `UPPER`

### Escaping Strings

Use double apostrophes (`''`) to escape single quotes inside strings.

**Summary:**  
SQL queries are highly expressive and allow for powerful data manipulation. Clauses and functions help refine and summarize results.

---

## Table Relationships

Relational databases support different types of relationships between tables:

### One-to-One

```sql
FOREIGN KEY(show_id) REFERENCES shows(id)
```

### One-to-Many

```sql
SELECT genre FROM genres
WHERE show_id = (SELECT id FROM shows WHERE title = 'Catweazle');
```

### Many-to-Many

```sql
SELECT name FROM people
WHERE id IN (
    SELECT person_id FROM stars
    WHERE show_id = (
        SELECT id FROM shows WHERE title = 'The Office' AND year = 2005
    )
);
```

**Summary:**  
Relationships allow data to be normalized across tables, reducing redundancy and improving consistency. Keys are used to link related records.

---

## JOIN Operations

JOINs combine data from multiple tables based on shared keys.

### Example: JOIN 3 Tables

```sql
SELECT title FROM shows
JOIN stars ON shows.id = stars.show_id
JOIN people ON stars.person_id = people.id
WHERE name = 'Steve Carell';
```

### Alternative Syntax

```sql
SELECT title FROM shows, stars, people
WHERE shows.id = stars.show_id
AND people.id = stars.person_id
AND name = 'Steve Carell';
```

**Summary:**  
JOINs are essential for querying across related tables. They can be nested or chained, but performance may vary depending on syntax and indexing.

---

## Indexes

Indexes improve query performance by creating efficient lookup structures.

### Examples

```sql
CREATE INDEX title_index ON shows(title);
CREATE INDEX name_index ON people(name);
CREATE INDEX person_index ON stars(person_id);
```

**Summary:**  
Indexes speed up data retrieval, especially for large datasets. They use memory and disk space, so they should be used strategically.

---

## Using SQL with Python

Python can interact with SQL databases using libraries like `sqlite3` or `cs50`.

### Example

```python
db = SQL("sqlite:///favorites.db")
favorite = input("Favorite: ")
rows = db.execute("SELECT COUNT(*) AS n FROM favorites WHERE language = ?", favorite)
print(rows[0]["n"])
```

**Summary:**  
Python provides flexible tools for querying databases. Results are returned as lists of dictionaries, making them easy to process.

---

## Race Conditions

Race conditions occur when multiple processes try to update the same data simultaneously.

### Safe Update Example

```python
db.execute("BEGIN TRANSACTION")
rows = db.execute("SELECT likes FROM posts WHERE id = ?", id)
likes = rows[0]["likes"]
db.execute("UPDATE posts SET likes = ? WHERE id = ?", likes + 1, id)
db.execute("COMMIT")
```

**Summary:**  
Transactions help prevent data corruption by locking operations until they’re complete. Use `BEGIN`, `COMMIT`, and `ROLLBACK` to manage them.

---

## SQL Injection Attacks

SQL injection is a security vulnerability caused by unsanitized user input.

### Unsafe vs Safe

```python
# Unsafe
db.execute(f"SELECT * FROM users WHERE email = '{email}'")

# Safe
db.execute("SELECT * FROM users WHERE email = ?", email)
```

**Summary:**  
Always use parameterized queries to prevent injection attacks. Never trust raw user input in SQL statements.

---

## Next Topics to Study

To build on this foundation, consider exploring:

- Database Security & Permissions
- Normalization & Denormalization
- Testing SQL Queries
- ORMs (Object-Relational Mappers) like SQLAlchemy or Django ORM
- Cloud Databases (e.g. AWS RDS, Firebase)
- Query Optimization & Execution Plans
- Stored Procedures & Triggers
- ACID Properties and Transaction Isolation Levels