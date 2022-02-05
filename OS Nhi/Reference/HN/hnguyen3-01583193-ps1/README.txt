/*******************************************************
	Name: Hung Q Nguyen
	Student ID: 01583193
    Email: Hung_Nguyen3@student.uml.edu
	Date: 1/31/2017
	Assignment 1
*******************************************************/

I think I have completed this assignment with 100% matches
with the requirement from prof.Moloney

I used the template code assign1.c and also used Assignment1-help
which is also provided on the website of prof.Moloney's. 

Sometime the kill process get timeout but not a big deal since 
all matches requirements and that process if pretty much fork 
from the template file from professor.

I also used union structure in the help file but I changed 
name of each elements in the union so that I can easily understood
what happen in my way.

    typedef union{
        int exit_status;
        struct{
        unsigned sig_ num:7;
        unsigned core_dmp:1;
        unsigned exit_num:8;
        }parts;
    }LE_Wait_Status;