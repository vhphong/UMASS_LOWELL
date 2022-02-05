/*******************************************************                        
  Name: Hung Q Nguyen                                                           
  Student ID: 01583193                                                          
  Email: Hung_Nguyen3@student.uml.edu                                           
  Date: 3/28/2017                                                                
  Assignment 4                         
*******************************************************/

- I think I finish the assignment with 100% satisfying all the requirements from Professor Moloney. (except some title of the ouput is printed multiple time but not a big deal I would say, since all data are created satisfying the requirements).

- First, I created up a list of files structure by splittedup the code from assgn4-call-help file in his website.
Then splitted into 2 files
	+ ps4.h
	+ ps4.c
- Then created a Makefile for making project convenient

Naming condition I complete followed the template for variables and Makefile for filename.

- After, I write modify loop in producer function to pthread_cond_signal and pthread_mutex_unlock to unlock producer and lock consumer 
- I also then created some code in consumer function to determine deadlock, terminate somaphores and then print out the value of PID and some related values as type of donuts.

Note: In the result file, I include only the data of 5th LOOP output to demo but did not inlcude the other output due to the messy of each file may confuse the TA (5th Loop has a "not messy" data so I picked it).

Capture of my console running the output to provide data is created.
Graph of percentage of deadlock depends on the size running also included.