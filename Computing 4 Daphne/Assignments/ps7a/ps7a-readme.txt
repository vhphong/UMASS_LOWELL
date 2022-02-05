/**********************************************************************
 *  readme.txt template                                                   
 *  Kronos PS7a startup
 **********************************************************************/

Name: Dangnhi Ngo


Hours to complete assignment (optional): 25 hours


/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/
I completed this assignment successfully.
I have compared my output with the device5_intouch.log_BOOTONLY.rpt file
and seen that they looked like the same.
My output prints out the Boot time or Incomplete boot.

/**********************************************************************
 *  Copy here all regex's you created for parsing the file, 
 *  and explain individually what each ones does.
 **********************************************************************/
std::string regex_st =
"([0-9]+)-([0-9]+)-([0-9]+) "
"([0-9]+):([0-9]+):([0-9]+): "
".*\\(log.c.166\\) server started.*";

std::string regex_ed =
"([0-9]+)-([0-9]+)-([0-9]+) "
"([0-9]+):([0-9]+):([0-9]+).([0-9]+):INFO:"
"oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080.*";
regex begin_boot(regex_st);
regex end_boot(regex_ed);

([0-9]+)-: the number range from 0-9 is checked 
+: more than one number
-: character is checked.
"\\(log.c.166\\) server started.*": seeking for the sentence without the "(log.c.166)".
":INFO:oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080.*": the boot is completed

/**********************************************************************
 *  Describe your overall approach for solving the problem.
 *  100-200 words.
 **********************************************************************/
I created two regrexes regex_st and regex_ed to check the begin and finish
string. Then, I have used the regrex_match to check if the new line matched 
with the regex begin and end.
if (regex_match(pos, startT, begin_boot))
else if (regex_match(pos, endT, end_boot))
Then, calculate the time starts and ends to compute the time process.
<< " Boot Time: " << time_d.total_milliseconds() << "ms\n" << std::endl;
If the boot is not completed, it will print out the result below:
if (!isCompleted) {
outputfile << "**** Incomplete boot ****\n" << std::endl;
}

/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/
I have discussed this assignment with  my friends to solve the solutions
for difficult cases.


/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
I have trouble in calculating the time start and time end, which causes
the time process for the boot is not correct.


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
None.


