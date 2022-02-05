-- ANSWERS:

-- M-1. Find the title and year of movies if there are two movies with the same title
		SELECT DISTINCT m1.title, m1.year FROM Movies m1, Movies m2 WHERE m1.title = m2.title AND m1.year <> m2.year;

-- M-2. Find the title of the longest movies
		SELECT title FROM Movies WHERE length >=ALL(SELECT length FROM Movies);

-- M-3. Find the name of stars who have stared in the same movie as Harrison Ford
		SELECT distinct name FROM starsin WHERE title IN (SELECT title FROM stars WHERE name='Harrison Ford') and name <> 'Harrison Ford';

-- M-4. Find the name of stars who have stared in both comedy and drama
		(SELECT DISTINCT name FROM starsin s, Movies m WHERE s.title=m.title AND s.year=m.year and genre='Comedy') intersect
		(SELECT DISTINCT name FROM starsin s, Movies m WHERE s.title=m.title AND s.year=m.year and genre='Drama');

-- M-5. Find name of stars who have stared in every genre of movies
		SELECT DISTINCT name
		FROM starsin AS star
		WHERE NOT EXISTS
			(SELECT genre FROM Movies WHERE genre NOT IN
				(SELECT genre FROM Movies m, starsin s WHERE m.title=s.title AND star.name=s.name));

-- Find the beer brands that are both sold at bar Joe and Sue
SELECT beer FROM sells WHERE bar='Joe' INTERSECT
SELECT beer FROM sells WHERE bar='Sue';

SELECT beer FROM sells WHERE bar='Joe' OR bar='Sue';
		-- => no rows selected