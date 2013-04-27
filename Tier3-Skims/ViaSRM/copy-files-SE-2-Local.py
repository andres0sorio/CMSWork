#!/usr/bin/python

import os,sys
import string
from optparse import OptionParser

# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="filelist",
                  help="List of LFNs" )

parser.add_option("-d", type = "string", dest="debug",
                  help="Are you in debug mode?" )

(options, args) = parser.parse_args()

if options.filelist is None:
        parser.error("please provide a file")

if options.debug is None:
        parser.error("please, are you in debug mode?")

#-----------------------------------------------------
#-----------------------------------------------------
nfiles = 0
filelist = options.filelist
debug = options.debug

print 'Copying files: '

fh    = open(filelist)

cpmethod = 'rfcp '

#............... TO
tdir     = '/scratch/aosorio/data/Skims/Run2011B/MET/'

while 1:

    line     = fh.readline()
    if not line:
        break
    pass

    info  = line[:-1].split('/')
    filename = info[-1]

    source   = line[:-1] + ' '
    target   = tdir + filename
    command  = cpmethod + source + target
    print command
    
    if debug == 'no':
	    if not os.path.isfile( target ):
		    os.system(command)
		    nfiles+=1

    if debug == 'yes':
	    break

print 'Done. Total files: ', (nfiles-1)

