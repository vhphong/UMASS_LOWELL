/**********************************************************************
 *  readme.txt template                                                   
 *  Kronos PS7a startup
 **********************************************************************/

Name: Phong Hong Vo


Hours to complete assignment (optional): 25 hours


/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/
I have completed this ps7a assignment. 


/**********************************************************************
 *  Copy here all regex's you created for parsing the file, 
 *  and explain individually what each ones does.
 **********************************************************************/
std::string regex_begin = "([0-9]+)-([0-9]+)-([0-9]+) ([0-9]+):([0-9]+):([0-9]+): .*\\(log.c.166\\) server started.*";
std::string regex_end = "([0-9]+)-([0-9]+)-([0-9]+) ([0-9]+):([0-9]+):([0-9]+).([0-9]+):INFO: oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080.*";

where:
([0-9]+)- : any number in range 0->9 is checked
+ : one or more number
- : the character is checked
/**********************************************************************
 *  Describe your overall approach for solving the problem.
 *  100-200 words.
 **********************************************************************/
I created two regex strings named regex_begin and regex_end to check the begin and the end of the string.
The I used function regrex_match to check if the new line is matched with the regex begin and end (line 33->60 in main.cpp);
	if (regex_match(pos, startT, begin_boot))
	else if (regex_match(pos, endT, end_boot))
After that, I computed the amount of time to start and to stop to carry out the time of process.
	<< " Boot Time: " << time_d.total_milliseconds() << "ms\n" << std::endl;
If the boot is not completed, it will print out the result as the following format:
	if (!isCompleted) {
		outputfile << "**** Incomplete boot ****\n" << std::endl;
	}


/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/

I discussed with my friends to approach this assignment.

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/

I had lots of problems in computing the amount of time to start and stop.


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
none