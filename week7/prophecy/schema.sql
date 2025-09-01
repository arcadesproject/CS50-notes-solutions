-- initial schema
CREATE TABLE students (
    id INTEGER,
    student_name TEXT,
    house TEXT,
    head TEXT,
    PRIMARY KEY(id)
);
-- to delete current students table
DROP TABLE students

-- new students table
CREATE TABLE students (
        id INTEGER NOT NULL,
        student_name VARCHAR(50) NOT NULL,
        PRIMARY KEY (id)
);

-- new houses table
CREATE TABLE houses (
        id INTEGER NOT NULL,
        house_name VARCHAR(50) NOT NULL,
        head VARCHAR(50),
        PRIMARY KEY (id),
        UNIQUE (house_name),
        UNIQUE (head)
);

-- new house assignments table
CREATE TABLE house_assignments (
        id INTEGER NOT NULL,
        student_id INTEGER NOT NULL,
        house_id INTEGER,
        PRIMARY KEY (id),
        CONSTRAINT uix_student UNIQUE (student_id),
        FOREIGN KEY(student_id) REFERENCES students (id) ON DELETE CASCADE ON UPDATE CASCADE,
        FOREIGN KEY(house_id) REFERENCES houses (id) ON DELETE CASCADE ON UPDATE CASCADE
);
