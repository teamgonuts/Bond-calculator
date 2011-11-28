# to debug shell script put this in first line:  #!/bin/sh -x

echo "calling user is: \"`id -un`\" at: `date`"
# embed his in main system()

EXECUTABLE=./testdriver
ERROR_LOGFILE=error_logfile
# DATA_INPUT_FILE="./midterm.txt"
FILEPATH="/files/"
DATA_OPENING_INPUT_FILE="tradingbook_opening_original.txt"
DATA_CLOSING_INPUT_FILE="tradingbook_closing_original.txt"

YC_INPUT_FILE="yieldcurve.txt"

echo "passing param: $DATA_OPENING_INPUT_FILE $DATA_CLOSING_INPUT_FILE $YC_INPUT_FILE $FILEPATH executable: $EXECUTABLE" 
echo

SBB_DEBUG=1; 
export SBB_DEBUG

echo "======= spawning executable ======="
$EXECUTABLE  $DATA_OPENING_INPUT_FILE $DATA_CLOSING_INPUT_FILE  $YC_INPUT_FILE $FILEPATH  2> $ERROR_LOGFILE >&1
# unix shell built in environment variable for return code is $?
# standard is to return 0 if successful, positive otherwise
ret=$?

# standard unix practice is if an executable returns a non-zero code then it failed 
if [ $ret -ne 0 ]
then
	echo my program returned non-zero return code: $ret
	echo "prog failed"
	[ -s $ERROR_LOGFILE ] && cat $ERROR_LOGFILE
	exit
fi


# quick and dirty to measure file size
#FILESIZE=`ls -lh $EXECUTABLE | awk '{print $5}'`
#echo executable file size on disk reported from "ls" is: $FILESIZE
#EXECUTABLE_COPY="$EXECUTABLE"copy
#cp $EXECUTABLE $EXECUTABLE_COPY
#strip $EXECUTABLE_COPY
#FILESIZE=`ls -lh $EXECUTABLE_COPY | awk '{print $5}'`
#echo with debug stripped executable file size is: $FILESIZE
