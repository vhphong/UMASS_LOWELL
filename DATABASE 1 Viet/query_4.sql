/*
4. Find the total number of students in each department. 
Display the number in ascending order.
*/

select count(name) as Total_Students,dept_name from student 
group by dept_name 
order by count(name) asc;

/*
OUTPUT
COUNT(NAME) DEPT_NAME
----------- ------------------------------
	  1 	Statistics
	  1 	Civil Eng.
	  1 	Psychology
	  2 	Findinance
	  3 	Accounting
	  3 	Marketing
	  4 	Math
	  4 	Comp. Sci.
	  5 	Physics
	  6 	Elec. Eng.
*/

