-- .\mysqldump.exe -u root -p ww2ships > ww2ships.sql
--
-- Table structure for table 'battles'
--

-- DROP TABLE IF EXISTS battles;
CREATE TABLE battles(
	name varchar(100) NOT NULL, 
	date date DEFAULT NULL, 
	PRIMARY KEY (name)
);


INSERT INTO battles VALUES 
('Denmark Strait', '0000-00-00'), 
('Guadalcanal', '0000-00-00'), 
('North Cape', '0000-00-00'), 
('Surigao Strait', '0000-00-00');
--
-- Table structure for table 'classes'
--

DROP TABLE IF EXISTS classes;

CREATE TABLE classes (
	class varchar(50) NOT NULL, 
	type varchar(5) DEFAULT NULL, 
	country varchar(30) DEFAULT NULL, 
	numGuns int(11) DEFAULT NULL, 
	bore int(11) DEFAULT NULL, 
	displacement int(11) DEFAULT NULL, 
	PRIMARY KEY (class)
);

INSERT INTO classes VALUES 
('Bismarck', 'bb', 'Germany', 8, 15, 42000), 
('Iowa', 'bb', 'USA', 9, 16, 46000), 
('Kongo', 'bc', 'Japan', 8, 14, 32000), 
('North Carolina', 'bb', 'USA', 9, 16, 37000), 
('Renown', 'bc', 'Gt. Britain', 6, 15, 32000), 
('Revenge', 'bb', 'Gt. Britain', 8, 15, 29000), 
('Tennessee', 'bb', 'USA', 12, 14, 32000), 
('Yamato', 'bb', 'Japan', 9, 18, 65000);


DROP TABLE IF EXISTS outcomes;

CREATE TABLE outcomes (
	ship varchar(50) NOT NULL, 
	battle varchar(100) DEFAULT NULL, 
	result varchar(20) DEFAULT NULL, 
	PRIMARY KEY (ship)
);


INSERT INTO outcomes VALUES
('Arizona', 'Pearl Harbor', 'sunk'), 
('Bismarck', 'Denmark Strait', 'sunk'), 
('California', 'Surigao Strait', 'ok'), 
('Duke of York', 'North Cape', 'ok'), 
('Fuso', 'Surigao Strait', 'sunk'), 
('Hood', 'Denmark Strait', 'sunk'), 
('King George V', 'Denmark Strait', 'ok'), 
('Kirishima', 'Guadalcanal', 'sunk'), 
('Prince of Wales', 'Denmark Strait', 'damaged'), 
('Rodney', 'Denmark Strait', 'ok'), 
('Scharnhorst', 'North Cape', 'sunk'), 
('South Dakota', 'Guadalcanal', 'damaged'), 
('Tennessee', 'Surigao Strait', 'ok'), 
('Washington', 'Guadalcanal', 'ok'), 
('West Virginia', 'Surigao Strait', 'ok'), 
('Yamashiro', 'Surigao Strait', 'sunk')
;


--
-- Table structure for table 'ships'
--

DROP TABLE IF EXISTS ships;

CREATE TABLE ships (
	name varchar(50), 
	class varchar(50) DEFAULT NULL, 
	launched int(11) DEFAULT NULL,
	PRIMARY KEY(name)
);


INSERT INTO ships VALUES 
('California', 'Tennessee', 1921), 
('Haruna', 'Kongo', 1915), 
('Hiei', 'Kongo', 1914), 
('Iowa', 'Iowa', 1943), 
('Kirishima', 'Kongo', 1915), 
('Kongo', 'Kongo', 1913), 
('Missouri', 'Iowa', 1944), 
('Musashi', 'Yamato', 1942), 
('New Jersey', 'Iowa', 1943), 
('North Carolina', 'North Carolina', 1941), 
('Ramillies', 'Revenge', 1917), 
('Renown', 'Renown', 1916), 
('Repulse', 'Renown', 1916), 
('Resolution', 'Revenge', 1916), 
('Revenge', 'Revenge', 1916), 
('Royal Oak', 'Revenge', 1916), 
('Royal Sovereign', 'Revenge', 1916), 
('Tennessee', 'Tennessee', 1920), 
('Washington', 'North Carolina', 1941), 
('Wisconsin', 'Iowa', 1944), 
('Yamato', 'Yamato', 1941)
;


SELECT DISTINCT o.ship, c.displacement, c.numGuns
FROM classes c, outcomes o, ships s
WHERE o.battle='Guadalcanal' AND
      o.ship IN (SELECT name FROM ships WHERE class IN (SELECT class FROM classes));
-- +------------+--------------+---------+
-- | ship       | displacement | numGuns |
-- +------------+--------------+---------+
-- | Kirishima  |        42000 |       8 |
-- | Washington |        42000 |       8 |
-- | Kirishima  |        46000 |       9 |
-- | Washington |        46000 |       9 |
-- | Kirishima  |        32000 |       8 |
-- | Washington |        32000 |       8 |
-- | Kirishima  |        37000 |       9 |
-- | Washington |        37000 |       9 |
-- | Kirishima  |        32000 |       6 |
-- | Washington |        32000 |       6 |
-- | Kirishima  |        29000 |       8 |
-- | Washington |        29000 |       8 |
-- | Kirishima  |        32000 |      12 |
-- | Washington |        32000 |      12 |
-- | Kirishima  |        65000 |       9 |
-- | Washington |        65000 |       9 |
-- +------------+--------------+---------+

SELECT DISTINCT o.ship, c.displacement, c.numGuns
FROM outcomes o, ships s, classes c
WHERE o.battle='Guadalcanal' AND o.ship IN (SELECT s.name FROM ships s WHERE class IN (SELECT c.class FROM classes c));
-- +------------+--------------+---------+
-- | ship       | displacement | numGuns |
-- +------------+--------------+---------+
-- | Kirishima  |        42000 |       8 |
-- | Washington |        42000 |       8 |
-- | Kirishima  |        46000 |       9 |
-- | Washington |        46000 |       9 |
-- | Kirishima  |        32000 |       8 |
-- | Washington |        32000 |       8 |
-- | Kirishima  |        37000 |       9 |
-- | Washington |        37000 |       9 |
-- | Kirishima  |        32000 |       6 |
-- | Washington |        32000 |       6 |
-- | Kirishima  |        29000 |       8 |
-- | Washington |        29000 |       8 |
-- | Kirishima  |        32000 |      12 |
-- | Washington |        32000 |      12 |
-- | Kirishima  |        65000 |       9 |
-- | Washington |        65000 |       9 |
-- +------------+--------------+---------+