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

-- sailors(sid, sname, rating, age)
-- reserves(sid, bid, day)
-- boats(bid, bname, color)

-- //Find the names of sailors who have reserved exactly one boat.
SELECT sname
FROM sailors s, reserves r
WHERE s.sid=r.sid GROUP BY s.sid HAVING COUNT(bid) = 1;

-- or

SELECT sname
FROM sailors
WHERE sid IN (SELECT sid
              FROM reserves
              GROUP BY SID
              HAVING COUNT(DISTINCT bid) = 1);

-- +---------+
-- | sname   |
-- +---------+
-- | Horatio |
-- +---------+

-- //Find the names of sailors who have reserved all the boats.
SELECT sname
FROM sailors S
WHERE NOT EXISTS (SELECT bid
                  FROM boats
                  WHERE bid NOT IN (SELECT R.bid
                                    FROM reserves R
                                    WHERE R.sid=S.sid));
-- +--------+
-- | sname  |
-- +--------+
-- | Dustin |
-- +--------+

-- //Or
SELECT sname
FROM sailors 
WHERE sid IN (SELECT sid
              FROM reserves 
              GROUP BY sid
              HAVING COUNT (DISTINCT bid) = (SELECT COUNT(*)
                                             FROM boats));



-- //Count how many unique boats each sailor has reserved. List the result in ascending order of sailors names.
SELECT sname, COUNT (DISTINCT bid)
FROM reserves r, sailors s
WHERE r.sid = s.sid 
GROUP BY s.sid, sname
ORDER by sname;

-- //Find the names of boats that have been reserved more frequently than the boat named Interlake. 
SELECT DISTINCT bname
FROM boats
WHERE bid IN (SELECT bid
              FROM reserves 
              GROUP BY bid
              HAVING COUNT(*) > (SELECT COUNT(*) 
                                 FROM reserves R, boats B
                                 WHERE R.bid = B.bid AND bname='Interlake'));

-- //Find the average age of the rating group if the group has the youngest sailor of all sailors. 
SELECT rating, AVG(age)
FROM sailors
GROUP BY rating
HAVING MIN(age) <= ALL (SELECT age
                        FROM sailors);

-- //Find the names and ratings of sailors who have reserved the most number of unique boats. 
SELECT sname, rating
FROM sailors
WHERE sid IN (SELECT sid
              FROM reserves 
              GROUP BY sid
              HAVING COUNT (DISTINCT bid) >= ALL (SELECT COUNT (DISTINCT bid) 
                                                  FROM reserves 
                                                  GROUP BY sid));

-- //For sailors in the rating group that reserve boats the most often, find how many times each sailor reserves boats.
SELECT S1.sname, count(*)
FROM reserves R1, sailors S1
WHERE R1.sid = S1.sid 
AND S1.rating IN (SELECT rating 
                  FROM reserves R2, sailors S2
                  WHERE R2.sid=S2.sid
                  GROUP BY S2.rating
                  HAVING COUNT(*) >= ALL (SELECT COUNT(*)
                                          FROM reserves R3, sailors S3
                                          WHERE R3.sid=S3.sid
                                          GROUP BY S3.rating))
GROUP BY S1.sid, S1.sname;


