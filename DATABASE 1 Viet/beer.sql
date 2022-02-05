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
