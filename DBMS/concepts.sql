-- CREATING TABLE
CREATE TABLE Company (
    companyId INT PRIMARY KEY AUTO_INCREMENT,
    companyName VARCHAR(50) NOT NULL,
    country VARCHAR(50),
    establishedYear YEAR,
    isActive BOOLEAN DEFAULT TRUE
);

CREATE TABLE ClothingBrands (
    brandId INT PRIMARY KEY AUTO_INCREMENT,
    brandName VARCHAR(30) NOT NULL,
    price DECIMAL(10, 2) CHECK(price > 0),
    brandDesc VARCHAR(30),
    isActive BOOLEAN DEFAULT TRUE,
    manufacturedBy INT REFERENCES Company(companyId)
);

INSERT INTO Company (companyName, country, establishedYear, isActive) 
VALUES 
    ('Adidas', 'Germany', 1949, TRUE),
    ('Puma', 'Germany', 1948, TRUE),
    ('Zara', 'Spain', 1974, TRUE),
    ('H&M', 'Sweden', 1947, TRUE);

INSERT INTO ClothingBrands (brandName, price, brandDesc, isActive, manufacturedBy) 
VALUES 
    ('Nike Air', 12000, 'Nike sports shoes', TRUE, 1),
    ('Adidas Originals', 15000, 'Adidas lifestyle brand', TRUE, 2),
    ('Puma RS-X', 10000, 'Puma running shoes', TRUE, 3),
    ('Zara Casual', 5000, 'Zara casual wear', TRUE, 4),
    ('H&M Basics', 4000, 'H&M everyday wear', TRUE, 5);


-- ALTERING TABLE
ALTER TABLE company
ADD COLUMN networth INT;

ALTER TABLE company
MODIFY COLUMN networth DECIMAL(10, 2) CHECK(networth >= 0) DEFAULT 0;

ALTER TABLE company
RENAME COLUMN networth TO netWorth;

ALTER TABLE company RENAME TO Company;

ALTER TABLE Company
ADD CONSTRAINT chk_establishedYear CHECK (establishedYear < 2025);

ALTER TABLE Company
ADD CONSTRAINT chk_establishedYear_2 CHECK (establishedYear < 2019);

ALTER TABLE company
DROP CONSTRAINT chk_establishedYear_2;

-- Operators

-- 1. Arithmatic

-- You can do this too...
SELECT 10 + 2;

SELECT price, price * 1.2 AS IncreasedPrice
FROM ClothingBrands;

-- AGG FUNCTIONS
SELECT SUM(price) as TotalPrice from clothingbrands;

USE semester_4;
SELECT * FROM clothingbrands;
