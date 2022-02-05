/**********************************************************************
 *  readme.txt template                                                   
 *  Markov Model
 **********************************************************************/

Name: Dangnhi Ngo


Hours to complete assignment: 30 hours
/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/
The purpose of this assignment is to analyze an input text for transitions between k-grams (a fixed number of characters) and the following letter.

Through working on this assignment, I have known how to create a Markov 
model of order k from the given text as well as generate a string of length T characters by simulating a trajectory through the corresponding Markov chain.


  /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/
The algorithms of this assignment is to apply the Markov model of natural
languages. It creates an output table comprised of the kgrams, the number
of times it appears and the frequency of the following character.
It creates the trajectory by appending the random character selected at each step.
while ((unsigned) T > output.length()) {
  string temp(1, randk(kgram));
  output.append(temp);
  if (_order > 0) {
    kgram = kgram.substr(1);
  }
  str = kgram + temp;
  kgram = str;
}

/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Include code excerpts.
 **********************************************************************/
First of all, I create the a Markov model of order k from given text.
It is described in the function MarkovModel(string text, int k).
Then, I calculate the number of occurrences of kgram in text in function
freq(string kgram):
if (_order != 0) {
   return kk[kgram];
} else {
   return strOfChar.size();
}
Function freq(string kgram, char c) to calculate number of times that character c follows kgram:
if (_order == 0) {
   int num = 0;
   for (unsigned i = 0; i < strOfChar.size(); i++) {
      if (strOfChar[i] == c) {
        num++;
      }
   }
   return num;
} else {
   return kk[kgram + c];
}
Next, find the random character following given kgram in the function randk(string kgram):
   string temp;
   if (kgram.length() == (unsigned)_order) {
   if (freq(kgram) != 0) {
     for (unsigned i = 0 ; i <strOfChar.size() ; i++) {
        for (int j = 0; j < kk[kgram + strOfChar[i]]; j++) {
            temp.push_back(strOfChar[i]);
        }
     }
     return temp[rand() % temp.size()];
    }
Finally, generate a string of length T characters by simulating a trajectory through the corresponding Markov chain
if (kgram.length() == (unsigned)order()) {
    while ((unsigned) T > output.length()) {
        string temp(1, randk(kgram));
        output.append(temp);
        if (_order > 0) {
           kgram = kgram.substr(1);
        }
        str = kgram + temp;
        kgram = str;
    }
    return output;
}


/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/
Yes, I completed the whole assignment successfully.
When I run ./TextGenerator 2 6 < input17.txt, the output is below:
gagggg
kgram	freq	 prob
----------------------

aa	 2	 2/17
aaa	 1
aac	 0
aag	 1

ag	 5	 5/17
aga	 3
agc	 0
agg	 2

cg	 1	 1/17
cga	 1
cgc	 0
cgg	 0

ga	 5	 5/17
gaa	 1
gac	 0
gag	 4

gc	 1	 1/17
gca	 0
gcc	 0
gcg	 1

gg	 3	 3/17
gga	 1
ggc	 1
ggg	 1


/**********************************************************************
 *  Does your implementation pass the unit tests?
 *  Indicate yes or no, and explain how you know that it does or does not.
 **********************************************************************/
Yes, the implementation of my program passes the unit test.
When I run ./mmtest, it prints the output as below:
Running 3 test cases...

*** No errors detected
It means that the program has no error.



/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/
I discussed this assignment with my friends to figure out the problems 
in this assignment.


/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
I have problems when trying to print out the string with the given order.
That is caused in the function gen(string kgram, int T). The output was
printed out incorrectly. Then, I tried to use the method output.append(temp)
to give the right output.


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
None.


