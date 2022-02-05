select name from instructor 
where ID =( 
	select teaches.ID from teaches,takes 
	where  teaches.course_id=takes.course_id 
	group by teaches.ID
having count( takes.ID) >= all 
(select count( takes.ID) from teaches,takes 
	where teaches.course_id=takes.course_id 
	group by teaches.ID));