DROP TABLE course;
DROP TABLE teaches;
DROP TABLE instructor;
DROP TABLE takes;
DROP TABLE student;

CREATE TABLE course (
	course_id int NOT NULL,
	title  varchar(30),
	dept_name varchar(30),
	credits int,
	CONSTRAINT PK_course PRIMARY KEY (course_id)
);

CREATE TABLE instructor (
	ID int NOT NULL,
	name  varchar(60),
	dept_name varchar(30),
	salary int,
	CONSTRAINT PK_instructor PRIMARY KEY (ID)
);

CREATE TABLE teaches (
	ID int NOT NULL,
	course_id int NOT NULL,
	sec_id int NOT NULL,
	semester varchar(20) NOT NULL,
	year int NOT NULL,
	CONSTRAINT PK_teaches PRIMARY KEY (ID, course_id, sec_id, semester, year),
	CONSTRAINT FK_teaches FOREIGN KEY (ID) REFERENCES instructor(ID)
);

CREATE TABLE student (
	ID int NOT NULL,
	name varchar(30),
	dept_name varchar(30),
	tot_cred int,
	CONSTRAINT PK_student PRIMARY KEY (ID)
);

CREATE TABLE takes (
	ID int NOT NULL,
	course_id int NOT NULL,
	sec_id int NOT NULL,
	semester varchar(20),
	year int NOT NULL,
	grade varchar(5),
	CONSTRAINT PK_takes PRIMARY KEY (ID, course_id, sec_id, semester, year),
	CONSTRAINT FK_takes FOREIGN KEY (ID) REFERENCES student(ID)
);