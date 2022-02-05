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