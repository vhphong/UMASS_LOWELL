/**********************************************************************

Student name: Phong Hong Vo
UML CS account: pvo
Assignment: ps6 - MARKOV MODEL OF NATURAL LANGUAGE
Time spent: 25 hours

/**********************************************************************

Operating System: Windows 10 64 bit and Ubuntu 18.04
CPU type: Intel Core i5-8250U @ 1.6GHz
RAM: 8GB
Editor tool: notepad++ on Windows 10 and built-in textEditor on Ubuntu 18.04

/**********************************************************************

Introduction: This assignment is to enumerate any of character strings length 
in a string using Markov model 'text'.
The output of the program is data set of kgram following by its time it appears in the string and the rate 

/**********************************************************************
These are two results from the program with variaty of substring's length (3 then 2).
The following syntax is to apply Markov model to enumerate of occurence of 3-char substring 
in the original string.

phongvo@phongvo-X510UAR:/media/phongvo/PNY16GB/ps6$ ./TextGenerator 3 6 < markov/input53.txt
aaaaaa
kgram	freq	 rate
----------------------

Xaa	 	 3	 	3/53
XaaX	 0
Xaaa	 3
Xaac	 0

Xca	 	 1	 	1/53
XcaX	 0
Xcaa	 1
Xcac	 0

aXa	 	 3	 	3/53
aXaX	 0
aXaa	 3
aXac	 0

aXc	 	 1	 	1/53
aXcX	 0
aXca	 1
aXcc	 0

aaX	 	 4	 	4/53
aaXX	 0
aaXa	 3
aaXc	 1

aaa	 	 40	 	40/53
aaaX	 4
aaaa	 36
aaac	 0

caa	 	 1	 	1/53
caaX	 0
caaa	 1
caac	 0

-------------------------------------------------------

The following syntax is to apply Markov model to enumerate of occurence of 2-char substring 
in the original string.
phongvo@phongvo-X510UAR:/media/phongvo/PNY16GB/ps6$ ./TextGenerator 2 6 < markov/input53.txt
aaaaaa
kgram	freq	 rate
----------------------

Xa	 	3	 	3/53
XaX	 	0
Xaa	 	3
Xac	 	0

Xc	 	1	 	1/53
XcX	 	0
Xca	 	1
Xcc	 	0

aX	 	4	 	4/53
aXX	 	0
aXa	 	3
aXc	 	1

aa	 	44	 	44/53
aaX	 	4
aaa	 	40
aac	 	0

ca	 	1	 	1/53
caX	 	0
caa	 	1
cac	 	0

/**********************************************************************

By running ./mmtest, I found no errors occurred.
phongvo@phongvo-X510UAR:/media/phongvo/PNY16GB/ps6$ ./mmtest
Running 3 test cases...

*** No errors detected

/**********************************************************************
