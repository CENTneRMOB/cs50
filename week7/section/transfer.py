from cs50 import SQL

db = SQL("sqlite:///roster.db")

houses = db.execute("select * from houses;")

students = db.execute("select id, house from students;")

for student in students:
    for house in houses:
        if student["house"] == house["house"]:
            db.execute("INSERT INTO assignments (student_id, house_id) VALUES (?, ?)", student["id"], house["id"])

# assignments = db.execute("select * from assignments;")

# print(assignments)

# print(houses)
# print(students)