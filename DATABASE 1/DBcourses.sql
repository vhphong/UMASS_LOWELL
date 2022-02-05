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

-----------------------------------------------------------------------------------------

delete from takes;
delete from student;
delete from teaches;
delete from instructor;
delete from course;

insert into course values('11', 'International Finance', 'Comp. Sci.', 3);
insert into course values('12', 'Greek Tragedy', 'Statistics', 4);
insert into course values('13', 'Greek Tragedy', 'Comp. Sci.', 4);
insert into course values('14', 'Virology', 'Statistics', 3);
insert into course values('15', 'Compiler Design', 'Elec. Eng.', 3);
insert into course values('16', 'Geology', 'Statistics', 3);
insert into course values('17', 'Mobile Computing', 'Physics', 3);
insert into course values('18', 'Surfing', 'Statistics', 3);
insert into course values('19', 'International Trade', 'Marketing', 3);
insert into course values('20', 'Graph Theory', 'Comp. Sci.', 3);
insert into course values('21', 'Visual BASIC', 'Comp. Sci.', 4);
insert into course values('22', 'How to Groom your Cat', 'Accounting', 3);
insert into course values('23', 'Rock and Roll', 'Marketing', 3);
insert into course values('24', 'FOCAL Programming', 'Comp. Sci.', 4);
insert into course values('25', 'Calculus', 'Statistics', 4);
insert into course values('26', 'Environmental Law', 'Math', 4);
insert into course values('27', 'The Beatles', 'Math', 3);


insert into instructor values('1', 'McKinnon', 'Comp. Sci.', 194333.99);
insert into instructor values('2', 'Pingr', 'Statistics', 49303.62);
insert into instructor values('3', 'Mird', 'Marketing', 119921.41);
insert into instructor values('4', 'Luo', 'Comp. Sci.', 188791.45);
insert into instructor values('5', 'Konstantinides', 'Comp. Sci.', 132570.50);
insert into instructor values('6', 'Levine', 'Elec. Eng.', 39805.83);
insert into instructor values('7', 'Shuming', 'Physics', 108011.81);
insert into instructor values('8', 'Queiroz', 'Math', 45538.32);
insert into instructor values('9', 'Sullivan', 'Elec. Eng.', 90038.09);
insert into instructor values('10', 'Bertolino', 'Comp. Sci.', 151647.57);
insert into instructor values('91', 'Sullivan', 'Elec. Eng.', 90038.09);
insert into instructor values('92', 'Bertolino', 'Elec. Eng.', 90038.09);


insert into teaches values('1', '11', '1', 'Spring', 2014);
insert into teaches values('1', '16', '1', 'Spring', 2007);
insert into teaches values('7', '14', '1', 'Spring', 2011);
insert into teaches values('7', '12', '1', 'Fall', 2013);
insert into teaches values('9', '13', '1', 'Spring', 2016);
insert into teaches values('2', '15', '1', 'Fall', 2008);
insert into teaches values('3', '15', '1', 'Fall', 2006);
insert into teaches values('3', '27', '1', 'Fall', 2012);
insert into teaches values('5', '26', '1', 'Spring', 2014);
insert into teaches values('3', '25', '1', 'Spring', 2016);
insert into teaches values('8', '19', '1', 'Fall', 2012);
insert into teaches values('6', '22', '1', 'Spring', 2016);
insert into teaches values('7', '20', '2', 'Fall', 2013);
insert into teaches values('5', '17', '1', 'Fall', 2006);
insert into teaches values('3', '14', '1', 'Fall', 2012);
insert into teaches values('5', '17', '1', 'Spring', 2012);
insert into teaches values('9', '27', '1', 'Spring', 2010);
insert into teaches values('2', '15', '1', 'Spring', 2014);
insert into teaches values('4', '13', '2', 'Spring', 2012);
insert into teaches values('6', '16', '1', 'Fall', 2009);
insert into teaches values('5', '18', '1', 'Spring', 2007);
insert into teaches values('10', '12', '3', 'Spring', 2016);
insert into teaches values('9', '27', '1', 'Fall', 2014);
insert into teaches values('8', '14', '1', 'Fall', 2013);
insert into teaches values('7', '18', '2', 'Spring', 2013);
insert into teaches values('6', '13', '1', 'Spring', 2010);
insert into teaches values('5', '19', '1', 'Spring', 2010);
insert into teaches values('4', '17', '2', 'Fall', 2009);
insert into teaches values('3', '18', '1', 'Fall', 2007);
insert into teaches values('2', '24', '1', 'Fall', 2009);
insert into teaches values('1', '25', '1', 'Fall', 2015);
insert into teaches values('10', '26', '1', 'Spring', 2015);
insert into teaches values('9', '27', '1', 'Spring', 2012);
insert into teaches values('7', '11', '1', 'Fall', 2006);
insert into teaches values('4', '12', '1', 'Fall', 2014);
insert into teaches values('6', '13', '1', 'Spring', 2006);
insert into teaches values('5', '14', '2', 'Fall', 2006);
insert into teaches values('4', '15', '1', 'Spring', 2006);
insert into teaches values('2', '16', '1', 'Fall', 2009);
insert into teaches values('10', '17', '1', 'Fall', 2009);
insert into teaches values('10', '18', '1', 'Fall', 2006);
insert into teaches values('6', '19', '1', 'Fall', 2007);
insert into teaches values('4', '20', '1', 'Spring', 2015);
insert into teaches values('3', '21', '1', 'Fall', 2012);
insert into teaches values('2', '22', '1', 'Spring', 2008);
insert into teaches values('7', '23', '1', 'Spring', 2016);
insert into teaches values('9', '24', '1', 'Spring', 2009);
insert into teaches values('9', '25', '1', 'Spring', 2016);
insert into teaches values('4', '26', '1', 'Fall', 2009);
insert into teaches values('2', '27', '2', 'Spring', 2016);
insert into teaches values('2', '22', '1', 'Fall', 2011);
insert into teaches values('4', '21', '1', 'Spring', 2006);
insert into teaches values('3', '20', '1', 'Fall', 2014);
insert into teaches values('8', '19', '1', 'Fall', 2015);
insert into teaches values('5', '18', '1', 'Fall', 2007);
insert into teaches values('7', '17', '1', 'Fall', 2016);
insert into teaches values('8', '16', '1', 'Fall', 2016);
insert into teaches values('5', '15', '1', 'Fall', 2016);
insert into teaches values('10', '14', '1', 'Fall', 2010);
insert into teaches values('10', '13', '2', 'Fall', 2010);
insert into teaches values('2', '12', '1', 'Spring', 2007);
insert into teaches values('3', '11', '1', 'Spring', 2010);
insert into teaches values('8', '12', '1', 'Spring', 2011);
insert into teaches values('5', '13', '1', 'Fall', 2010);
insert into teaches values('6', '14', '1', 'Fall', 2007);
insert into teaches values('7', '15', '1', 'Spring', 2013);
insert into teaches values('8', '16', '2', 'Fall', 2012);
insert into teaches values('9', '17', '2', 'Fall', 2012);
insert into teaches values('10', '18', '1', 'Fall', 2011);
insert into teaches values('1', '19', '2', 'Fall', 2007);
insert into teaches values('1', '20', '1', 'Spring', 2015);
insert into teaches values('2', '21', '1', 'Spring', 2013);
insert into teaches values('2', '21', '1', 'Spring', 2007);
insert into teaches values('3', '22', '1', 'Fall', 2012);
insert into teaches values('7', '23', '2', 'Spring', 2010);
insert into teaches values('4', '24', '1', 'Fall', 2015);
insert into teaches values('5', '25', '1', 'Fall', 2010);
insert into teaches values('6', '26', '1', 'Fall', 2006);
insert into teaches values('7', '27', '1', 'Fall', 2009);
insert into teaches values('8', '26', '1', 'Spring', 2013);
insert into teaches values('9', '25', '1', 'Spring', 2014);
insert into teaches values('10', '24', '1', 'Spring', 2014);
insert into teaches values('1', '23', '1', 'Spring', 2015);
insert into teaches values('2', '22', '2', 'Fall', 2012);
insert into teaches values('3', '21', '1', 'Fall', 2010);
insert into teaches values('4', '20', '1', 'Spring', 2010);
insert into teaches values('5', '19', '1', 'Fall', 2006);
insert into teaches values('6', '18', '1', 'Fall', 2015);
insert into teaches values('6', '17', '1', 'Spring', 2011);
insert into teaches values('7', '16', '1', 'Spring', 2013);
insert into teaches values('8', '15', '1', 'Spring', 2007);
insert into teaches values('9', '14', '1', 'Spring', 2006);
insert into teaches values('10', '13', '2', 'Spring', 2006);
insert into teaches values('3', '12', '2', 'Fall', 2006);
insert into teaches values('4', '11', '1', 'Spring', 2008);
insert into teaches values('2', '11', '1', 'Spring', 2007);
insert into teaches values('1', '12', '1', 'Fall', 2015);
insert into teaches values('5', '14', '1', 'Fall', 2013);
insert into teaches values('8', '13', '1', 'Spring', 2009);
insert into teaches values('9', '15', '1', 'Spring', 2013);

insert into student values('111', 'Schrefl', 'Accounting', 4);
insert into student values('112', 'Rumat', 'Finance', 100);
insert into student values('113', 'Miliko', 'Statistics', 116);
insert into student values('114', 'Moszkowski', 'Civil Eng.', 73);
insert into student values('115', 'Prieto', 'Accounting', 91);
insert into student values('116', 'Marcol', 'Elec. Eng.', 15);
insert into student values('117', 'Quimby', 'Comp. Sci.', 4);
insert into student values('118', 'Sowerby', 'Elec. Eng.', 108);
insert into student values('119', 'Coppens', 'Math', 58);
insert into student values('120', 'Cirsto', 'Math', 115);
insert into student values('121', 'Velikovs', 'Marketing', 110);
insert into student values('122', 'Marek', 'Elec. Eng.', 53);
insert into student values('123', 'Tran-', 'Marketing', 116);
insert into student values('124', 'Guerra', 'Elec. Eng.', 59);
insert into student values('125', 'Hawthorne', 'Marketing', 78);
insert into student values('126', 'Leuen', 'Math', 43);
insert into student values('127', 'Eguchi', 'Comp. Sci.', 14);
insert into student values('128', 'Moei', 'Elec. Eng.', 15);
insert into student values('129', 'Alfaro', 'Elec. Eng.', 69);
insert into student values('130', 'Krishnakumar', 'Physics', 81);
insert into student values('131', 'Inoue', 'Math', 18);
insert into student values('132', 'Sahm', 'Finance', 4);
insert into student values('133', 'Tomason', 'Physics', 118);
insert into student values('134', 'Karande', 'Comp. Sci.', 57);
insert into student values('135', 'Wunderli', 'Physics', 117);
insert into student values('136', 'Greve', 'Psychology', 113);
insert into student values('137', 'Cerime', 'Accounting', 35);
insert into student values('138', 'Crick', 'Comp. Sci.', 86);
insert into student values('139', 'Hashimoto', 'Physics', 102);
insert into student values('140', 'Dage', 'Physics', 7);

insert into takes values('111', '11', '1', 'Spring', 2014, 'C-');
insert into takes values('112', '12', '1', 'Fall', 2013, 'B-');
insert into takes values('113', '13', '1', 'Spring', 2016, 'A-');
insert into takes values('114', '14', '1', 'Spring', 2011, 'A ');
insert into takes values('115', '15', '1', 'Fall', 2010, 'B+');
insert into takes values('116', '16', '1', 'Spring', 2007, 'B-');
insert into takes values('117', '17', '1', 'Spring', 2014, 'B ');
insert into takes values('118', '18', '1', 'Fall', 2010, 'A ');
insert into takes values('119', '19', '1', 'Fall', 2006, 'C+');
insert into takes values('120', '20', '1', 'Fall', 2013, 'B-');
insert into takes values('121', '21', '1', 'Spring', 2011, 'C-');
insert into takes values('122', '22', '1', 'Spring', 2007, 'A+');
insert into takes values('123', '23', '1', 'Spring', 2007, 'C ');
insert into takes values('124', '24', '1', 'Spring', 2014, 'A-');
insert into takes values('125', '25', '1', 'Fall', 2011, 'C-');
insert into takes values('126', '26', '1', 'Spring', 2014, 'B ');
insert into takes values('127', '27', '1', 'Fall', 2009, 'A ');
insert into takes values('128', '26', '1', 'Spring', 2013, 'A-');
insert into takes values('129', '25', '1', 'Fall', 2010, 'C+');
insert into takes values('130', '24', '1', 'Fall', 2012, 'A-');
insert into takes values('131', '23', '1', 'Fall', 2015, 'C+');
insert into takes values('132', '22', '1', 'Fall', 2006, 'A+');
insert into takes values('133', '22', '1', 'Spring', 2009, 'A+');
insert into takes values('134', '21', '1', 'Fall', 2007, 'A+');
insert into takes values('135', '20', '1', 'Fall', 2006, 'C ');
insert into takes values('136', '19', '1', 'Fall', 2012, 'A ');
insert into takes values('137', '18', '1', 'Spring', 2010, 'C ');
insert into takes values('138', '17', '1', 'Spring', 2009, 'A-');
insert into takes values('139', '16', '1', 'Spring', 2007, 'B-');
insert into takes values('140', '17', '1', 'Fall', 2014, 'C ');
insert into takes values('139', '15', '1', 'Fall', 2007, 'A-');
insert into takes values('138', '14', '1', 'Spring', 2011, 'B ');
insert into takes values('137', '13', '1', 'Spring', 2016, 'A-');
insert into takes values('136', '12', '1', 'Fall', 2013, 'A ');
insert into takes values('135', '11', '1', 'Spring', 2014, 'A+');
insert into takes values('134', '12', '1', 'Fall', 2015, 'A+');
insert into takes values('133', '13', '1', 'Spring', 2016, 'B-');
insert into takes values('132', '14', '1', 'Spring', 2011, 'B-');
insert into takes values('131', '15', '1', 'Fall', 2014, 'A+');
insert into takes values('130', '16', '1', 'Spring', 2007, 'A ');
insert into takes values('129', '17', '1', 'Spring', 2013, 'B-');
insert into takes values('128', '18', '2', 'Fall', 2007, 'B-');
insert into takes values('127', '19', '1', 'Fall', 2009, 'C-');
insert into takes values('126', '20', '1', 'Fall', 2006, 'A+');
insert into takes values('125', '21', '2', 'Spring', 2016, 'A ');
insert into takes values('124', '22', '1', 'Fall', 2007, 'C ');
insert into takes values('123', '23', '1', 'Fall', 2009, 'B+');
insert into takes values('122', '24', '1', 'Spring', 2010, 'A-');
insert into takes values('121', '25', '1', 'Spring', 2007, 'A-');
insert into takes values('120', '26', '1', 'Fall', 2010, 'B ');
insert into takes values('119', '27', '2', 'Fall', 2006, 'C+');
insert into takes values('118', '20', '1', 'Spring', 2007, 'C-');
insert into takes values('117', '20', '1', 'Spring', 2011, 'C-');
insert into takes values('116', '23', '1', 'Fall', 2009, 'B ');
insert into takes values('115', '25', '1', 'Spring', 2015, 'B-');
insert into takes values('114', '24', '1', 'Fall', 2010, 'B ');
insert into takes values('113', '23', '1', 'Fall', 2006, 'C+');
insert into takes values('112', '21', '1', 'Spring', 2015, 'C+');
insert into takes values('111', '14', '1', 'Spring', 2011, 'B-');
insert into takes values('112', '15', '1', 'Fall', 2009, 'C+');
insert into takes values('113', '16', '1', 'Spring', 2007, 'B ');
insert into takes values('114', '17', '1', 'Spring', 2011, 'A ');
insert into takes values('115', '18', '1', 'Fall', 2009, 'A+');
insert into takes values('116', '17', '1', 'Spring', 2006, 'B ');
insert into takes values('117', '16', '1', 'Spring', 2007, 'C ');
insert into takes values('118', '13', '1', 'Spring', 2016, 'A ');
insert into takes values('119', '12', '1', 'Fall', 2006, 'B+');
insert into takes values('120', '13', '1', 'Spring', 2016, 'B-');
insert into takes values('121', '11', '1', 'Spring', 2014, 'C-');
insert into takes values('122', '16', '1', 'Spring', 2007, 'C ');
insert into takes values('123', '15', '3', 'Spring', 2016, 'A-');
insert into takes values('124', '13', '1', 'Fall', 2010, 'A ');
insert into takes values('125', '13', '1', 'Spring', 2016, 'B-');
insert into takes values('126', '14', '1', 'Spring', 2011, 'A-');
insert into takes values('127', '12', '1', 'Fall', 2013, 'A-');
insert into takes values('128', '14', '1', 'Spring', 2011, 'C-');
insert into takes values('129', '12', '1', 'Fall', 2013, 'C-');
insert into takes values('130', '14', '1', 'Spring', 2011, 'C-');
insert into takes values('131', '16', '1', 'Spring', 2007, 'A-');
insert into takes values('132', '12', '1', 'Fall', 2013, 'A+');
insert into takes values('133', '16', '2', 'Fall', 2012, 'B-');
insert into takes values('134', '12', '1', 'Fall', 2013, 'C ');
insert into takes values('135', '16', '2', 'Fall', 2012, 'B+');
insert into takes values('136', '14', '1', 'Spring', 2011, 'A ');
insert into takes values('137', '16', '2', 'Fall', 2012, 'B+');
insert into takes values('138', '11', '1', 'Spring', 2014, 'C ');
insert into takes values('139', '16', '1', 'Spring', 2015, 'C-');
insert into takes values('140', '12', '1', 'Fall', 2013, 'B+');
insert into takes values('139', '13', '1', 'Spring', 2016, 'C-');
insert into takes values('138', '16', '2', 'Fall', 2012, 'A+');
insert into takes values('137', '12', '1', 'Fall', 2013, 'B+');
insert into takes values('136', '11', '1', 'Spring', 2014, 'C ');
insert into takes values('135', '14', '1', 'Fall', 2015, 'C-');
insert into takes values('134', '16', '1', 'Spring', 2007, 'C-');
insert into takes values('133', '12', '1', 'Fall', 2013, 'C+');
insert into takes values('132', '13', '1', 'Spring', 2016, 'B ');
insert into takes values('131', '18', '1', 'Spring', 2015, 'C-');
insert into takes values('130', '11', '1', 'Spring', 2014, 'C ');
insert into takes values('129', '20', '2', 'Spring', 2010, 'C-');
insert into takes values('128', '13', '1', 'Spring', 2016, 'B-');
insert into takes values('127', '21', '1', 'Fall', 2014, 'B+');
insert into takes values('126', '22', '1', 'Spring', 2011, 'A ');
insert into takes values('125', '12', '1', 'Fall', 2013, 'B-');
insert into takes values('125', '14', '1', 'Spring', 2011, 'C ');
insert into takes values('124', '23', '2', 'Fall', 2012, 'C-');
insert into takes values('124', '24', '2', 'Spring', 2012, 'B ');
insert into takes values('123', '25', '1', 'Fall', 2015, 'C ');
insert into takes values('123', '26', '1', 'Fall', 2014, 'B-');
insert into takes values('121', '27', '1', 'Spring', 2016, 'C ');
insert into takes values('120', '14', '1', 'Spring', 2011, 'A-');
insert into takes values('119', '12', '1', 'Fall', 2013, 'B+');
insert into takes values('118', '26', '1', 'Fall', 2009, 'A+');
insert into takes values('117', '25', '1', 'Spring', 2007, 'A ');
insert into takes values('116', '24', '1', 'Spring', 2016, 'C ');
insert into takes values('115', '23', '1', 'Fall', 2010, 'C-');
insert into takes values('114', '22', '1', 'Spring', 2010, 'B+');
insert into takes values('113', '21', '2', 'Fall', 2006, 'A ');
insert into takes values('114', '20', '1', 'Spring', 2007, 'A-');
insert into takes values('113', '15', '1', 'Fall', 2008, 'C-');
insert into takes values('113', '22', '1', 'Fall', 2014, 'B ');
insert into takes values('112', '14', '1', 'Spring', 2011, 'A ');
insert into takes values('111', '17', '1', 'Fall', 2007, 'C ');
insert into takes values('111', '12', '1', 'Fall', 2013, 'C-');
insert into takes values('121', '17', '1', 'Fall', 2007, 'A ');
insert into takes values('122', '14', '2', 'Fall', 2013, 'C+');
insert into takes values('123', '17', '1', 'Fall', 2013, 'A+');
insert into takes values('124', '16', '1', 'Fall', 2010, 'C-');
insert into takes values('135', '14', '1', 'Spring', 2011, 'A+');