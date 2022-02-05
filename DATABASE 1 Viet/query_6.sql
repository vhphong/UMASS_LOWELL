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