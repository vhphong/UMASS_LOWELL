/*      Saivenkat Thatikonda       Student Id- 01727982
        Tran,Viet Q.

*/


 /* 1 */     select name from student where ID='113';

 /*2 */     select title from course where title like 'G%';

 /*3 */     select distinct ID from instructor where ID not in (select t.ID from teaches t,instructor i
 where t.ID=i.ID and semester='Fall' and year=2016);  



  /*4 */    select dept_name,count(ID)
      from student
      group by dept_name
      order by count(ID) asc;













  /*5*/ 
  select name from instructor 
  where ID in
  ( select teaches.ID from teaches,takes 
    where  teaches.course_id=takes.course_id 
    group by teaches.ID
    having count(DISTINCT takes.ID) >= all 
    (select max(count(DISTINCT takes.ID)) from teaches,takes 
    where teaches.course_id=takes.course_id 
    group by teaches.ID));




 
/*6 */select DISTINCT i.name 
from instructor i,teaches t
where i.ID=t.ID and t.year IN ( select t1.year 
                                from instructor i1,teaches t1
                                where i1.ID=t1.ID and i1.name='McKinnon');





 /*7*/  select  name,salary
from instructor
where ROWNUM<=2 and dept_name=(select dept_name
from instructor
group by dept_name
having avg(salary) >= all( select avg(salary)
                            from instructor
                            group by dept_name));



/*8*/ select s.name,     t.year,    t.semester,c.title,s.tot_cred,t.grade 
from student s,takes t,course c
where s.ID=t.ID and t.course_id=c.course_id and s.name IN(select name from student where ROWNUM<=5 and dept_name='Comp. Sci.')
order by s.name,t.year desc,t.semester desc;




/*9*/update instructor
set salary = salary + 10000
where salary <=50000 ;





/*10*/ delete from takes
where ID  IN (select ID from takes natural join student
              where name='Tomason');