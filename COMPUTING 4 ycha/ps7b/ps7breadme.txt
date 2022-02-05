/**********************************************************************
 *  readme.txt template                                                   
 *  Kronos PS7b complete
 **********************************************************************/

Name: Yoo Min Cha
CS Login: ycha@cs.uml.edu


Hours to complete assignment (optional): 2


/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/

I completed most of the assignment, the only thing I wasn't sure of was when the service startups failed.  I surveyed the log files but there are just too many entries to find a specific service startup failing.  

/**********************************************************************
 *  Copy here all regex's you created for parsing the file, 
 *  and explain individually what each ones does.
 **********************************************************************/

    timeRegex=".*((\\d{4})-(\\d{2})-(\\d{2})).(\\d{2}):(\\d{2}):(\\d{2}).*";
Find the date and time for each entry because service startups do not have a time tag.
First string is date, second is time.  I used d for decimals and {n} where n is the number of decimals for each tag. Parenthesis groups up the tags.

    serviceStartRegex=".*(Starting Service).*";
Find all the starting service messages.

    successRegex=".*(Service started).*";
Find all the successful startups messages.

    startUpgrade=".*(Install started).*";
Start of install has this tag.

    endUpgrade=".*(ExitValue from install command : 0).*";
successful startup has exitvalue 0.

    newApp=".*(Processing)(.*)(intouch-application-base-)(.*)(\\.armv6jel_vfp\\.rpm)(.*)";
Find new app version by using the the (.*) between the intouch app tag and the .armv6jel tag.

    oldApp=".*(removing intouch-application-base-)(.*)(\\.armv6jel_vfp\\.rpm)(.*)";
Find the old app version by using (.*) between the removing tag and the .armv6 tag.

/**********************************************************************
 *  Describe your overall approach for solving the problem.
 *  100-200 words.
 **********************************************************************/

My overall approach was the find the appropriate regex match for each of these services.  For the updates I had a flag that would indicate the beginnin of the update and the matching completion of update.  There was an issue with certain entries in the log starting off with the completion of an update even though the start was never indicated.  The same with the opposite issue of starting but no completion.  Any Nested start install of upgrades were sorted out as failed upgrades.  I used a update the time for each entry so that I would had the nearest time point right before the service startup and would use these time entries as the time output for the following service startup.

/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/

I had no help.

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/



/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/


