#!/usr/bin/python
# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...

import os,sys
import string

from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="infileA",
                  help="File name", metavar="INFILEA" )

parser.add_option("-r", type = "string", dest="run",
                  help="Run ID", metavar="RUN" )

(options, args) = parser.parse_args()

if options.infileA is None:
        parser.error("please give an input file")

if options.run is None:
        parser.error("please give a run id")

#-----------------------------------------------------
#-----------------------------------------------------

infileA    = options.infileA
run        = options.run

outfileA   = 'list_of_sorted_' + run + '.txt'

tmpfile    = 'tmp.out'

cmd = 'grep \"' + run + '\" ' + infileA + ' > ' + tmpfile
excode = os.system(cmd)

inputA     = open(tmpfile,'r')
outputA    = open(outfileA,'w')

for line in inputA.readlines():
	info = line[:-3].split()
	runid = info[2]
	file = info[-1]
	subjob = file.split('/')[-3]
	outputA.writelines( file + '\n' )


inputA.close()
outputA.close()

cmd = 'rm ' + tmpfile
excode = os.system(cmd)

print 'Okey. all done'

