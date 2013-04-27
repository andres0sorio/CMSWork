#!/usr/bin/python
import os,sys
import string
from optparse import OptionParser

#---------------------------------------------------------------------------
parser = OptionParser()
parser.add_option("-w", type = "string", dest="window",
                  help="Rate window", metavar="WINDOW" )

(options, args) = parser.parse_args()

if options.window is None:
        parser.error("please give time window")

#---------------------------------------------------------------------------
# ...
# Andres Osorio - aosorio@uniandes.edu.co
# .

window = options.window

cmd  = ''

cmd += './TtuCheckRates ' + ' '
cmd += '| /nfshome0/aosorio/TtuRatemon/exe/getRates'

print cmd

#data = os.popen( cmd , 'r' ).readlines()
#for lines in data:
#    print lines[:-1]

excode = os.system( cmd )

