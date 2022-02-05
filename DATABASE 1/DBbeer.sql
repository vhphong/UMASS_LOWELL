-- Beers(name, manf)
-- Bars(name, addr, license)
-- Drinkers(name, addr, phone)
-- Likes(drinker, beer)
-- Sells(bar, beer, price)
-- Frequents(drinker, bar)

CREATE TABLE bars (
  name varchar(50) DEFAULT '' NOT NULL,
  license varchar(7) DEFAULT NULL,
  city varchar(50) DEFAULT NULL,
  phone varchar(12) DEFAULT NULL,
  addr varchar(200) DEFAULT NULL,
  PRIMARY KEY (name)
);
CREATE TABLE beers (
  name varchar(50) DEFAULT '' NOT NULL,
  manf varchar(50) DEFAULT NULL,
  PRIMARY KEY (name)
);
CREATE TABLE drinkers (
  name varchar(50) DEFAULT '' NOT NULL,
  city varchar(50) DEFAULT NULL,
  phone varchar(12) DEFAULT NULL,
  addr varchar(200) DEFAULT NULL,
  PRIMARY KEY (name)
);
CREATE TABLE frequents (
  drinker varchar(50) DEFAULT '' NOT NULL,
  bar varchar(50) DEFAULT '' NOT NULL,
  PRIMARY KEY (drinker,bar),
  CONSTRAINT fk_frequents_bar FOREIGN KEY (bar) REFERENCES bars (name),
  CONSTRAINT fk_frequents_drinker FOREIGN KEY (drinker) REFERENCES drinkers (name)
);
CREATE TABLE likes (
  drinker varchar(50) DEFAULT '' NOT NULL,
  beer varchar(50) DEFAULT '' NOT NULL,
  PRIMARY KEY (drinker,beer),
  CONSTRAINT fk_likes_beer FOREIGN KEY (beer) REFERENCES beers (name),
  CONSTRAINT fk_likes_drinker FOREIGN KEY (drinker) REFERENCES drinkers (name)
);
CREATE TABLE sells (
  bar varchar(50) DEFAULT '' NOT NULL,
  beer varchar(50) DEFAULT '' NOT NULL,
  price decimal(9,2) DEFAULT NULL,
  PRIMARY KEY (bar,beer),
  CONSTRAINT fk_sells_bar FOREIGN KEY (bar) REFERENCES bars (name),
  CONSTRAINT fk_sells_beer FOREIGN KEY (beer) REFERENCES beers (name)
);

---------------------------------------------------------------------------------------

INSERT INTO bars (name, license, city, phone, addr) VALUES ('A.P. Stump''s','MA12347','Boston',NULL,NULL);
INSERT INTO bars (name, license, city, phone, addr) VALUES ('Blue Angel','CA45678','San Francisco',NULL,NULL);
INSERT INTO bars (name, license, city, phone, addr) VALUES ('Blue Tattoo','CA45678','San Francisco','415-567-1289','1500 Market St.');
INSERT INTO bars (name, license, city, phone, addr) VALUES ('Britannia Arms','MA12346','Boston','345-567-1289',NULL);
INSERT INTO bars (name, license, city, phone, addr) VALUES ('Cabana','CA45678','San Francisco',NULL,'1200 California Ave.');
INSERT INTO bars (name, license, city, phone, addr) VALUES ('Caravan','IL12345','Chicago',NULL,NULL);
INSERT INTO bars (name, license, city, phone, addr) VALUES ('Club 175','CA45678','San Francisco','415-567-1289',NULL);
INSERT INTO bars (name, license, city, phone, addr) VALUES ('Coconut Willie''s Cocktail Lounge','CA45678','San Francisco','415-567-1289',NULL);
INSERT INTO bars (name, license, city, phone, addr) VALUES ('Eulipia','IL12346','Chicago','123-456-7890','1060 West Addison');
INSERT INTO bars (name, license, city, phone, addr) VALUES ('Gecko Grill','IL12348','Chicago',NULL,'1060 West Addison');
INSERT INTO bars (name, license, city, phone, addr) VALUES ('Giza Hookah Lounge','IL12349','Chicago','345-678-9012',NULL);
INSERT INTO bars (name, license, city, phone, addr) VALUES ('Hedley Club','NY12345','New York',NULL,'161st St and River Ave');
INSERT INTO bars (name, license, city, phone, addr) VALUES ('Il Fornaio','NY12346','New York',NULL,'161st St and River Ave');
INSERT INTO bars (name, license, city, phone, addr) VALUES ('Seven Bamboo','NY12347','New York',NULL,'161st St and River Ave');
INSERT INTO bars (name, license, city, phone, addr) VALUES ('The B-Hive','MA12348','Boston','345-567-1280',NULL);
INSERT INTO bars (name, license, city, phone, addr) VALUES ('The Backbeat','CA45678','San Francisco','415-567-1289',NULL);
INSERT INTO bars (name, license, city, phone, addr) VALUES ('The Blank Club','MA12349','Boston','345-567-1281',NULL);
INSERT INTO bars (name, license, city, phone, addr) VALUES ('The Shark and Rose','MA12345','Boston',NULL,NULL);


INSERT INTO beers VALUES
('Blue Moon','Coors Brewing Company'),
('Budweiser','Anheuser-Busch'),
('Creamy Dark','Jacob Leinenkugel Brewing Company'),
('Extra Gold','Coors Brewing Company'),
('Hefeweizen','Jacob Leinenkugel Brewing Company'),
('Hefeweizen Doppelbock','Jacob Leinenkugel Brewing Company'),
('ICEHOUSE','Plank Road Brewery'),
('Killian''s','Coors Brewing Company'),
('Michelob Amber Bock','Anheuser-Busch'),
('Michelob Golden Draft','Anheuser-Busch'),
('Michelob Golden Draft Light','Anheuser-Busch'),
('Michelob ULTRA','Anheuser-Busch'),
('Original Premium','Jacob Leinenkugel Brewing Company'),
('Original Premium Lager','Jacob Leinenkugel Brewing Company'),
('Original Premium Lager Dog','Plank Road Brewery'),
('Sauza Diablo','Miller Brewing Company'),
('Southpaw Light','Plank Road Brewery'),
('Stolichnaya Citrona','Miller Brewing Company'),
('Zima','Coors Brewing Company'),
('Zima Citrus','Coors Brewing Company');


INSERT INTO drinkers VALUES
('Bob','San Francisco','415-234-6789',NULL),
('Erik','San Francisco','415-234-6789',NULL),
('Herb','Boston',NULL,NULL),
('Jesse','San Francisco','415-234-6789',NULL),
('John','Chicago',NULL,'1060 West Addison'),
('Justin','Boston',NULL,NULL),
('Mike','Boston',NULL,NULL),
('Rebecca','Chicago',NULL,'1060 West Addison'),
('Tom','Chicago',NULL,'1060 West Addison'),
('Vince','New York','234-456-7890','161st St and River Ave')
;


INSERT INTO frequents VALUES
('Mike','A.P. Stump''s'),
('Erik','Blue Angel'),
('Jesse','Blue Angel'),
('Tom','Blue Angel'),
('Vince','Blue Angel'),
('John','Caravan'),
('Tom','Caravan'),
('Bob','Coconut Willie''s Cocktail Lounge'),
('Rebecca','Coconut Willie''s Cocktail Lounge'),
('Justin','Gecko Grill'),
('Rebecca','Gecko Grill'),
('Herb','Seven Bamboo'),
('Vince','Seven Bamboo'),
('Mike','The Shark and Rose')
;


INSERT INTO likes VALUES 
('John','Blue Moon'),
('Mike','Blue Moon'),
('John','Budweiser'),
('Mike','Budweiser'),
('John','Creamy Dark'),
('Mike','Creamy Dark'),
('Mike','Hefeweizen'),
('John','Killian''s'),
('John','Michelob Golden Draft'),
('Mike','Michelob Golden Draft Light'),
('John','Original Premium'),
('Mike','Original Premium Lager'),
('Jesse','Original Premium Lager Dog'),
('Mike','Original Premium Lager Dog'),
('John','Stolichnaya Citrona')
;


INSERT INTO sells VALUES 
('A.P. Stump''s','Hefeweizen',6.00),
('Blue Angel','Hefeweizen Doppelbock',5.50),
('Blue Angel','Original Premium Lager Dog',6.25),
('Blue Tattoo','Killian''s',6.00),
('Britannia Arms','Budweiser',6.50),
('Cabana','Budweiser',5.00),
('Cabana','Hefeweizen Doppelbock',7.00),
('Cabana','Original Premium Lager Dog',5.00),
('Caravan','Budweiser',5.50),
('Caravan','Original Premium Lager Dog',3.50),
('Club 175','Budweiser',4.50),
('Coconut Willie''s Cocktail Lounge','Budweiser',3.25),
('Eulipia','Hefeweizen Doppelbock',4.50),
('Gecko Grill','Budweiser',3.00),
('Giza Hookah Lounge','Stolichnaya Citrona',6.00),
('Hedley Club','Hefeweizen',8.00),
('Seven Bamboo','Budweiser',2.50),
('The B-Hive','Michelob Amber Bock',5.00),
('The Backbeat','Killian''s',3.50),
('The Blank Club','Budweiser',5.50),
('The Shark and Rose','Budweiser',4.50),
('The Shark and Rose','Original Premium Lager Dog',5.50)
;


-- Find the bars that don't sell any beer.
SELECT name
FROM Bars b
WHERE NOT EXISTS (SELECT bar FROM Sells WHERE bar=b.name);

-- B-1. Find the manufacture of the beers sold at Joe’s bar
		SELECT distinct manf FROM beers, sells WHERE name=beer and bar='Joe';
-- B-2. Find the name and price of the most expensive beer sold at Joe’s bar
		SELECT beer, price FROM sells WHERE bar='Joe' and price>=ALL(SELECT price FROM sells WHERE bar='Sue');
-- B-3. Find the name and price of the beer that Joe’s bar is selling it at a price lower than Sue's bar
		
-- B-4. Find the name of the beer is sold at both Joe’s bar and Sue’s bar

-- B-5. Find the name of the bar that sells all kinds of beer
		SELECT name FROM bars b WHERE NOT EXISTS (SELECT name FROM beers WHERE name NOT IN (SELECT beer FROM sells s WHERE s.bar=b.name));
			-- => Sue
-- Find the beers that are the unique beer made by their manufacturers

-- Find for each drinker the average price of Bud at the bars they frequent
SELECT drinker, AVG(price) 
FROM frequents, sells 
WHERE sells.beer='Bud' AND sells.bar=frequents.bar 
GROUP BY drinker;
