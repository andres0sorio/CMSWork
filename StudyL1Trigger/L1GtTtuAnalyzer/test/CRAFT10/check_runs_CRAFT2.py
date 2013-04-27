#!/usr/bin/python

import sys,os
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="runid",
                  help="All CRAFT2 runs", metavar="TABLE" )

(options, args) = parser.parse_args()

if options.runid is None:
        parser.error("Please give it an input file")
	
#-----------------------------------------------------
#-----------------------------------------------------

runid    = options.runid

cmd      = 'mv -v ' + runid + '/list_of_files.txt ' + runid + '/temp.txt'
os.system(cmd)

infileNm    = runid + '/temp.txt'
outfileNm   = runid + '/list_of_files.txt'

infileOp    = open( infileNm,  'r' )
outfileOp   = open( outfileNm, 'w' )

success = 0

for line in infileOp.readlines():
	if line.find('HAPPY') > 0:
		print success=success+1
	else:
		outfileOp.writelines( line )

infileOp.close()
outfileOp.close()

print "Total runs processed: ", success





