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
clear break
clear comp
clear col

set linesize 9999
set trimspool ON
set tab off
set echo off
set recsep off

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
NAME                           TITLE                          GRADE SEMESTER                   YEAR    CREDITS
------------------------------ ------------------------------ ----- -------------------- ---------- ----------
Crick                          International Finance          C     Spring                     2014          3
Crick                          Geology                        A+    Fall                       2012          3
Crick                          Virology                       B     Spring                     2011          3
Crick                          Mobile Computing               A-    Spring                     2009          3
Eguchi                         Visual BASIC                   B+    Fall                       2014          4
Eguchi                         Greek Tragedy                  A-    Fall                       2013          4
Eguchi                         The Beatles                    A     Fall                       2009          3
Eguchi                         International Trade            C-    Fall                       2009          3
Karande                        Greek Tragedy                  A+    Fall                       2015          4
Karande                        Greek Tragedy                  C     Fall                       2013          4
Karande                        Geology                        C-    Spring                     2007          3

NAME                           TITLE                          GRADE SEMESTER                   YEAR    CREDITS
------------------------------ ------------------------------ ----- -------------------- ---------- ----------
Karande                        Visual BASIC                   A+    Fall                       2007          4
Quimby                         Mobile Computing               B     Spring                     2014          3
Quimby                         Graph Theory                   C-    Spring                     2011          3
Quimby                         Calculus                       A     Spring                     2007          4
Quimby                         Geology                        C     Spring                     2007          3

16 rows selected.
*/

