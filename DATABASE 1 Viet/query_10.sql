/*
Delete all the records in table "takes" which students' name = "Tomason".

TBD: check if delete from student too
*/

delete from takes 
	where id = (select id from student 
				where name = 'Tomason');