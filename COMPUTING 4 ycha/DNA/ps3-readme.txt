/**********************************************************************
 *  readme template                                                   
 *  DNA Sequence Alignment
 **********************************************************************/

Name: Yoo Min Cha
Login: yoo_cha@cs.uml.edu


Hours to complete assignment (optional):


/**********************************************************************
 *  Explain what you did to find the alignment itself.
 **********************************************************************/
I used a while loop so that I could control the number of iterations through the matrix,
depending on how many steps it would take to finish the alignment.  I would check the difference
between the current cell and the cells to the right and bottom to see if the penalty == 2, and 
if either of these were true, I would store the edit cost and then iterate the appropriate index
to move into that cell.  If it did not meet either of these conditions it would know to check 
the bottom right diagonal cell and store the edit cost depending on the result of the penalty
function, and then we would transition into that cell for further tracing.

/**********************************************************************
 * Does your code work correctly with the endgaps7.txt test file? 
 * 
 * This example should require you to insert a gap at the beginning
 * of the Y string and the end of the X string.
 **********************************************************************/
Input: atattat
tattata


Expected output:
Edit distance = 4
----------------
a - 2
t t 0
a a 0
t t 0
t t 0
a a 0
t t 0
- a 2

Execution time is 0.066961seconds. 


What happened:Insert gap at beginning of Y string and end of X string.



/**********************************************************************
 *  How much main memory does your computer have? Typical answers
 *  are 4GB and 2GB. If your machine has 1 GB or less, use a cluster
 *  machine for this readme (see the checklist for instructions).
 **********************************************************************/

4GB


/**********************************************************************
 *  For this question assume M=N. Look at your code and determine
 *  approximately how much memory it uses in bytes, as a function of 
 *  N. Give an answer of the form a * N^b for some constants a 
 *  and b, where b is an integer. Note chars are 2 bytes long, and 
 *  ints are 4 bytes long.
 *
 *  Provide a brief explanation.
 *
 *  What is the largest N that your program can handle if it is
 *  limited to 1GB (billion bytes) of memory?
 **********************************************************************/
a =4bytes
b = 2
largest N = 16384
1073741824/4 =268435456
sqrt(268435456)=16384

/**********************************************************************
 *  Were you able to run Valgrind's massif tool to verify that your
 *  implementation uses the expected amount of memory?
 *
 *  Answer yes, no, I didn't try, I tried and failed, or I used a 
 *  different tool.
 *
 *  If yes, paste in the ms_print top chart of memory use over time,
 *  and also indicate which file your code was solving.
 * 
 *  Explain if necessary.
/**********************************************************************
yes, it used double what I expected it to.  My calculations led me to 
believe I would only need around 400kb or so of heap space.  I ended up using 
way more than my previous estimate.

ms_print arguments: massif.out.18195
--------------------------------------------------------------------------------


    KB
1.141^                                                                       #
     |                                                                       #
     |                                                                       #
     |                                                                       #
     |                                                                    @ :#
     |                                                                    @ @#
     |                 