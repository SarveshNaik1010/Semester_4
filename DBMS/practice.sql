-- DEFINING A SCHEMA
CREATE TABLE college (
    collegeId INT PRIMARY KEY NOT NULL,
    collegeName VARCHAR(50) NOT NULL,
    city VARCHAR(20) DEFAULT "Pune",
    ranking INT CHECK (ranking >= 1)
);

INSERT INTO college (collegeId, collegeName, city, ranking) VALUES
( 1, "VU", "Pune", 24 ),
( 2, "VJIT", "Mumbai", 3 ),
( 3, "IIT Bombay", "Mumbai", 1 );

INSERT INTO college (collegeId, collegeName, city, ranking) VALUES
(4, "COEP", "Pune", 2),
(5, "MIT WPU", "Pune", 10),
(6, "IIT Delhi", "Delhi", 1),
(7, "NIT Trichy", "Tiruchirappalli", 8),
(8, "IIIT Hyderabad", "Hyderabad", 5),
(9, "BITS Pilani", "Pilani", 4),
(10, "Jadavpur University", "Kolkata", 7),
(11, "IIT Madras", "Chennai", 1),
(12, "NIT Surathkal", "Mangalore", 6),
(13, "Delhi Technological University", "Delhi", 9);

select AVG(ranking) from college
WHERE city = 'Pune';