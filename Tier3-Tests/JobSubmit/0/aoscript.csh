#!/bin/csh -f
#..................................................
#.. Andres Osorio - aosorio@uniandes.edu.co        

if ( $#argv != 1 ) then
   echo "usage: $0 filepath"
   goto done
endif

set message=$1
echo "--------"
echo "${message}"
echo "---End--"

#..................................................

done:
  exit 0
error:
  exit 1

