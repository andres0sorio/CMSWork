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
parser.add_option("-f", type = "string", dest="infile",
                  help="File name", metavar="INFILE" )

(options, args) = parser.parse_args()

if options.infile is None:
        parser.error("please give an input file")

#-----------------------------------------------------
#-----------------------------------------------------

infile    = options.infile
fullinfo  = open(infile,'r')
rawname   = infile.split('.')
outfile   = open(rawname[0] + '-ready.csv','w')

for line in fullinfo.readlines():
	info = []
	rawinfo = line[:-1].split('/')
	sample = rawinfo[1].replace('RelVal','')
	info.append( sample )
	cmssw = rawinfo[2].split('-')[0]
	info.append( cmssw )
	gtag = rawinfo[2].split('-')[1]
	info.append( gtag )
	dataset = rawinfo[3].replace('GEN-SIM-RECO','GEN-SIM-DIGI-RAW-HLTDEBUG')
	info.append( dataset )
	for column in info:
		outfile.writelines( column + '\t' )
	outfile.writelines('\n')

outfile.close()
fullinfo.close()


print 'Okey. all done'

