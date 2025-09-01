CREATE TABLE shows (id INTEGER, title TEXT NOT NULL, PRIMARY KEY(id));
CREATE TABLE genres (show_id INTEGER, genre TEXT NOT NULL, FOREIGN KEY(show_id) REFERENCES shows(id));

UPDATE shows SET title = 'Adventure Time' WHERE LOWER(TRIM(title)) LIKE '%adventure time%';


-- lower to make skip case issues, trim to skip whitespace issues
UPDATE shows SET title = 'New Title' WHERE LOWER(TRIM(title)) LIKE '%title%'
OR WHERE title LIKE 'tit%';

SELECT title FROM shows WHERE LOWER(TRIM(title)) LIKE '%title%';

-- '' to escape apostrophe
sqlite> UPDATE shows SET title = 'Grey''s Anatomy' WHERE LOWER(TRIM(title)) LIKE '%grey''s anatomy';
