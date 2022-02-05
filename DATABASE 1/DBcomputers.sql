CREATE DATABASE computers;
USE computers;
CREATE TABLE product(
	maker VARCHAR(20),
	model INT,
	type VARCHAR(20),
	PRIMARY KEY (model)
);

CREATE TABLE pc(
	model INT,
	speed FLOAT,
	ram INT,
	hd INT,
	price FLOAT,
	PRIMARY KEY (model)
);

CREATE TABLE laptop(
	model INT,
	speed FLOAT,
	ram INT,
	hd INT,
	screen FLOAT,
	price FLOAT,
	PRIMARY KEY (model)
);

CREATE TABLE printer(
	model INT,
	color BOOLEAN,
	type VARCHAR(20),
	price FLOAT,
	PRIMARY KEY	(model)
);

INSERT INTO product VALUES
('A',1001,'pc'),
('A',1002,'pc'),
('A',1003,'pc'),
('A',2004,'laptop'),
('A',2005,'laptop'),
('A',2006,'laptop'),
('B',1004,'pc'),
('B',1005,'pc'),
('B',1006,'pc'),
('B',2007,'laptop'),
('c',1007,'pc'),
('D',1008,'pc'),
('D',1009,'pc'),
('D',1010,'pc'),
('D',3004,'printer'),
('D',3005,'printer'),
('E',1011,'pc'),
('E',1012,'pc'),
('E',1013,'pc'),
('E',2001,'laptop'),
('E',2002,'laptop'),
('E',2003,'laptop'),
('E',3001,'printer'),
('E',3002,'printer'),
('E',3003,'printer'),
('F',2008,'laptop'),
('F',2009,'laptop'),
('G',2010,'laptop'),
('H',3006,'printer'),
('H',3007,'printer')
;

INSERT INTO pc VALUES
(1001, 2.66, 1024, 250, 21.14),
(1002, 2.1, 512, 250, 995),
(1003, 1.42, 512, 80, 478),
(1004, 2.8, 1024, 250, 649),
(1005, 3.2, 512, 250, 630),
(1006, 3.2, 1024, 320, 1049),
(1007, 2.2, 1024, 200, 510),
(1008, 2.2, 2048, 250, 770),
(1009, 2, 1024, 250, 650),
(1010, 2.8, 2048, 300, 770),
(1011, 1.86, 2048, 160, 959),
(1012, 2.8, 1024, 160, 649),
(1013, 3.06, 512, 80, 529)
;

INSERT INTO laptop VALUES
(2001, 2, 2048, 240, 20.1, 3673),
(2002, 1, 73, 1024, 80, 17),
(2003, 1.8, 512, 60, 15.4, 549),
(2004, 2, 512, 60, 13.3, 1150),
(2005, 2.16, 1024, 120, 17, 2500),
(2006, 2, 2048, 80, 15.4, 1700),
(2007, 1.83, 1024, 120, 13.3, 1429),
(2008, 1.6, 1024, 100, 15.4, 900),
(2009, 1.6, 512, 80, 14.1, 680),
(2010, 2, 2048, 160, 15.4, 2300)
;

INSERT INTO printer VALUES
(3001, TRUE, 'ink-jet', 99),
(3002, FALSE, 'laser', 239),
(3003, TRUE, 'laser', 899),
(3004, TRUE, 'ink-jet', 120),
(3005, FALSE, 'laser', 120),
(3006, TRUE, 'ink-jet', 100),
(3007, TRUE, 'laser', 200)
;
