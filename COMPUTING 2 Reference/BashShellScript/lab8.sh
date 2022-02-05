#!/bin/bash
#------------------------------------------------------------------------------
# Script to generate random data
#
# Course: 91.102 Computing II
# Author: Krishnan Seetharaman
#-----------------------------------------------------------------------------


#------------------------------------------------------------------------------
die()
# print error message and exit with failure error code;
#------------------------------------------------------------------------------
{
    echo "ERROR $1"
    exit 1
}

#------------------------------------------------------------------------------
checkErrorCode()
# check error code and die if error;
#------------------------------------------------------------------------------
{
    local err=$1
    local emsg="$2"

    [ $err -ne 0 ] && die "$emsg"
}

#------------------------------------------------------------------------------
usage()
# display usage for this script;
#------------------------------------------------------------------------------
{
cat << EOF
$0 is used to generate random (numeric or alphanumeric) data.
usage: $0 command [-h] [-c <cols>] [-d <delimiter>] [-r <rows>] [-s] [-u] 
                  [-w <width>] [-x] [H <highlimit>] [-L <lowlimit>] [-S]

  -h print this usage
  -c <cols>
     number of columns to generate; default is $NCOLUMNS
  -d <delimiter>
     delimiter to use for multi-column output; default is '$DELIMITER'
  -r <rows>
     number of rows to generate; default is $NROWS
  -s descending sort; default is $bDESC_SORT
  -u generate unique data; default is $bUNIQUE
  -w <width>
     width of alphanumeric data; default is $WIDTH
  -x generate alphanumeric data; default is $bALPHANUMERIC
  -H <highlimit>
     higher bound for random number; default is $HIGH_BOUND
  -L <lowFileSize>
     lower bound for random number; default is $LOW_BOUND
  -S ascending sort; default is $bASC_SORT

Example usage:

To run the $0 using defaults
$0

To run the $0 to generate unique data sorted ascending, 3 columns and 1000 rows:
$0 -u -S -c 3 -r 1000

To run the $0 to generate unique data sorted ascending in the range [0..255], 
3 columns and 1000 rows:
$0 -u -S -c 3 -r 1000 -L 0 -H 255

To run the $0 to generate alphanumeric data, 3 columns and 1000 rows:
$0 -x -c 3 -r 1000

To run the $0 to generate numeric data, 3 columns, 4 rows, sorted ascending, unique, and delimiter |:
$0 -c 3 -r 4 -S -L 10 -H 20 -u -d "|"
10|15|18
14|10|20
16|15|19
19|10|10

To run the $0 to generate alphanumeric data, 4 columns, 4 rows, unique, and delimiter ,:
$0  -c 4 -r 4 -u -x -d ","
qj7g0qJP3USHuDTq,7tIyr31Fp3AOclRU,fwPQygyVivv8HVT6,p76T8izT5nowEJ9i
iDdQz2Fgcl1FEBPx,h7ax7l1wKm17BbYv,ji6WW5jvoiScma9I,kAi3xdST0s4Tl2GZ
aFSssqixO9dotdpv,SrXkClXzJpnPu5Y5,HOgIsiahXfbOlI5O,lWHyKQ563LLsU0V7
1neS9lzYZjCE0S6B,Iq0cb0wQVsi1KIbJ,MeQa49JYTQBpSmAc,CW8Hw20YGGhrf8Y7

EOF

    exit 1
}

#------------------------------------------------------------------------------
setDefaults()
# set defaults 
#------------------------------------------------------------------------------
{
    # delimiter
    DELIMITER=" "

    # number of columns;
    NCOLUMNS=1

    # number of rows;
    NROWS=64
 
    # is descending sort;
    bDESC_SORT=0

    # width;
    WIDTH=16

    # is alphanumeric;
    bALPHANUMERIC=0

    # high bound;
    HIGH_BOUND=1000000

    # low bound;
    LOW_BOUND=0

    # is ascending sort;
    bASC_SORT=0

    # generate unique data;
    bUNIQUE=0
}

#------------------------------------------------------------------------------
generateData()
# generate random data as specified via command line args;
#------------------------------------------------------------------------------
{
local temp="out.txt"
>out.txt
row=0
col=0
if [ $bALPHANUMERIC -eq 1 ] #if alphanumeric flag is on
  then
    while [ $row -lt $NROWS ]
      do
        while [ $col -lt $NCOLUMNS ]
          do
            printf $(randomAlphaNumeric)>>$temp;
            (( col++ ))
            if [ $col -ne $NCOLUMNS ]
              then
              printf "$DELIMITER" >>$temp;
            fi  
          done
        let "col = 0"
        echo " " >>$temp  
        (( row++ ))
      done
else #generate numbers when alphanumeric flag is off
    while [ $row -lt $NROWS ]
      do
        while [ $col -lt $NCOLUMNS ]
          do
            printf $(randomNumeric)>>$temp 
            (( col++ ))
            if [ $col -ne $NCOLUMNS ]
              then
              printf "$DELIMITER" >>$temp;
            fi  
          done
        let "col = 0"
        echo " " >>$temp  
        (( row++ ))
      done      
fi

if [ $bUNIQUE -eq 1 -a $bDESC_SORT -eq 1 ]
  then
    cat out.txt|uniq|sort -r -t "$DELIMITER" -o out.txt|cat out.txt #reverse sort , use limiter to recognize fields and  output to file
   
elif [ $bUNIQUE -eq 1 -a $bASC_SORT -eq 1 ]
  then
    cat out.txt|uniq|sort -n -t "$DELIMITER" -o out.txt| cat out.txt  #sort ascending order ,use limiter to recogniz fields and output to file
  
elif [ $bUNIQUE -eq 1 ]
  then
    cat out.txt|uniq 
  
elif [ $bDESC_SORT -eq 1 ]
  then
    cat out.txt|sort -r -t "$DELIMITER" -o out.txt| cat out.txt 
    
elif [ $bASC_SORT -eq 1 ]
  then
     cat out.txt|sort -n -t "$DELIMITER" -o out.txt | cat out.txt 
     
fi


}

randomAlphaNumeric()
{
 echo $(cat /dev/urandom |tr -dc "a-zA-Z0-9"|fold -w $WIDTH|head -n 1)   
}

randomNumeric()
{
 echo $(($LOW_BOUND + $RANDOM % ($HIGH_BOUND + 1 - $LOW_BOUND))) 
}

#------------------------------------------------------------------------------
processArgs()
# args processing;
#------------------------------------------------------------------------------
{
    while getopts "c:d:hr:suw:xH:L:S" opt; do
      case "$opt" in
        c)
          NCOLUMNS=$OPTARG
          ;;
        d)
          DELIMITER=$OPTARG
          ;;
        h)
          usage
          ;;
        r)
          NROWS=$OPTARG
          ;;
        s)
          bDESC_SORT=1
          ;;
        u)
          bUNIQUE=1
          ;;
        w)
          WIDTH=$OPTARG
          ;;
        x)
          bALPHANUMERIC=1
          ;;
        H)
          HIGH_BOUND=$OPTARG
          ;;
        L)
          LOW_BOUND=$OPTARG
          ;;
        S)
          bASC_SORT=1
          ;;
        \?)
          echo "Invalid option: -$OPTARG" >&2
          usage
          ;;
      esac
    done

    # error checking
    [ $LOW_BOUND -gt $HIGH_BOUND ] && die "lowBound $LOW_BOUND is > highBound $HIGH_BOUND"
    [ $bDESC_SORT -eq 1 -a $bASC_SORT -eq 1 ] && die "Only ascending or descending"
    # TBD--add more error checking if required;

}

#------------------------------------------------------------------------------
# main processing
#------------------------------------------------------------------------------

setDefaults
processArgs "$@"

generateData

exit 0

