-- UNIVERSITY OF MASSACHUSETTS - LOWELL
-- COMP3090: DATABASE I
-- STUDENT: PHONG VO - SID: 01790283
-- HOMEWORK 5
-------------------------------------------------------
-- Product(maker, model, type)                        |
-- PC(model, speed, ram, hd, price)                   |
-- Laptop(model, speed, ram, hd, screen, price)       |
-- Printer(model, color, type, price)                 |
-------------------------------------------------------

-- a) Find the average speed of PC's.
SELECT AVG(speed) AS Average_PC_Speed
FROM pc;
-- +--------------------+
-- | Average_PC_Speed   |
-- +--------------------+
-- | 2.4846153809474063 |
-- +--------------------+

-- b) Find the average speed of laptops costing over $1000.
SELECT AVG(speed) AS Avg_Speed_laptop_over1K
FROM laptop
WHERE price > 1000;
-- +-------------------------+
-- | Avg_Speed_laptop_over1K |
-- +-------------------------+
-- |      1.9983333547910054 |
-- +-------------------------+

-- c)  Find the average price of PC's made by manufacturer "A" 
SELECT AVG(price) AS Avg_Price_PC_A
FROM pc
WHERE model IN (SELECT model
                FROM product
                WHERE maker='A');
-- or
SELECT AVG(price) AS Avg_Price_PC_A
FROM pc, product
WHERE pc.model=product.model AND product.maker='A';
-- +--------------------+
-- | Avg_Price_PC_A     |
-- +--------------------+
-- | 1195.6666666666667 |
-- +--------------------+

-- ! d) Find the average price of PC's and laptops made by manufacturer "D"
SELECT AVG(price) AS PCLaptop_Avg_Price_By_D
FROM (SELECT model, price FROM pc
      UNION
      SELECT model, price FROM laptop) pclaptop
WHERE pclaptop.model IN (SELECT model
                         FROM product 
                         WHERE maker='D')
;
-- or
SELECT AVG(price) AS PCLaptop_Avg_Price_By_D
FROM (SELECT model, price FROM pc
      UNION
      SELECT model, price FROM laptop) pclaptop, product p
WHERE p.model=pclaptop.model AND p.maker='D'
;
-- +-------------------------+
-- | PCLaptop_Avg_Price_By_D |
-- +-------------------------+
-- |                     730 |
-- +-------------------------+

-- e) Find, for each different speed, the average price of a PC.
SELECT speed, AVG(price) AS PC_Average_Price
FROM pc 
GROUP BY speed;
-- +-------+-------------------+
-- | speed | PC_Average_Price  |
-- +-------+-------------------+
-- |  1.42 |               478 |
-- |  1.86 |               959 |
-- |     2 |               650 |
-- |   2.1 |               995 |
-- |   2.2 |               640 |
-- |  2.66 |              2114 |
-- |   2.8 | 689.3333333333334 |
-- |  3.06 |               529 |
-- |   3.2 |             839.5 |
-- +-------+-------------------+

-- ! f)  Find for each manufacturer, the average screen size of its laptops.
SELECT maker, AVG(screen) AS Average_Screen_Size
FROM product p, laptop l
WHERE l.model IN (SELECT p.model 
                  FROM product) 
GROUP BY maker;
-- or
SELECT maker, AVG(screen) AS Average_Screen_Size
FROM product, laptop
WHERE product.model = laptop.model
GROUP BY maker;
-- +-------+---------------------+
-- | maker | Average_Screen_Size |
-- +-------+---------------------+
-- | A     |  15.233333269755045 |
-- | B     |  13.300000190734863 |
-- | E     |                17.5 |
-- | F     |               14.75 |
-- | G     |  15.399999618530273 |
-- +-------+---------------------+

-- ! g)  Find the manufacturers that make at least three different models of PC. 
SELECT maker AS PC_Makers
FROM product
WHERE type='pc'
GROUP BY maker
HAVING COUNT(maker) >=3;
-- or
SELECT maker AS PC_Makers
FROM product 
WHERE model IN (SELECT model FROM pc)
GROUP BY maker
HAVING COUNT(maker) >= 3;
-- or
SELECT maker AS PC_Makers
FROM product, pc
WHERE product.model = pc.model
GROUP BY maker
HAVING COUNT(maker) >= 3;
-- +-----------+
-- | PC_Makers |
-- +-----------+
-- | A         |
-- | B         |
-- | D         |
-- | E         |
-- +-----------+

-- ! h) Find for each manufacturer who sells PC's the maximum price of a PC.
SELECT maker, MAX(pc.price) AS Max_Price
FROM product p, pc pc
WHERE p.model=pc.model
GROUP BY maker;
-- +-------+-----------+
-- | maker | Max_Price |
-- +-------+-----------+
-- | A     |      2114 |
-- | B     |      1049 |
-- | C     |       510 |
-- | D     |       770 |
-- | E     |       959 |
-- +-------+-----------+

-- ! i)  Find, for each speed of PC above 2.0, the average price.
SELECT speed, AVG(price) AS Average_Price
FROM pc 
WHERE speed IN (SELECT DISTINCT speed 
                FROM pc 
                WHERE speed > 2.0)
GROUP BY speed;
-- +-------+-------------------+
-- | speed | Average_Price     |
-- +-------+-------------------+
-- |   2.1 |               995 |
-- |   2.2 |               640 |
-- |  2.66 |              2114 |
-- |   2.8 | 689.3333333333334 |
-- |  3.06 |               529 |
-- |   3.2 |             839.5 |
-- +-------+-------------------+

-- !! j)  Find the average hard disk size of a PC for all those manufacturers that make printers. 
SELECT AVG(hd) AS Average_HD_size
FROM pc 
WHERE model IN (SELECT model 
                FROM product 
                WHERE maker IN (SELECT maker 
                                FROM product 
                                WHERE type='printer'));
-- +-----------------+
-- | Average_HD_size |
-- +-----------------+
-- |             200 |
-- +-----------------+