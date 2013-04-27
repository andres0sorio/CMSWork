#!/usr/bin/python

import sys, os
from optparse import OptionParser

#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="cfgfile",
                  help="Configuration file" )

(options, args) = parser.parse_args()

if options.cfgfile is None:
        parser.error("please give the configuration file")

#--------------------------------------------------------
cfgfile   = options.cfgfile
#--------------------------------------------------------

infile = open( cfgfile, 'r' )

for line in infile.readlines():
	info = line[:-1].split(',')[0]
	vardef = os.getenv(info)
	value = ''
	if vardef == None:
		value = 'X'
	else:
		value = vardef
	print info, " = ", value


	


