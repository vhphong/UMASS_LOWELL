-- UNIVERSITY OF MASSACHUSETTS - LOWELL
-- COMP3090: DATABASE I
-- STUDENT: PHONG VO - SID: 01790283
-- HOMEWORK 6
-------------------------------------------------------
-- Product(maker, model, type)                     	  |
-- PC(model, speed, ram, hd, price)                   |
-- Laptop(model, speed, ram, hd, screen, price)       |
-- Printer(model, color, type, price)                 |
-------------------------------------------------------

-- a) Using two INSERT statements, store in the database the fact that PC model 1100 is made by manufacturer C, has speed 3.2, RAM 1024, hard disk 180, and sells for $2499.
		INSERT INTO product VALUES ('C', 1100, 'pc');
		INSERT INTO pc VALUES (1100, 3.2, 1024, 180, 2499);


--!b) Insert the facts that for every PC there is a laptop with the same manufacturer, speed, RAM, and hard disk, a 17-inch screen, a model number 1100 greater, and a price $500 more.
	INSERT INTO product
		(SELECT maker, model+1100,'laptop'
		 FROM product
		 WHERE type='pc');
	INSERT INTO laptop
		(SELECT model+1100, speed, ram, hd, 17, price+500
		 FROM PC);
		 

-- c) Delete all PC's with less than 100 gigabytes of hard disk. 
		DELETE FROM pc
		WHERE hd<100;
	  

-- d) Delete all laptops made by a manufacturer that doesn't make printers.
		DELETE FROM laptop
		WHERE model IN (SELECT model 
						FROM product 
						WHERE maker IN (SELECT DISTINCT maker 
										FROM product 
										WHERE maker NOT IN (SELECT maker 
															FROM product 
															WHERE type='printer')));


-- e) Manufacturer A buys manufacturer B. Change all products made by B so they are now made by A.
		UPDATE product
		SET maker='A'
		WHERE maker='B';


-- f) For each PC, double the amount of RAM and add 60 gigabytes to the amount of hard disk. (Remember that several attributes can be changed by one UPDATE statement.) 
		UPDATE pc
		SET ram=ram*2, hd=hd+60;


--!g) For each laptop made by manufacturer B, add one inch to the screen size and subtract $100 from the price.
		UPDATE laptop
		SET screen=screen+1, price=price-100
		WHERE model IN (SELECT model FROM product WHERE maker='B');