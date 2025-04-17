/* -------------------------------------------------------------------------- */
/*                                   PART 1                                   */
/* -------------------------------------------------------------------------- */
-- Creating branch table
CREATE TABLE branch (
    branch_name VARCHAR(50) PRIMARY KEY,
    branch_city VARCHAR(50) NOT NULL,
    assets DECIMAL(15, 2) CHECK (assets >= 0)
);

-- Creating customer table
CREATE TABLE customer (
    cust_name VARCHAR(50) PRIMARY KEY,
    cust_street VARCHAR(100),
    cust_city VARCHAR(50)
);

-- Creating account table
CREATE TABLE account (
    acc_no INT PRIMARY KEY,
    branch_name VARCHAR(50),
    balance DECIMAL(10, 2) NOT NULL CHECK (balance >= 0),
    FOREIGN KEY (branch_name) REFERENCES branch(branch_name)
);

-- Creating depositor table
CREATE TABLE depositor (
    cust_name VARCHAR(50),
    acc_no INT,
    PRIMARY KEY (cust_name, acc_no),
    FOREIGN KEY (cust_name) REFERENCES customer(cust_name),
    FOREIGN KEY (acc_no) REFERENCES account(acc_no)
);

-- Creating loan table
CREATE TABLE loan (
    loan_no INT PRIMARY KEY,
    branch_name VARCHAR(50),
    amount DECIMAL(10, 2) NOT NULL CHECK (amount > 0),
    FOREIGN KEY (branch_name) REFERENCES branch(branch_name)
);

-- Creating borrower table
CREATE TABLE borrower (
    cust_name VARCHAR(50),
    loan_no INT,
    PRIMARY KEY (cust_name, loan_no),
    FOREIGN KEY (cust_name) REFERENCES customer(cust_name),
    FOREIGN KEY (loan_no) REFERENCES loan(loan_no)
);

-- Insert into branch table
INSERT INTO branch VALUES 
('Main', 'New York', 5000000.00),
('North', 'Chicago', 3000000.00),
('South', 'Houston', 2000000.00),
('West', 'Los Angeles', 4000000.00),
('East', 'Boston', 3500000.00);

-- Insert into customer table
INSERT INTO customer VALUES 
('Alice', '12 Park Ave', 'New York'),
('Bob', '43 Lake St', 'Chicago'),
('Charlie', '77 Hill Rd', 'Houston'),
('David', '88 Elm St', 'Los Angeles'),
('Eva', '99 Ocean Dr', 'Boston'),
('Frank', '10 Pine St', 'New York'),
('Grace', '22 Sunset Blvd', 'Los Angeles');

-- Insert into account table
INSERT INTO account VALUES 
(1001, 'Main', 15000.00),
(1002, 'North', 22000.00),
(1003, 'South', 18000.00),
(1004, 'West', 30000.00),
(1005, 'Main', 5000.00),
(1006, 'East', 12000.00),
(1007, 'North', 8000.00);

-- Insert into depositor table
INSERT INTO depositor VALUES 
('Alice', 1001),
('Alice', 1005),
('Bob', 1002),
('Charlie', 1003),
('David', 1004),
('Eva', 1006),
('Frank', 1005),
('Grace', 1007);

-- Insert into loan table
INSERT INTO loan VALUES 
(501, 'Main', 30000.00),
(502, 'North', 25000.00),
(503, 'South', 27000.00),
(504, 'West', 22000.00),
(505, 'East', 35000.00),
(506, 'Main', 15000.00);

-- Insert into borrower table
INSERT INTO borrower VALUES 
('Alice', 501),
('Bob', 502),
('Charlie', 503),
('David', 504),
('Eva', 505),
('Alice', 506),
('Frank', 506);

-- 1. Find the names of all branches in loan relation.
SELECT DISTINCT branch_name FROM loan;

-- 2. Find all loan numbers for loans made at New York Branch with loan amount > 12000.
SELECT loan_no from loan
WHERE branch_name = "Main" AND amount > 12000;

-- 3. Find all customers who have a loan from bank. Find their names,loan_no and loan amount.
SELECT 
    borrower.cust_name, 
    loan.loan_no, 
    loan.amount
FROM 
    borrower
JOIN 
    loan ON borrower.loan_no = loan.loan_no;


-- 4. List all customers in alphabetical order who have loan from Shivaji nagar branch.
SELECT DISTINCT borrower.cust_name FROM borrower
WHERE loan_no IN (SELECT loan_no from loan where branch_name = "Main")
ORDER BY borrower.cust_name;


-- 5. Find all customers who have an account or loan or both at bank.





