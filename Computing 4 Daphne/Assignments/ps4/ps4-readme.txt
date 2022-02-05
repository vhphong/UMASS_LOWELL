/**********************************************************************
 *  readme template                                                   
 *  DNA Sequence Alignment
 **********************************************************************/

Name: Dangnhi Ngo
Login: dngo


Hours to complete assignment (optional): 40 hours


/**********************************************************************
 *  Explain what you did to find the alignment itself.
 **********************************************************************/
First of all, I used the function int ED::OptDistance() to create the table
for two strings and fill in all the cells in that table with suitable
number. Also, I have used 2 more functions ED::penalty(char a, char b)
(used to find the number that position opt[i+1][j+1] should add is 0 or 1)
and ED::min(int a, int b, int c) (used to find the minimum values in 3 
numbers). Finally, this function returns the optimal edit distance at
the position opt[0][0].
Next, I used the function std::string ED::Alignment() to print out the
alignment for 2 input strings.I followed exactly the rules described in
princeton, part "Recovering the alignment itself" to find the appropriate
letter, gap and cost.


/**********************************************************************
 * Does your code work correctly with the endgaps7.txt test file? 
 * 
 * This example should require you to insert a gap at the beginning
 * of the Y string and the end of the X string.
 **********************************************************************/
Input: ./ED < sequence/endgaps7.txt

Expected output:
Edit distance = 4
a - 2
t t 0
a a 0
t t 0
t t 0
a a 0
t t 0
- a 2
Execution time is 8.7e-05 seconds

What happened: Same expected output


/**********************************************************************
 *  How much main memory does your computer have? Typical answers
 *  are 2 GB to 16 GB.
 **********************************************************************/
My computer has 16.0GB memory.


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
 *  limited to 8GB (billion bytes) of memory?
 **********************************************************************/
a = 4
b = 2
largest N = ~ 16384

Explanation: integers are 4 bytes long, chars are 2 bytes long
1 GB = 1,000,000,000 bytes =~ 2^30
a * N^b = 4 * N^2 = 2^30 ==> N =~ 16384
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
Yes, I am able to run Valgrind's massif tool
I used the file "example10.txt"

--------------------------------------------------------------------------------
  n        time(i)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
--------------------------------------------------------------------------------
 10      2,597,282           77,312           77,140           172            0
 11      2,597,338           77,368           77,176           192            0
 12      2,597,394           77,424           77,212           212            0
 13      2,597,450           77,480           77,248           232            0
 14      2,597,506           77,536           77,284           252            0
 15      2,623,944           78,568           78,308           260            0
 16      2,645,827           78,608           78,339           269            0
 17      2,646,497           78,680           78,400           280            0
 18      2,647,287           78,680           78,400           280            0
--------------------------------------------------------------------------------
  n        time(i)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
--------------------------------------------------------------------------------
 19      2,647,287           78,640           78,369           271            0
 20      2,663,493           78,568           78,308           260            0
 21      2,674,584           74,464           74,212           252            0
 22      2,674,616           73,432           73,188           244            0

                               

/**********************************************************************
 *  For each data file, fill in the edit distance computed by your
 *  program and the amount of time it takes to compute it.
 *
 *  If you get segmentation fault when allocating memory for the last
 *  two test cases (N=20000 and N=28284), note this, and skip filling
 *  out the last rows of the table.
 **********************************************************************/

data file           distance       time (seconds)     memory (MB)
------------------------------------------------------------------
ecoli2500.txt	      118          0.198126		24.02
ecoli5000.txt	      160	   2.13256	        95.65
ecoli7000.txt	      194          4.19628              187.3
ecoli10000.txt        223          8.37107              382.0 
ecoli20000.txt        3135         37.7313	        1491
ecoli28284.txt        8394	   150.579	        2981

/*************************************************************************
 *  Here are sample outputs from a run on a different machine for 
 *  comparison.
 ************************************************************************/

data file           distance       time (seconds)
-------------------------------------------------
ecoli2500.txt          118             0.171
ecoli5000.txt          160             0.529
ecoli7000.txt          194             0.990
ecoli10000.txt         223             1.972
ecoli20000.txt         3135            7.730

/**********************************************************************
 *  For this question assume M=N (which is true for the sample files 
 *  above). By applying the doubling method to the data points that you
 *  obtained, estimate the running time of your program in seconds as a 
 *  polynomial function a * N^b of N, where b is an integer.
 *  (If your data seems not to work, describe what went wrong and use 
 *  the sample data instead.)
 *
 *  Provide a brief justification/explanation of how you applied the
 *  doubling method.
 * 
 *  What is the largest N your program can handle if it is limited to 1
 *  day of computation? Assume you have as much main memory as you need.
 **********************************************************************/
a = 4
b = 2
largest N = 16384

Explanation: a * N^b
With a = 4, N = 16384:
The ratio: 16384/7.73 =~ 2119.53

1 day = 86400 seconds
With N = 10000, it took 1.972 seconds
With N = 20000, it took 7.730 seconds
The larger the size is, the longer time it takes.


/**********************************************************************
 *  List whatever help (if any) you received from the course TAs,
 *  instructor, classmates, or anyone else.
 **********************************************************************/
I have discussed this assignment with some friends of mine to solve
problems.

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
I tried to use 1 std::string to print out the result alignment, but it failed; therefore, I decided to use 2 different str::string align and str::str to assign
each of value into the variable str.


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
None.

