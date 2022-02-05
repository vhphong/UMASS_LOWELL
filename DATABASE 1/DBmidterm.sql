CREATE TABLE students(
    id      INT NOT NULL,
    name    VARCHAR(30) NOT NULL,
    gradelevel  VARCHAR(30) DEFAULT '',
    PRIMARY KEY (id)
);

CREATE TABLE class(
    title   VARCHAR(30),
    year    INT,
    instructor  VARCHAR(30),
    dept    VARCHAR(10)
);

CREATE TABLE taken(
    id      INT NOT NULL,
    title   VARCHAR(30),
    year    INT,
    score   FLOAT
);


INSERT INTO students VALUES (111, 'Bob', 'Freshmen');
INSERT INTO students VALUES (222, 'Joe', 'Sophomore');
INSERT INTO students VALUES (333, 'Sue', 'Junior');
INSERT INTO students VALUES (444, 'Bob', 'Senior');

INSERT INTO class VALUES 
('Algorithms', 2018, 'Turing', 'CS'),
('Algorithms', 2019, 'Codd', 'CS'),
('Database', 2018, 'Codd', 'CS'),
('OS', 2019, 'Turing', 'CS'),
('Calculus', 2018, 'Fields', 'Math'),
('Statistics', 2019, 'Fields', 'Math');

INSERT INTO taken VALUES
(111, 'Algorithms', 2019, 70),
(222, 'Algorithms', 2018, 90),
(333, 'Calculus', 2018, 80),
(333, 'Algorithms', 2019, 80),
(333, 'OS', 2019, 80),
(333, 'Database', 2018, 80),
(444, 'Algorithms', 2018, 50),
(444, 'Algorithms', 2019, 100),
(444, 'Calculus', 2018, 100),
(444, 'Statistics', 2019, 100);