# SQL & Relational Database Notes

## Topics Covered

- [Design Principles](#design-principles)
- [Basic Table Operations](#basic-table-operations)
- [Querying with Conditions](#querying-with-conditions)
- [Aggregation Functions](#aggregation-functions)
- [Working with Multiple Tables](#working-with-multiple-tables)
- [Data Types & Tools](#data-types--tools)
- [JOIN Types](#join-types)
- [Update & Delete Operations](#update--delete-operations)
- [Next Topics to Study](#next-topics-to-study)

---

## Design Principles

- Each table should represent a single entity (e.g. `friend`, `song`, `artist`).
- Avoid data duplication; each piece of data should be stored once and referenced via a unique identifier.
- Use a `PRIMARY KEY` to uniquely identify each row.
- Use `.schema` in SQLite to inspect table structure before querying.

**Summary:**  
Good database design ensures clarity, consistency, and scalability. Normalization and unique identifiers help maintain data integrity and reduce redundancy.

---

## Basic Table Operations

### Creating and Modifying Tables

```sql
CREATE TABLE IF NOT EXISTS friend (
    id INTEGER NOT NULL,
    first_name TEXT NOT NULL,
    PRIMARY KEY (id)
);

ALTER TABLE friend ADD COLUMN last_name TEXT NOT NULL;
```

### Inserting Data

```sql
INSERT INTO friend (first_name, last_name) VALUES ("Carter", "Zenke");
INSERT INTO friend (first_name, last_name, id) VALUES ("Brian", "Yu", 5);
INSERT INTO friend (first_name, last_name, id) VALUES ("John", "Harvard", 2);
INSERT INTO friend (first_name, last_name, id) VALUES ("Elvis", "Costello");
```

- If `id` is not specified, SQLite will auto-increment it.
- Skipped IDs (e.g. 3, 4) remain unused unless manually inserted.

### Viewing Data

```sql
SELECT * FROM friend;
SELECT * FROM friend LIMIT 1;
```

**Summary:**  
Creating, altering, and inserting into tables are foundational SQL operations. Auto-incrementing IDs simplify record management, and `SELECT` retrieves data for inspection.

---

## Querying with Conditions

### Filtering by Value

```sql
SELECT name FROM songs WHERE duration < 240;
```

### Pattern Matching with `LIKE`

```sql
-- Ends with "Percy Jackson"
SELECT title FROM songs WHERE title LIKE "%Percy Jackson";

-- Starts with "Percy Jackson"
SELECT title FROM songs WHERE title LIKE "Percy Jackson%";

-- Contains "Percy Jackson" anywhere
SELECT title FROM songs WHERE title LIKE "%Percy Jackson%";
```

### Sorting and Limiting

```sql
SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5;
```

### Multiple Conditions

```sql
SELECT name FROM songs
WHERE danceability > 0.75 AND energy > 0.75 AND valence > 0.75;
```

**Summary:**  
SQL conditions allow precise filtering and sorting. `LIKE` enables flexible pattern matching, and `ORDER BY` with `LIMIT` helps extract top results.

---

## Aggregation Functions

SQL provides built-in functions to summarize data:

- `COUNT()`
- `MIN()`
- `MAX()`
- `AVG()`
- `SUM()`

### Examples

```sql
SELECT COUNT(*) FROM songs WHERE tempo > 100;
SELECT COUNT(*) AS n FROM songs WHERE tempo > 100;
SELECT AVG(energy) FROM songs;
```

### Notes

- Use quotes for strings with spaces.
- Use double apostrophes (`''`) to escape quotes inside strings.

**Summary:**  
Aggregation functions are essential for analyzing datasets. They help compute totals, averages, and other metrics across rows.

---

## Working with Multiple Tables

### Subqueries

```sql
SELECT * FROM songs
WHERE artist_id = (
    SELECT id FROM artists WHERE name = "Oh Wonder"
);
```

### JOINs

```sql
SELECT * FROM songs
JOIN artists ON songs.artist_id = artists.id;
```

### Aggregation with Subquery

```sql
SELECT AVG(energy)
FROM songs
WHERE artist_id IN (
    SELECT id FROM artists WHERE name = 'Drake'
);
```

### Pattern Matching

```sql
SELECT name FROM songs WHERE name LIKE '%feat.%';
```

**Summary:**  
Subqueries and JOINs allow you to work across multiple tables. They’re powerful tools for combining and filtering related data.

---

## Data Types & Tools

### Common SQL Tools

- MySQL
- SQLite3
- PostgreSQL
- phpMyAdmin (GUI)
- pgAdmin

### Data Types

| Category     | Examples                                                                 |
|--------------|--------------------------------------------------------------------------|
| Integers     | `INT`, `SMALLINT`, `TINYINT`, `MEDIUMINT`, `BIGINT`                     |
| Decimals     | `DECIMAL`, `FLOAT`                                                      |
| Binary       | `BIT`, `BINARY`, `BLOB`                                                 |
| Text         | `CHAR`, `VARCHAR`, `TEXT`, `ENUM`                                       |
| Date/Time    | `DATE`, `TIME`, `DATETIME`, `TIMESTAMP`                                 |
| Spatial      | `GEOMETRY`, `LINESTRING` (used in GIS applications)                     |

### Notes

- `CHAR(n)` stores fixed-length strings (padded with nulls).
- `VARCHAR(n)` stores variable-length strings up to `n` characters.

**Summary:**  
Understanding data types is crucial for defining columns correctly. Each type has specific use cases and performance implications.

---

## JOIN Types

SQL supports several types of JOINs:

| JOIN Type    | Description                                                                 |
|--------------|-----------------------------------------------------------------------------|
| `INNER JOIN` | Returns rows with matching values in both tables                           |
| `LEFT JOIN`  | Returns all rows from the left table, and matched rows from the right      |
| `RIGHT JOIN` | Returns all rows from the right table, and matched rows from the left      |
| `CROSS JOIN` | Returns the Cartesian product of both tables                               |
| `SELF JOIN`  | Joins a table to itself                                                    |

**Summary:**  
JOIN types determine how tables are merged. Choosing the right JOIN depends on the structure of your data and the desired output.

---

## Update & Delete Operations

### Updating Records

```sql
UPDATE table SET column = 'value' WHERE id = number;
```

### Deleting Records

```sql
DELETE FROM table WHERE column = 'value';
```

**Summary:**  
Use `UPDATE` to modify existing data and `DELETE` to remove records. Always use `WHERE` to avoid affecting unintended rows.

---

## Next Topics to Study

To continue building your SQL and database skills, consider exploring:

- Normalization & Denormalization
- Indexing strategies and performance tuning
- ACID properties and transaction isolation levels
- Stored Procedures and Triggers
- Views and Materialized Views
- Role-based access control and permissions
- Object-Relational Mapping (ORM) with SQLAlchemy or Django
- NoSQL databases (e.g. MongoDB, Redis) and their differences from relational models
