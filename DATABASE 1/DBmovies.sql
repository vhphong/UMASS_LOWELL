-- Practice of Aggregations:

-- Movies(title, year, length, genre, studioName; producerC#) 
-- Starsin(movieTitle, movieYear, starName) 
-- MovieStar(name, address, gender, birthdate) 
-- MovieExec(name, address, cert#, netWorth) 
-- Studio(name, address, presC#) 

CREATE DATABASE movies;
USE movies;
CREATE TABLE movies(
    title VARCHAR(100),
    year INT,
    length INT,
    genre VARCHAR(50), 
    studioName VARCHAR(100), 
    producerC VARCHAR(100),
    PRIMARY KEY (title, year)
);

CREATE TABLE starsin(
    movieTitle      VARCHAR(100), 
    movieYear       INT, 
    starName        VARCHAR(200),
    PRIMARY KEY     (movieTitle, movieYear, starName)
);

CREATE TABLE moviestar(
    name            VARCHAR(100), 
    address         VARCHAR(100), 
    gender          CHAR, 
    birthdate       DATE,
    PRIMARY KEY     (name)
);

CREATE TABLE movieexec(
    name            VARCHAR(100),
    address         VARCHAR(100),
    certnum         INT,
    networth        INT,
    PRIMARY KEY     (certnum)
);

CREATE TABLE studio(
	name VARCHAR(100),
	address VARCHAR(100),
	presC INT,
	PRIMARY KEY (name)
);


-- Movies(title, year, length, genre, studioName; producerC#) 
-- Starsin(movieTitle, movieYear, starName) 
-- MovieStar(name, address, gender, birthdate)
-- MovieExec(name, address, cert#, netWorth) 
-- Studio(name, address, presC#) 

-- 1) Find the title of the longest movie
SELECT title 
FROM movies 
WHERE length >= ALL(SELECT length FROM movies);
-- or
SELECT title 
FROM movies 
WHERE length = (SELECT MAX(length) FROM movies);

-- 2) Find the year in which most movies are made
SELECT year 
FROM movies
GROUP BY year 
HAVING COUNT(*) >= ALL(SELECT COUNT(*) FROM movies GROUP BY year);
-- or 
SELECT year 
FROM movies
GROUP BY year
HAVING COUNT (*) = (SELECT MAX(COUNT(*) FROM movies GROUP BY year);

-- 3) Find the title of movies that have more than two stars
SELECT movieTitle
FROM Starsin
GROUP BY movieTitle, movieYear 
HAVING COUNT(starName)>2;

-- 4) Find the number of stars in each movie
SELECT movieTitle, movieYear, COUNT(starName) -- differentiate movieTitle by movieYear. Two films may have the same title but different year.
FROM Starsin
GROUP BY movieTitle, movieYear;
-- or
SELECT m.year, COUNT(name) 
FROM starsin s, movies m 
WHERE m.title=s.title AND m.year=s.year 
GROUP BY m.title, m.year;

-- 5) Find the title of movies that have most number of stars have starred in it and list the stars name
SELECT movieTitle, movieYear, starName
FROM starsin
WHERE (movieTitle, movieYear) IN (SELECT movieTitle, movieYear
								  FROM starsin
								  GROUP BY movieTitle, movieYear
								  HAVING COUNT(starName) >= ALL(SELECT COUNT(starName)
																FROM starsin 
																GROUP BY movieTitle, movieYear));

-- 6) Find name of stars who have starred in every genre of movies.
-- Number of genres that the stars starred in = number of available genres
SELECT starName 
FROM starsin s, movies m1 
WHERE s.movieTitle=m1.title AND s.movieYear=m1.year 
GROUP BY starName 
HAVING COUNT(DISTINCT m1.genre) = (SELECT COUNT(DISTINCT m2.genre)
								   FROM movies m2);

-- Movies(title, year, length, genre, studioName; producerC#) 
-- Starsin(movieTitle, movieYear, starName) 
-- MovieStar(name, address, gender, birthdate) 
-- MovieExec(name, address, cert#, netWorth) 
-- Studio(name, address, presC#) 