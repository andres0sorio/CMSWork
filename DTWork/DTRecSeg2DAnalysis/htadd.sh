#!/bin/bash
# Andres Osorio - aooliver@ph.ed.ac.uk
#... this scripts uses ROOT's hadd to get the

if [ $# -lt 2 ]
    then
    echo "usage: $0 <target> <list of files>"
    exit 1
fi

output=$1
infile=$2

#....................................

files=(`cat $infile`)
tot=`echo ${#files[*]}`
if [ $tot -lt 2 ]
    then
    echo "need more than 2 files"
    exit 1
fi

#....................................

mxiter=$(($tot-1))

var='1'
file1=${files[0]}

for i in `seq 1 $mxiter`
  do
  
  target=target.root
  hadd $target $file1 ${files[$var]}
  mv $target temp.root
  file1=temp.root
  var=$(($var+1))
  
done

echo "done. Output file is: $output"
mv temp.root $output

