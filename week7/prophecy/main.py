"""
sqlite3 Version
"""

# import csv, sqlite3

# # initialize roster db
# conn = sqlite3.connect('roster.db')
# cursor = conn.cursor()

# # populate houses, only 4 so don't do it looping over all rows
# houses = [
#     {"house_name": "Gryffindor", "head": "Minerva McGonagall"},
#     {"house_name": "Hufflepuff", "head": "Pomona Sprout"},
#     {"house_name": "Ravenclaw", "head": "Filius Flitwick"},
#     {"house_name": "Slytherin", "head": "Severus Snape"}
# ]

# for house in houses:
#     cursor.execute(
#         "INSERT INTO houses (house_name, head) VALUES (?, ?)",
#         (house["house_name"], house["head"])
#     )

# # add all students in csv to students table
# def add_students():
#     with open('students.csv', newline='') as students_file:
#         reader = csv.DictReader(students_file)
#         for row in reader:
#             cursor.execute("INSERT INTO students (id, student_name) VALUES (?, ?)",
#                             (row['id'], row['student_name']))

# add_students()

# conn.commit()
# conn.close()

"""
SQLAlchemy version
With added idempotency
Composite student_id for house_assignments
"""

import os
import csv
from sqlalchemy import create_engine, Column, Integer, String, ForeignKey, UniqueConstraint
from sqlalchemy.orm import declarative_base, relationship, sessionmaker
from sqlalchemy.engine import Engine
# use dialects.postgres.insert for postgres etc
from sqlalchemy.dialects.sqlite import insert as sqlite_insert
from sqlalchemy import event

Base = declarative_base()

# Enable foreign key constraints in SQLite
@event.listens_for(Engine, "connect")
def enforce_foreign_keys(dbapi_connection, connection_record):
    cursor = dbapi_connection.cursor()
    cursor.execute("PRAGMA foreign_keys=ON")
    cursor.close()

class Student(Base):
    __tablename__ = 'students'
    id = Column(Integer, primary_key=True)
    student_name = Column(String(50), nullable=False)

    assignments = relationship("HouseAssignment", back_populates="student", cascade="all, delete-orphan")

class House(Base):
    __tablename__ = 'houses'
    id = Column(Integer, primary_key=True)
    house_name = Column(String(50), nullable=False, unique=True)
    head = Column(String(50), unique=True)

    assignments = relationship("HouseAssignment", back_populates="house", cascade="all, delete")

class HouseAssignment(Base):
    __tablename__ = 'house_assignments'
    id = Column(Integer, primary_key=True, autoincrement=True)
    student_id = Column(Integer, ForeignKey('students.id', ondelete="CASCADE", onupdate="CASCADE"), nullable=False)
    house_id = Column(Integer, ForeignKey('houses.id', ondelete="CASCADE", onupdate="CASCADE"))

    # explain uniqueness of student_id, composite, easier update later if needed
    __table_args__ = (UniqueConstraint('student_id', name='uix_student'),)

    student = relationship("Student", back_populates="assignments")
    house = relationship("House", back_populates="assignments")

# idempotent upsert pattern
def insert_houses(session, house_data):
    for data in house_data:
        stmt = sqlite_insert(House).values(**data)
        stmt = stmt.on_conflict_do_update(
            index_elements=['house_name'],
            set_={'head': stmt.excluded.head}
        )
        session.execute(stmt)
    # So can query houses
    session.flush()


# Insert students from CSV
def add_students(session):
    # lookup of houses
    house_lookup = {house.house_name: house for house in session.query(House).all()}

    with open('students.csv', newline='') as students_file:
        reader = csv.DictReader(students_file)
        for row in reader:
            student = session.get(Student, int(row['id']))
            # avoid duplicate
            if not student:
                student = Student(id=int(row['id']), student_name=row['student_name'])
                session.add(student)
            else:
                student.student_name = row['student_name']  # update if needed

            # assign house
            house = house_lookup.get(row['house'])
            if house:
            # avoid duplicate assignment
                existing_assignment = session.query(HouseAssignment).filter_by(student_id=student.id).first()
                if not existing_assignment:
                    session.add(HouseAssignment(student=student, house=house))
                elif existing_assignment.house_id != house.id:
                    existing_assignment.house = house  # update assignment

            else:
                print(f"Warning: House '{row['house']}' not found for student {row['student_name']}")

def main():
    # create db, alembic
    db_url = os.getenv('DATABASE_URL', 'sqlite:///roster.db')
    engine = create_engine(db_url, echo=False)
    Base.metadata.create_all(engine)

    Session = sessionmaker(bind=engine)
    with Session() as session:
        insert_houses(session, [
            {"house_name":"Gryffindor","head":"Minerva McGonagall"},
            {"house_name":"Hufflepuff","head":"Pomona Sprout"},
            {"house_name":"Ravenclaw","head":"Filius Flitwick"},
            {"house_name":"Slytherin","head":"Severus Snape"}
        ])
        add_students(session)
        session.commit()

if __name__ == '__main__':
    main()
