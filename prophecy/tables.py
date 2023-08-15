import csv
from cs50 import SQL

def studentlist(students, student):
    if not any(student in studentlist["student_name"] for studentlist in students):
        students.append({"student_name" : student})

def houselist(houses, house, head):
    if not any(house in houselist["house"] for houselist in houses):
        houses.append({"house" : house, "head" : head})

def relationshiplist(relationships, student, house):
    relationships.append({"student_name" : student, "house" : house})

students = []
houses = []
relationships = []

with open("students.csv", "r") as file:
    buffer = csv.DictReader(file)
    for row in buffer:
        # print(row)
        student = row["student_name"]
        house = row["house"]
        head = row["head"]

        studentlist(students, student)
        houselist(houses, house, head)
        relationshiplist(relationships, student, house)

    # print(relationships)

# Open database
db = SQL("sqlite:///roster.db")

# db.execute("CREATE TABLE newstudents (id INTEGER, student_name TEXT, PRIMARY KEY(id)")
# db.execute("CREATE TABLE newhouses (id INTEGER, house TEXT, head TEXT, PRIMARY KEY(id)")
# db.execute("CREATE TABLE relationship (id INTEGER, student_name TEXT, house TEXT, PRIMARY KEY(id)")

for student in students:
    db.execute("INSERT INTO newstudents (student_name) VALUES(?)", student["student_name"])

for house in houses:
    db.execute("INSERT INTO newhouses (house, head) VALUES(?, ?)", house["house"], house["head"])

for relationship in relationships:
    db.execute("INSERT INTO relationship (student_name, house) VALUES(:student_name, :house)", student_name = relationship["student_name"], house = relationship["house"])
