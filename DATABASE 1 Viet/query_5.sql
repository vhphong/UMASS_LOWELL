/*
5. Find the name of instructor who teaches the most students.
*/

clear break
clear comp
clear col

set linesize 9999
set trimspool ON
set tab off
set echo off
set recsep off

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