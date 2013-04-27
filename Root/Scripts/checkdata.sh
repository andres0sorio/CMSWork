#!/bin/bash
## Andres Osorio - aooliver@ph.ed.ac.uk
##

if [ $# -lt 1 ]
    then
    echo "usage:: $0 <list of files>"
    exit 1
fi

infile=$1

failed="./failedjobs"

EXEC=$PWD/checkdata

files=(`cat $infile`)
len1=`echo ${#files[*]}`

var='0'

while [ "$var" -lt "$len1" ]
  do
  
    $EXEC ${files[$var]} 
    var=$(($var+1))
  
done

