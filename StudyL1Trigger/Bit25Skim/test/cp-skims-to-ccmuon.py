#!/usr/bin/python

import os,sys
import string

# ...
# Andres Osorio - aosorio@uniandes.edu.co
# .

from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()

parser.add_option("-f", type = "string", dest="runlist",
                  help="Run info list" )

(options, args) = parser.parse_args()

if options.runlist is None:
        parser.error("please provide a run list")

#-----------------------------------------------------
#-----------------------------------------------------


print 'Copying files: '

runlist   = options.runlist
inputfile = open(runlist,'r')

cpmethod = 'rfcp'
cpopts   = ' '

tprefix  = ' /castor/cern.ch/user/c/ccmuon/RPC/GlobalRuns/FirstCollisions/TTUSkims/'

nfiles=0

for line in inputfile.readlines():
    
    source   = line[:-1]
    filename = source.split('/')[-1]
    target   = tprefix  + filename
    command  = cpmethod + cpopts + source + target  
    print command
    os.system(command)
    nfiles+=1

print 'Done. Total files: ', (nfiles-1)

