#!/usr/bin/python
import sys, os
from optparse import OptionParser
#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="filelist",
                 help="File list" )

(options, args) = parser.parse_args()

if options.filelist is None:
        parser.error("File list")
#--------------------------------------------------------
#--------------------------------------------------------

filelist = open( options.filelist, 'r')
outfile = open('step1-dataset-local.dat','w')

for item in filelist.readlines():
	source = item[:-1].replace('fisica/aosorio','home/aosorio/pbsserver')
	outfile.writelines( source + '\n')

outfile.close()

print 'Done!'	

