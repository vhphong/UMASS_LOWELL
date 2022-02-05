-- DOCTORS (D_ID, D_NAME, D_GENDER, D_AGE, D_SPECIALIZATION, D_YEARS_OF_EXPERIENCE, D_CONTACT, D_STREET, D_CITY)
-- PATIENTS (P_ID, P_NAME, P_GENDER, P_AGE, P_DISEASE, P_CONTACT, P_STREET, P_CITY)
-- NURSES (N_ID, N_NAME, N_SPECIALIZATION, N_SHIFT, N_STREET, N_CITY)
-- P_ASSIGNMENT (P_ID, D_ID)
-- N_ASSISTS (N_ID, D_ID)
-- TESTS (T_ID, T_NAME, P_ID, D_ID, T_DATE, T_RESULT)

-- 7) Find the doctor whose patients have the most different type of diseases.
-- (Your result should display the doctor's name.)
SELECT D_NAME AS DOCTORS_NAMES
FROM DOCTORS
WHERE D_ID IN (SELECT D_ID FROM P_ASSIGNMENT GROUP BY D_ID HAVING COUNT(*) >= ALL(SELECT COUNT(*) FROM P_ASSIGNMENT GROUP BY P_ID));
-- DOCTORS_NAMES
-- JAMES SMITH
-- JOHN JOHNSON
-- MICHAEL JONES
-- WILLIAM BROWN
-- MARY SMITH
-- PATRICIA JOHNSON
-- LINDA WILLIAMS
-- BARBARA JONES
-- ELIZABETH BROWN

-- Find the patient who has the most different type of diseases
SELECT P_ID
FROM P_ASSIGNMENT
GROUP BY P_ID
HAVING COUNT(*) >= ALL(select COUNT(*) FROM P_ASSIGNMENT GROUP BY P_ID);
-- P_ID
-- 1027
-- 1038


-- 8) List the city where the most number of doctors and nurses live in.
-- (Your result should display the city and the number.)
-- City where the most number of doctors live in
-- SQL version
(SELECT D_CITY
FROM DOCTORS
GROUP BY D_CITY
HAVING COUNT(*) >= ALL(SELECT COUNT(*) FROM DOCTORS GROUP BY D_CITY))
INTERSECT
(SELECT N_CITY
FROM NURSES
GROUP BY N_CITY
HAVING COUNT(*) >= ALL(SELECT COUNT(*) FROM NURSES GROUP BY N_CITY))
;

-- MS ACCESS version
SELECT DISTINCT D_CITY, N_CITY
FROM DOCTORS D, NURSES N
GROUP BY D_CITY, N_CITY
HAVING COUNT(D_CITY) >= ALL(SELECT COUNT(D_CITY) FROM DOCTORS GROUP BY D_CITY) AND
            COUNT(N_CITY) >= ALL(SELECT COUNT(N_CITY) FROM DOCTORS GROUP BY N_CITY)
;

-- Find all cities that all doctors and all nurses live in
-- Then find the max of count of the cities data set
-- Find all cities that all doctors and all nurses live in
SELECT D_CITY
FROM (SELECT D_CITY, N_CITY FROM DOCTORS D, NURSES N WHERE D.D_CITY = N.N_CITY)
;

-- Then find the max of count of the cities data set
SELECT D_CITY
FROM (SELECT D_CITY, N_CITY FROM DOCTORS D, NURSES N WHERE D.D_CITY = N.N_CITY)
GROUP BY D_CITY
HAVING COUNT(D_CITY) >= ALL()
;


































