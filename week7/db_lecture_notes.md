# Databases

flat-file databases text etc

# csv 
comma separated values ascii/unicode row by row / line by line

interpret commas delineating where columns end

first row usually header / columns

with open("filename.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        favorite = row["langauge"]
        print(favorite)

    or
    counts = {}
    favorite = row("language")
    if favorite in counts:
        counts[favorite] += 1
    else:
        counts[favorite] = 1

for favorite in counts:
    print(f"{favorite}: {counts[favorite]})

will sort by count totals from most to least:
for favorite in sorted(counts, key=counts.get, reverse=True):

so prints second col of each line and next(reader) skips header/col names, don't need next for dictreader

reader gives sequence of list, dictreader gives dict
so row[1] for reader etc

# Relational Databases

SQL: Structured Query Language

CRUD: Create, Read, Update, Delete

in SQL:
CREATE UPDATE DELETE
SELECT (for read), also INSERT, DROP

Has tables: Rows/Columns

Lots of different sql implementations often CLI - sqlit, postgres, oracle etc all with slightly different sugar

sqlite3
.mode csv
.import favorites.csv favorites0

.schema table_name - gets to see what schema defs are to get stuff

.timer ON - to see how quick etc

SELECT columns FROM table;

AVG, COUNT, DISTINCT, LOWER< MAX, MIN, UPPER etc

SELECT COUNT(*) FROM favorites; - count of rows so e.g. 300 rows
SELECT DISTINCT language FROM favorites; - shows the unique values
SELECT COUNT(DISTICNT language) FROM favorites; - count of uniques
SELECT COUNT(*) FROM favorites WHERE language = 'C'; - count of rows with favorite C
then can add AND problem = 'Hello world'; - would add where problem col values are also hellow world and language is C

For escapes instead use two of it? e.g. two apostrophes for string confusion

GROUP BY, LIKE, LIMIT, ORDER BY, WHERE

SELECT language, COUNT(*) AS n FROM favorites GROUP BY language ORDER BY COUNT(*) DESC - does same as the earlier sorted python code

ORDER BY n DESC to set column name as n - **aliasing**

LIMIT - to limit results e.g. top 10, 20 etc
after DESC put LIMIT 1; to just get top language

INSERT INTO Table (column, ...) VALUES (value, ...)

NULL to represent absence of value

DELETE FROM table WHERE condition;

DELETE FROM table; - deletes everything, DO NOT!
DELETE FROM favorites WHERE Timestamp IS NULL;

UPDATE table SET column = value WHERE condition;

Use unique identifiers for things and then link them together, using simple integers

Schema is design of database

Relational databases have different types of relationships. e.g. one-to-one so one show_id has one rating and names changes so in original table shows has id, title, year, episodes but then in a ratings table the id will then become show_id

PRIMARY KEY(id) - defines uniqueness a unique id for tables rows in shows table here
FOREIGN KEY(show_id) REFERENCES shows(id) - a primary key from another table

BLOB, INTEGER, NUMERIC, REAL, TEXT - binary large object, integer, numbers but years/dates, floating point, text

NOT NULL, UNIQUE - has to have value, has to be unique

SELECT show_id FROM ratings WHERE rating >= 6.0 LIMIT 10; - get 10 show_ids in ratings that are over 6 ratings

SELECT title FROM shows WHERE id IN (SELECT show_id FROM ratings WHERE rating >= 6.0) LIMIT 10; - uses the ids from ratings, passing to get info from the shows table, this is a **nested query**

ok to use enter key with sqlite for multiple line easier readability will just see ...> on cli

## JOIN

JOIN for joining tables with SQL

SELECT title, rating FROM shows JOIN ratings ON shows.id = ratings.show_id WHERE rating >= 6.0 LIMIT 10; - so where those ids match you can join the information you want

**one-to-many** - e.g. on id has many genres

SELET id FROM shows WHERE title = 'Catweazle'; - gets id
SELCT genre FROM genres WHERE show_id = (SELECT id FROM shows WHERE title = 'Catweazle'); - so gets genre using id

SELECT title, genre FROM shows JOIN genres ON shows.id = genres.show_id WHERE id = 63881; - when joining will repeat the lesser values to keep dimensions rowsxcolumns, e.g. show title repeated for diff genre

**many-to-many**

e.g. show with lots of tv stars, other values - people table, stars table, shows table

SELECT id FROM shows WHERE title = 'The Office' AND year = 2005; - get show id
SELECT person_id FROM stars WHERE show_id = (
    ...> SELECT id FROM shows WHERE title = 'The Office' AND year = 2005); - gets all ids of stars in the office

SELECT name FROM people WHERE id IN
...> (SELECT person_id FROM stars WHERE show_id =
...> (SELECT id FROM shows WHERE title = 'The Office' AND year = 2005)); - gets peoples names where person ids from stars that match shows ids that match the office from 2005

can also JOIN

SELECT title FROM shows
...> JOIN stars ON shows.id = stars.show_id
...> JOIN people ON stars.person_id = people.id
...> WHERE name = 'Stever Carell';
- joining 3 tables based on say id keys but slower ish

SELECT title FROM shows, stars, people
...> WHERE shows.id = stars.show_id
...> AND people.id = stars.person_id
...> AND name = 'Steve Carell';
- same idea as previous, on ids diff syntax also little slow

## indexes

For more efficiency, structure it better using data structures/algos

CREATE INDEX name ON table (column, ...);

If you know certain things will be common searches, create b tree on RAM

CREATE INDEX title_index ON shows (title); - create index on shows table title column

CREATE INDEX name_index ON people (name);
CREATE INDEX person_index on stars(person_id);

SELECT TITLE FROM shows WHERE id IN
...> (SELECT show_id FROM stars WHERE person_id =
...> (SELECT id FROM people WHERE name = 'Steve Carell')); - will now be far faster

BUT creating indexes does take up space using b trees

Very good for very read heavy sites etc

## with python

db = SQL("sqlite://favorites.db)
favorite = input("Favorite: ")
row = db.execute("SELECT COUNT(*) AS n FROM favorites WHERE language = ?", favorite)
row = rows[0]
print(row("n"))

rows as list, containing dictionaries, bit like DictReader for the readcsv

## Race conditions

make sure to signal process of updating so another query does not also try to update variable, lock it to prevent

e.g. if thousands of likes on a post per second, +1 likes on non updates values so does not increment properly

BEGIN TRANSACTION, COMMIT, ROLLBACK - start/lock, update, revert

db.execute("BEGIN TRANSACTION")
rows = db.execute("SELECT likes FROM posts WHERE id = ?", id);
likes = rows[0]["likes"]
db.execute("UPDATE posts SET likes = ? WHERE id = ?", likes + 1, id);
db.execute("COMMIT")

## Injection attacks

injecting unexpected input, e.g. using invalid email characters but valid sql chars '-- (-- is start of comment, so gets ignored and thus maybe ignore password fields etc)

never trust user input, so use placeholders rather than straight user input

drop tables etc. malicious attacks







