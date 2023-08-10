import csv
from cs50 import SQL
from os import path

FILENAME = "students.csv"
DBNAME = "new_roster.db"


def main():

    students = []

    try:
        # Read data from csv file
        with open(FILENAME , "r") as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                students.append(row)
    except:
        print(f"The file {FILENAME} doesn't exist.")
        return 1

    # Open database
    if path.exists(DBNAME):
        db = SQL("sqlite:///new_roster.db")
    else:
        print(f"The file {DBNAME} doesn't exist.")
        return 2



    # Insert data into the database
    for student in students:
        db.execute(
            "INSERT  OR IGNORE INTO students(id, student_name) VALUES(?, ?)",
            student["id"],
            student["student_name"]
        )
        db.execute(
            "INSERT  OR IGNORE INTO houses(house, head) VALUES(?, ?)",
            student["house"],
            student["head"]
        )
        db.execute(
            "INSERT  OR IGNORE INTO house_assignments(student_id, house_id) VALUES(?, ?)",
            student["id"],
            student["house"]
        )

    # Print out that operation completed
    print("Insertion successfully completed")



if __name__ == "__main__":
    main()