#!/bin/bash
# This will update the journal file by appending user input as well as date the time user wrote their input.
looptest=y
while [ "$looptest" = y ]
do
echo -e "Hello!This program will help you update the journal file for project 2.Enter \n t for inserting content with timestamp \n e for entering contents without timestamp \n r for reading the journal file \n vi for opening the vi editor of the journal file \n l for inserting a divider "

read userinput
        case "$userinput" in
        "t")  date >>project2_team5;
        echo "The current timestamp has been entered, please enter the content now: ";
        read userinput2;
        echo -e " \n$userinput2">>project2_team5;
        echo "Do you want to open the file to check its content?Enter y or n";
        read userinput4
        if [ "$userinput4" = y ]
        then
         more project2_team5
        fi;;
        "l")echo -e "-------------------------------------------\n" >>project2_team5;;
        "L")echo -e "-------------------------------------------\n" >>project2_team5;;
        "T") date >>project2_team5;
        echo "The current timestamp has been entered, please enter the content now: ";
        read userinput6;
        echo -e "\n$userinput6">>project2_team5;
        echo "Do you want to open the file to check its content?Enter y or n";
        read userinput5
        if [ "$userinput5" = y ]
        then
         more project2_team5
        fi;;

        "e") echo "Please enter the content now: ";read userinput3
        echo "$userinput3">>project2_team5;
        echo "Do you want to open the file to check its content?Enter y or n";
        read userinput5
        if [ "$userinput5" = y ]
        then
         more project2_team5
        fi;;

        "E") echo "Please enter the content now: ";read userinput3
        echo "$userinput3">>project2_team5;
        echo "Do you want to open the file to check its content?Enter y or n";
        read userinput5
        if [ "$userinput5" = y ]
        then
         more project2_team5
        fi;;

        "r") more project2_team5;;

        "R") more project2_team5;;

        "vi") vi project2_team5;;

        "VI") vi project2_team5;;

        "Vi") vi project2_team5;;

        "vI") vi project2_team5;;
        *) echo "Please enter the above letters only!";;
        esac
echo -n "Do you want to keep editing?Enter y or n: ";
read looptest
        if [ "$looptest" = n ]
        then
        echo "Good luck with the project!"
        fi
done
