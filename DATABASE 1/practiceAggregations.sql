-- Find the average price of the laptops
SELECT AVG(price) FROM laptop;

-- Find the average price of the laptops with the models is 2005 or later
SELECT AVG(price) FROM laptop WHERE model >=2005;

-- Find the average price of the laptops with the models is 2005 or later and ram is greater than 512MB
SELECT AVG(price) FROM laptop WHERE model >=2005 AND ram >512;

-- Find the quantity of the laptops being sold
SELECT COUNT(model) FROM laptop;

-- Find the quantity of various RAM sizes are available in the laptops
SELECT COUNT(DISTINCT ram) FROM laptop;

-- Find the quantity of laptops which cost more $1000
SELECT COUNT(price) FROM laptop WHERE price > 1000;

-- From laptop, find the average price. Grouped by hard-disk size
SELECT hd, AVG(price) FROM laptop GROUP BY hd;

-- Find the laptop with the lowest price
SELECT model FROM laptop WHERE price = (SELECT MIN(price) FROM laptop);
SELECT model FROM laptop WHERE price <= ALL (SELECT price FROM laptop);

-- Find the laptop with the highest price
SELECT model FROM laptop WHERE price = (SELECT MAX(price) FROM laptop);
SELECT model FROM laptop WHERE price >= ALL (SELECT price FROM laptop);

-- Find the sailors's names who served on only boat.
SELECT sname 
FROM sailors 
WHERE sid IN (SELECT sid 
			  FROM reserves 
			  GROUP BY sid 
			  HAVING COUNT(DISTINCT bid)=1);
-- +---------+
-- | sname   |
-- +---------+
-- | Horatio |
-- +---------+

SELECT s1.sname, count(*) 
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
-- | sname   | count(*) |
-- +---------+----------+
-- | Dustin  |        4 |
-- | Horatio |        2 |
-- +---------+----------+


SELECT sname, rating FROM sailors WHERE sid IN (SELECT sid FROM reserves GROUP BY sid HAVING COUNT(DISTINCT bid) >= ALL (SELECT COUNT(DISTINCT bid) FROM reserves GROUP BY sid));

SELECT sname FROM sailors s WHERE NOT EXISTS (SELECT bid FROM boats WHERE bid NOT IN (SELECT r.bid FROM reserves r WHERE r.sid=s.sid));
-- >> Dustin, using double negation

SELECT sname FROM sailors WHERE sid IN (SELECT sid FROM reserves GROUP BY sid HAVING COUNT(DISTINCT bid) = (SELECT COUNT(bid) FROM boats));
-- >> Dustin