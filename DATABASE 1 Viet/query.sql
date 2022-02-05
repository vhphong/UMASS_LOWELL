/* 
1. Find the student's name whose ID = "113".
*/

select name from student 
where id = '113';

/* OUTPUT 
NAME
------------------------------
Miliko
*/


/*
2. List all courses which title starts with "G".
*/
select title from course 
where title like 'G%';

/* OUTPUT
TITLE
------------------------------
Greek Tragedy
Greek Tragedy
Geology
Graph Theory
*/

/*
3. List all instructor IDs who did not teach any courses in Fall 2016.
*/
select distinct(id) from teaches 
MINUS 
select distinct(id) from teaches 
where semester = 'Fall' and year = '2016';

/* OUTPUT
	ID
----------
	 1
	 2
	 3
	 4
	 6
	 9
	10
*/

/*
4. Find the total number of students in each department. 
Display the number in ascending order.
*/

select count(name) as Total_Students,dept_name from student 
group by dept_name 
order by count(name) asc;

/*
OUTPUT
TOTAL_STUDENTS DEPT_NAME
-------------- ------------------------------
             1 Statistics
             1 Civil Eng.
             1 Psychology
             2 Finance
             3 Accounting
             3 Marketing
             4 Math
             4 Comp. Sci.
             5 Physics
             6 Elec. Eng.

10 rows selected.
*/

/*
5. Find the name of instructor who teaches the most students.
*/

select distinct(instructor.name) 
from instructor inner join teaches
on teaches.id = instructor.id
where teaches.id in (
	select teaches.id
	from takes inner join teaches 
	on  takes.sec_id = teaches.sec_id 
	and takes.semester = teaches.semester 
	and takes.year = teaches.year 
	and takes.course_id = teaches.course_id
	having count(teaches.id) = (
		select max(count(teaches.id)) 
		from takes inner join teaches 
		on  takes.sec_id = teaches.sec_id 
		and takes.semester = teaches.semester 
		and takes.year = teaches.year 
		and takes.course_id = teaches.course_id
		group by teaches.id) 
	group by teaches.id
);

/* OUTPUT
NAME
------------------------------------------------------------
Shuming
*/

/*
6. List all instructors who teach in all those 
years that the instructor "McKinnon" teaches.
*/

select distinct(name)
from instructor inner join teaches
on instructor.id = teaches.id
where (year) in (
	select distinct(year) 
	from instructor join teaches
	on instructor.id = teaches.id
	where name = 'McKinnon'
	)
and name != 'McKinnon'
group by name;

/*
OUTPUT
NAME
------------------------------------------------------------
Pingr
Luo
Queiroz
Sullivan
Bertolino
Mird
Konstantinides
Levine
*/

/*
7. For the department where the instructors have the highest average salary, 
list the top 2 instructors who have the highest salaries and their salaries.
*/

select name,salary from instructor 
	where dept_name in (
	select dept_name from instructor 
	having (avg(salary))= (
		select max(avg(salary)) from instructor 
		group by dept_name)
	group by dept_name
	) 
	and ROWNUM <=2
order by salary desc;

/* OUTPUT
NAME                                                             SALARY
------------------------------------------------------------ ----------
McKinnon                                                         194334
Luo                                                              188791
*/

/*

Generate "transcript records" for all students of "Comp. Sci." department. 
A transcript record should include student name, course title, the year
and semester when the student took this course, the credits of this course 
and the grade of the student on this course. The transcript records from 
one student should be shown together, and in year, semester descending order. 
Return only 5 of those transcript records.

student name
course title,credit
takes year,semester,grade

*/

select name,title,semester,year,credits,grade
from student join takes 
on student.id = takes.id 
join course 
on takes.course_id = course.course_id 
where student.name in (
	select name from student 
	where ROWNUM <= 5 and dept_name='Comp. Sci.')
order by name,year desc,semester desc;

/* OUTPUT
NAME                           TITLE                          SEMESTER                   YEAR    CREDITS GRADE
------------------------------ ------------------------------ -------------------- ---------- ---------- -----
Crick                          International Finance          Spring                     2014          3 C
Crick                          Geology                        Fall                       2012          3 A+
Crick                          Virology                       Spring                     2011          3 B
Crick                          Mobile Computing               Spring                     2009          3 A-
Eguchi                         Visual BASIC                   Fall                       2014          4 B+
Eguchi                         Greek Tragedy                  Fall                       2013          4 A-
Eguchi                         The Beatles                    Fall                       2009          3 A
Eguchi                         International Trade            Fall                       2009          3 C-
Karande                        Greek Tragedy                  Fall                       2015          4 A+
Karande                        Greek Tragedy                  Fall                       2013          4 C
Karande                        Geology                        Spring                     2007          3 C-

NAME                           TITLE                          SEMESTER                   YEAR    CREDITS GRADE
------------------------------ ------------------------------ -------------------- ---------- ---------- -----
Karande                        Visual BASIC                   Fall                       2007          4 A+
Quimby                         Mobile Computing               Spring                     2014          3 B
Quimby                         Graph Theory                   Spring                     2011          3 C-
Quimby                         Calculus                       Spring                     2007          4 A
Quimby                         Geology                        Spring                     2007          3 C

16 rows selected.
*/

