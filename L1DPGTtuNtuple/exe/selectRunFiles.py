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

parser.add_option("-j", type = "string", dest="infileB",
                  help="File name", metavar="INFILEB" )

parser.add_option("-t", type = "string", dest="tagA",
                  help="Tag option", metavar="TAGA" )

parser.add_option("-s", type = "string", dest="tagB",
                  help="Tag option", metavar="TAGB" )

(options, args) = parser.parse_args()

if options.infileA is None:
        parser.error("please give an input file")

if options.tagA is None:
        parser.error("please give a tag")

#-----------------------------------------------------
#-----------------------------------------------------

infileA    = options.infileA
infileB    = options.infileB
tagA       = options.tagA
tagB       = options.tagB

outfileA   = 'list_of_sorted_' + tagA + '.txt'
outfileB   = 'list_of_sorted_' + tagB + '.txt'

inputA    = open(infileA,'r')
inputB    = open(infileB,'r')

outputA    = open(outfileA,'w')
outputB    = open(outfileB,'w')

for line in inputA.readlines():
	info = line[:-3].split()
	runid = info[2]
	file = info[-1]
	subjob = file.split('/')[-3]
	outputA.writelines( file + '\n' )

	for bline in inputB.readlines():
		info = bline[:-1]
		bfile = info
		subjobB = bfile.split('/')[-3]
		if subjob == subjobB:
			outputB.writelines( bfile + '\n')
			break
	inputB.seek(0)
	

inputA.close()
inputB.close()

outputA.close()
outputB.close()
	
print 'Okey. all done'

