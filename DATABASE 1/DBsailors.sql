CREATE DATABASE sailors;
use sailors;


CREATE TABLE sailors(sid INT NOT NULL, sname VARCHAR(20) NOT NULL, rating INT, age FLOAT, PRIMARY KEY(sid, sname));
INSERT INTO sailors VALUES (22, 'Dustin', 7, 45);
INSERT INTO sailors VALUES (29, 'Brutus', 1, 33.3);
INSERT INTO sailors VALUES (31, 'Lubber', 8, 55.5);
INSERT INTO sailors VALUES (32, 'Andy', 8, 25.5);
INSERT INTO sailors VALUES (58, 'Rusty', 10, 35.0);
INSERT INTO sailors VALUES (64, 'Horatio', 7, 35);
INSERT INTO sailors VALUES (71, 'Zorba', 10, 16.0);
INSERT INTO sailors VALUES (74, 'Horatio', 9, 35.0);
INSERT INTO sailors VALUES (85, 'Art', 3, 25.5);
INSERT INTO sailors VALUES (95, 'Bob', 3, 63.3);

CREATE TABLE reserves(sid INT NOT NULL, bid INT NOT NULL, day DATE);
INSERT INTO reserves VALUES (22, 101, '1998-10-10');
INSERT INTO reserves VALUES (22, 102, '1998-10-10');
INSERT INTO reserves VALUES (22, 103, '1998-10-08');
INSERT INTO reserves VALUES (22, 104, '1998-10-07');
INSERT INTO reserves VALUES (31, 102, '1998-11-10');
INSERT INTO reserves VALUES (31, 103, '1998-11-06');
INSERT INTO reserves VALUES (31, 104, '1998-11-12');
INSERT INTO reserves VALUES (64, 101, '1998-09-05');
INSERT INTO reserves VALUES (64, 102, '1998-09-08');
INSERT INTO reserves VALUES (74, 103, '1998-09-08');

CREATE TABLE boats(bid INT NOT NULL, bname VARCHAR(20), color VARCHAR(20), PRIMARY KEY(bid));
INSERT INTO boats VALUES (101, 'Interlake', 'Blue');
INSERT INTO boats VALUES (102, 'Interlake', 'Red');
INSERT INTO boats VALUES (103, 'Clipper', 'Green');
INSERT INTO boats VALUES (104, 'Marine', 'Red');


SELECT rating, COUNT(*)
FROM reserves r, sailors s 
WHERE r.sid=s.sid
GROUP BY rating;
-- +--------+----------+
-- | rating | COUNT(*) |
-- +--------+----------+
-- |      7 |        6 |
-- |      8 |        3 |
-- |      9 |        1 |
-- +--------+----------+

SELECT rating
FROM reserves r, sailors s 
WHERE r.sid=s.sid
GROUP BY rating 
HAVING COUNT(*) >= ALL(SELECT COUNT(*) 
					   FROM reserves r1, sailors s1 
					   WHERE r1.sid=s1.sid 
					   GROUP BY rating);
-- +--------+
-- | rating |
-- +--------+
-- |      7 |
-- +--------+

SELECT s1.sname, COUNT(*) 
FROM reserves r1, sailors s1 
WHERE r1.sid=s1.sid AND s1.rating IN (SELECT rating 
									  FROM reserves r2, sailors s2 
									  WHERE r2.sid=s2.sid 
									  GROUP BY s2.rating 
									  HAVING COUNT(*) >= ALL (SELECT COUNT(*) 
															  FROM reserves r3, sailors s3 
															  WHERE r3.sid=s3.sid 
															  GROUP BY s3.rating)) 
GROUP BY s1.sid, s1.sname;
-- +---------+----------+
-- | sname   | COUNT(*) |
-- +---------+----------+
-- | Dustin  |        4 |
-- | Horatio |        2 |
-- +---------+----------+

SELECT rating, COUNT(*)
FROM reserves r, sailors s 
WHERE r.sid=s.sid 
GROUP BY rating;
-- +--------+----------+
-- | rating | COUNT(*) |
-- +--------+----------+
-- |      7 |        6 |
-- |      8 |        3 |
-- |      9 |        1 |
-- +--------+----------+

SELECT sname, rating 
FROM sailors 
WHERE sid IN (SELECT sid 
			  FROM reserves 
			  GROUP BY sid 
			  HAVING COUNT(DISTINCT bid) >= ALL(SELECT COUNT(DISTINCT bid) 
												FROM reserves 
												GROUP BY sid));
-- +--------+--------+
-- | sname  | rating |
-- +--------+--------+
-- | Dustin |      7 |
-- +--------+--------+

SELECT sname, rating 
FROM sailors 
WHERE sid IN (SELECT sid 
			  FROM reserves 
			  GROUP BY sid 
			  HAVING COUNT(bid) >= ALL(SELECT COUNT(DISTINCT bid) 
												FROM reserves 
												GROUP BY sid));
-- +--------+--------+
-- | sname  | rating |
-- +--------+--------+
-- | Dustin |      7 |
-- +--------+--------+
												

SELECT sname 
FROM sailors s 
WHERE NOT EXISTS (SELECT bid 
				  FROM boats 
				  WHERE bid NOT IN (SELECT r.bid 
									FROM reserves r 
									WHERE r.sid=s.sid));
-- +--------+
-- | sname  |
-- +--------+
-- | Dustin |
-- +--------+

SELECT sname 
FROM sailors 
WHERE sid IN (SELECT sid 
			  FROM reserves 
			  GROUP BY sid 
			  HAVING COUNT(DISTINCT bid) = (SELECT COUNT(bid) FROM boats));
-- +--------+
-- | sname  |
-- +--------+
-- | Dustin |
-- +--------+

SELECT rating, MIN(age) 
FROM sailors 
GROUP BY rating 
HAVING min(age)<=ALL(SELECT age FROM sailors);
-- +--------+----------+
-- | rating | MIN(age) |
-- +--------+----------+
-- |     10 |       16 |
-- +--------+----------+

SELECT rating, AVG(age) 
FROM sailors 
GROUP BY rating 
HAVING MIN(age)<=ALL(SELECT age FROM sailors);
-- +--------+----------+
-- | rating | AVG(age) |
-- +--------+----------+
-- |     10 |     25.5 |
-- +--------+----------+