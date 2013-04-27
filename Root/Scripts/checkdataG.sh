#!/bin/bash
## Andres Osorio - aooliver@ph.ed.ac.uk
##

if [ $# -lt 1 ]
    then
    echo "usage:: $0 <root File>"
    exit 1
fi

rootFile=$1

failed="./failedjobs"

EXEC=$PWD/checkdata

`find . -name "$rootFile" | sort > list_of_results.txt`

infile="list_of_results.txt"

files=(`cat $infile`)
len1=`echo ${#files[*]}`

var='0'

while [ "$var" -lt "$len1" ]
  do
  
    $EXEC ${files[$var]} 
    var=$(($var+1))
  
done

