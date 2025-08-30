# Section notes

## Design principles

- Each table a collection of single entity, don't repeat rows etc
- Each piece of data stored in a single location and  referred to by primary ID (unique)

.schema to see table schema to then query easily

CREATE TABLE IF NOT EXISTS "friend" ("id" INTEGER NOT NULL, "first_name" TEXT NOT NULL, PRIMARY KEY ("id"));

ALTER TABLE friend ADD COLUMN "last_name" TEXT NOT NULL;

INSERT INTO friend (first_name, last_name) VALUES ("Carter", "Zenke");

INSERT INTO friend (first_name, last_name, id) VALUES ("Brian", "Yu", 5);

INSERT INTO friend (first_name, last_name, id) VALUES ("John", "Harvard", 2);

SELECT * FROM friend; - to list them

INSERT INTO friend (first_name, last_name, id) VALUES ("Elvis", "Costello"); - gets given id 6 as had given Brian Yu id 5 so gives next value and 3, 4 get skipped unless specified

SELECT * FROM friend LIMIT 1; - gets first id

___

SELECT name FROM songs WHERE duration < 240;
 
WHERE title LIKE "%Percy Jackson" all titles with percy jackson at end 
"Percy Jackson%" all with a start "%PERCY JACKSON%" somewhere in
Lots more keywords

SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5; - list 5 longest songs and just show their names

SELECT name FROM songs WHERE danceability > 0.75 AND energy > 0.75 > AND valence 0.75 - lists songs that match all these attributes can do OR if don't need all

# Aggregating

COUNT(), MIN(), MAX(), AVG(), SUM()

SELECT COUNT(*) FROM songs WHERE tempo > 100;
SELECT COUNT(*) AS n FROm songs WHERE tempo > 100; - just makes col name n instead of *

SELECT AVG(energy) FROM songs; - would get avg energy of all songs

Use quotes for whitespaces and double quote '' if quote in the string itself

# Multiple tables

SELECTs, JOINs

SELECT * FROM songs WHERE artist_id = (
    SELECT id FROM artists WHERE name = "Oh Wonder"
); - will get all songs by Oh Wonder, but needed to get id from artists to then use in songs table

SELECT * FROM songs JOIN artists ON songs.artist_id = artists.id; - the same as previous but using joins

SELECT AVG(energy)
FROM songs
WHERE aritst_id IN (SELECT id FROM artists WHERE name = 'Drake');
- would get avg energy of drake's songs

SELECT name FROM songs WHERE name LIKE '%feat.%'; - get songs that have feat in name i.e. feature other artists

## Other tools

MySQL, phpMyAdmin (GUI), integrate into python or php, sqlite3, pgadmin

Each column holds data of a particular type (LOTS)

INT, SMALLINT, TINYINT, MEDIUMINT, BIGINT, DECIMAL, FLOAT, BIT, DATE, TIME, DATETIME, TIMESTAMP, CHAR, VARCHAR, BINARY, BLOB, TEXT, ENUM, GEOMETRY, LINESTRING ...etc geometry/linestring e.g. for gis map data

CHAR - is a fixed length string e.g. CHAR(10) so "hi" would have 8 extra null parts, 
VARCHAR - variable length string, e.g. VARCHAR(99) up to 99

## JOINs

INNER JOIN (the standard JOIN) - only matching rows from both tables
LEFT JOIN - all rows from left table + matching rows from right, NULL if no match
RIGHT JOIN - above but reverse
CROSS JOIN - all combinations (cartesian product)
SELF JOIN - table joined to itself

UPDATE - modify information
UPDATE table SET column = 'value' WHERE id = number
DELETE FROM table WHERE column = 'value'

