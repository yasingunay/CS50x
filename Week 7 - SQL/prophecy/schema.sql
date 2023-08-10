CREATE TABLE IF NOT EXISTS students(
    id INTEGER NOT NULL,
    student_name TEXT,
    PRIMARY KEY(id)
    );

CREATE TABLE IF NOT EXISTS houses(
    house TEXT,
    head TEXT,
    PRIMARY KEY(house)
    );

CREATE TABLE IF NOT EXISTS house_assignments(
    student_id INTEGER NOT NULL,
    house_id INTEGER NOT NULL,
    FOREIGN KEY(student_id) REFERENCES students(id),
    FOREIGN KEY(house_id) REFERENCES houses(house)
    );


-- Some useful sql queries
SELECT * FROM students;


SELECT students.id, students.student_name, houses.house
FROM students
INNER JOIN house_assignments ON students.id = house_assignments.student_id
INNER JOIN houses ON houses.house = house_assignments.house_id
ORDER BY students.id;



-- IN SQL there is no way to delete spesific columns so we need to do following steps to do that:
-- Create a new_student table
CREATE TABLE new_students(id INTEGER NOT NULL, student_name TEXT, PRIMARY KEY(id));

-- Copy only student ids and student names from old students table to new_student table
INSERT INTO new_students(id, student_name) SELECT id, student_name FROM students;

-- Delete old students table
DROP TABLE students;

--Rename the new_students table to the original table name (students)
ALTER TABLE new_students RENAME TO students;
