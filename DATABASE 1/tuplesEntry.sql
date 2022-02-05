-- Find the model numbers and prices of all products (of any type) made by manufacturer B
SELECT DISTINCT pr.model, p.price, l.price, pt.price
FROM Product pr JOIN pc p, Product pr JOIN laptop l, Product pr JOIN printer
WHERE (maker = 'B' AND pr.model=p.model) OR (maker = 'B' AND pr.model=l.model) OR (maker = 'B' AND pr.model=pt.model)
ORDER BY model;

-- Find manufacturers of at least two different computers (PCs or laptops) with speeds of at least 2.80
-- SELECT
-- FROM pc, laptop
-- WHERE 

CREATE TABLE classes(class VARCHAR(50) PRIMARY KEY, type  VARCHAR(5), country VARCHAR (30), numGuns INT, bore INT, displacement INT);
CREATE TABLE battles(name VARCHAR(100) PRIMARY KEY, date DATE);
CREATE TABLE outcomes(ship VARCHAR(50) PRIMARY KEY, battle VARCHAR(100), result VARCHAR(20));
CREATE TABLE ships(name VARCHAR(50), class VARCHAR(50), launched INT);

INSERT INTO classes VALUES ('Bismarck', 'bb', 'Germany', 8, 15, 42000);
INSERT INTO battles VALUES ('Denmark Strait', 5/24-27/41);
INSERT INTO outcomes VALUES ('Yamashiro', 'Surigao Strait', 'sunk');
INSERT INTO ships VALUES ('Yamato', 'Yamato', 1941);

SELECT DISTINCT o.ship, c.displacement, c.numGuns
FROM classes c, outcomes o, ships s
WHERE o.battle='Guadalcanal' AND
      o.ship IN (SELECT name FROM ships WHERE class IN (SELECT class FROM classes));


SELECT DISTINCT o.ship, c.displacement, c.numGuns
FROM outcomes o, ships s, classes c
WHERE o.battle='Guadalcanal' AND o.ship IN (SELECT s.name FROM ships s WHERE class IN (SELECT c.class FROM classes c));


-- Find the bars that don't sell any beer.
SELECT name
FROM Bars b
WHERE NOT EXISTS (SELECT bar FROM Sells WHERE bar=b.name);

-- Find the beers that are the unique beer made by their manufacturers
-- SELECT name
-- FROM Beers
-- WHERE NOT EXISTS


























































































