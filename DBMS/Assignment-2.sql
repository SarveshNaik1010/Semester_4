CREATE TABLE Instructor (
    instructorid INT PRIMARY KEY,
    instructorname VARCHAR(100),
    instructorcity VARCHAR(100),
    specialization VARCHAR(100)
);

CREATE TABLE Students (
    studentid INT PRIMARY KEY,
    studentname VARCHAR(100),
    instructorid INT,
    studentcity VARCHAR(100),
    FOREIGN KEY (instructorid) REFERENCES Instructor(instructorid)
);

INSERT INTO Instructor (instructorid, instructorname, instructorcity, specialization) VALUES 
(1, 'Dr. Smith', 'New York', 'Computer Science'),
(2, 'Prof. Johnson', 'Los Angeles', 'Mathematics'),
(3, 'Dr. Williams', 'Chicago', 'Physics'),
(4, 'Prof. Warner', 'LA', 'Computer Science');

INSERT INTO Students (studentid, studentname, instructorid, studentcity) 
VALUES 
(101, 'Alice Brown', 1, 'New York'),
(102, 'Bob Johnson', 2, 'Los Angeles'),
(103, 'Charlie Davis', 1, 'New York'),
(104, 'Diana Evans', 3, 'Chicago'),
(105, 'Ethan Green', 2, 'Los Angeles'),
(106, 'Fiona Harris', 3, 'Chicago'),
(107, 'George Martin', 1, 'New York'),
(108, 'Hannah Scott', 2, 'Los Angeles'),
(109, 'Ian Turner', 3, 'Chicago'),
(110, 'Jack White', 1, 'New York'),
(111, 'Joshep Diva', NULL, 'New York');


-- Find the instructor of each student.
SELECT 
    s.studentname, 
    i.instructorname
FROM Students s
JOIN Instructor i ON s.instructorid = i.instructorid;

-- Find the student who is not having any instructor.
SELECT * FROM students
WHERE instructorid IS NULL;

-- Find the student who is not having any instructor as well as instructor who is not having student.
SELECT * FROM students
WHERE instructorid IS NULL;

SELECT * FROM instructor i
LEFT JOIN students s ON i.instructorid = s.instructorid
WHERE s.studentid IS NULL;


-- Find the students whose instructor’s specialization is computer.
SELECT * FROM students s
WHERE instructorid = (SELECT instructorid from instructor WHERE s.instructorid = instructorid AND specialization = "Computer Science");

-- Create a view containing total number of students whose instructor belongs to "Chicago”.
SELECT * FROM students s
WHERE instructorid IN (SELECT instructorid FROM instructor WHERE instructorid = s.instructorid AND instructorcity = "Chicago");



-- Corrected Departments Table
CREATE TABLE departments (
    department_id INT AUTO_INCREMENT PRIMARY KEY,
    department_name VARCHAR(30) NOT NULL,
    location_id INT DEFAULT NULL
);

-- Corrected Employees Table
CREATE TABLE employees (
    employee_id INT AUTO_INCREMENT PRIMARY KEY,
    first_name VARCHAR(20) DEFAULT NULL,
    last_name VARCHAR(25) NOT NULL,
    email VARCHAR(100) NOT NULL,
    phone_number VARCHAR(20) DEFAULT NULL,
    hire_date DATE NOT NULL,
    job_id INT NOT NULL,
    salary DECIMAL(8,2) NOT NULL,
    manager_id INT DEFAULT NULL,
    department_id INT DEFAULT NULL,
    FOREIGN KEY (department_id) REFERENCES departments(department_id) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (manager_id) REFERENCES employees(employee_id) ON DELETE SET NULL ON UPDATE CASCADE
);
    
-- Insert sample data into departments
INSERT INTO departments (department_name, location_id) VALUES
('Engineering', 1),
('Marketing', 2),
('Human Resources', 3),
('Finance', 4),
('IT Support', 5);

-- Insert sample data into employees
INSERT INTO employees (first_name, last_name, email, phone_number, hire_date, job_id, salary, manager_id, department_id) VALUES
('John', 'Doe', 'john.doe@email.com', '123-456-7890', '2020-06-15', 101, 75000.00, NULL, 1), 
('Jane', 'Smith', 'jane.smith@email.com', '987-654-3210', '2019-09-23', 102, 68000.00, 1, 1), 
('Robert', 'Brown', 'robert.brown@email.com', '555-123-4567', '2021-02-18', 103, 72000.00, 1, 1), 
('Emily', 'Davis', 'emily.davis@email.com', '111-222-3333', '2022-03-12', 104, 60000.00, NULL, 2), 
('Michael', 'Wilson', 'michael.wilson@email.com', '444-555-6666', '2020-07-29', 105, 58000.00, 4, 2),
('Sarah', 'Johnson', 'sarah.johnson@email.com', '777-888-9999', '2021-11-05', 106, 65000.00, NULL, 3), 
('David', 'Miller', 'david.miller@email.com', '333-444-5555', '2023-01-17', 107, 62000.00, 6, 3),
('Anna', 'Taylor', 'anna.taylor@email.com', '999-888-7777', '2022-09-10', 108, 70000.00, NULL, 4), 
('James', 'Anderson', 'james.anderson@email.com', '666-777-8888', '2018-05-30', 109, 71000.00, 8, 4),
('Olivia', 'Martinez', 'olivia.martinez@email.com', '555-666-7777', '2023-06-20', 110, 67000.00, NULL, 5), 
('Daniel', 'Harris', 'daniel.harris@email.com', '222-333-4444', '2019-12-14', 111, 64000.00, 10, 5);


-- Find all employees who locate in the location with the id 1700
SELECT * FROM employees
WHERE department_id IN (SELECT department_id from departments WHERE location_id = 1700);

-- Find all employees who do not locate at the location 1700
SELECT * FROM employees
WHERE department_id NOT IN (SELECT department_id from departments WHERE location_id = 1700);

-- Finds the employees who have the highest salary
SELECT * FROM employees
WHERE salary = (SELECT MAX(salary) from employees);

-- Finds all employees who salaries are greater than the average salary of all employees
SELECT * FROM employees
WHERE salary > (SELECT AVG(salary) from employees);

-- Finds all departments which have at least one employee with the salary is greater than 10,000
SELECT * from departments
WHERE department_id IN (SELECT department_id FROM employees WHERE salary > 70000);

-- Finds all departments that do not have any employee with the salary greater than 10,000
SELECT * from departments
WHERE department_id NOT IN (SELECT department_id FROM employees WHERE salary > 70000);

-- Finds all employees whose salaries are greater than the lowest salary of every department
SELECT * FROM employees
WHERE salary > ANY (
    SELECT MIN(salary) FROM employees GROUP BY department_id
);

-- Finds all employees whose salaries are greater than or equal to the highest salary of every department
SELECT * FROM employees
WHERE salary > ANY (
    SELECT MAX(salary) FROM employees GROUP BY department_id
);

-- Finds the salaries of all employees, their average salary, and the difference between the salary of each employee and the average salary
select employee_id, 
    first_name, 
    last_name, 
    salary, 
    (SELECT AVG(salary) FROM employees) AS avg_salary,
    salary - (SELECT AVG(salary) FROM employees) AS diff_salary
FROM employees;
