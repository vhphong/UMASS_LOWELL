/*
List all instructor IDs who did not teach any courses in Fall 2016.
*/
select distinct(id) from teaches 
where semester != 'Fall' and year != '2016';

/* OUTPUT
	ID
----------
	 1
	 2
	 3
	 4
	 5
	 6
	 7
	 8
	 9
	10
*/