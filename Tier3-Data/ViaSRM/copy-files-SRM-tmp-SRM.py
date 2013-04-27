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
parser.add_option("-f", type = "string", dest="infile",
                  help="List of LFNs" )

parser.add_option("-d", type = "string", dest="debug",
                  help="Are you in debug mode?" )

(options, args) = parser.parse_args()

if options.infile is None:
        parser.error("please provide a file")

if options.debug is None:
        parser.error("please, are you in debug mode?")

#-----------------------------------------------------
#-----------------------------------------------------

infile    = options.infile
debug     = options.debug

print 'Copying files: '

fh    = open(infile)
nfiles=0

cpmethod = 'srmcp '
rmmethod = 'rm '
cpopts   = '-srm_protocol_version=2 -use_urlcopy_script=true -urlcopy= ${SRM_PATH}/sbin/url-copy.sh'

#............... TO

localprefix = ' file:///'
tmp      = os.getenv('PWD') + '/'
tprefix  = ' srm://moboro.uniandes.edu.co:8446/srm/managerv2\?SFN=/dpm/uniandes.edu.co/home/cms'
tdir     = '/user/a/aosorio/gridfiles/RAW/Run2011B/L1Accept/'

#............... FROM

sprefix = ' srm://cmssrm.fnal.gov:8443/srm/managerv2\?SFN=/11'

host = os.getenv('HOST')
print "excecuting from: ", host

while 1:

    line     = fh.readline()

    if not line:
        break

    lfn      = line[8:-3]
    info     = lfn.split('/')
    filename = info[-1]

    #. Step 1 - SE -> Local
    source   = sprefix  + lfn
    target   = localprefix + tmp + filename
    command  = cpmethod + cpopts + source + target
    print command

    if debug == 'no':
	    os.system(command)

    #. Step 1 - Local -> SE
    source   = target
    target   = tprefix  + tdir   + filename
    command  = cpmethod + cpopts + source + target  
    print command
    if debug == 'no':
	    os.system(command)
    
    #. Clean up TMP
    command  = rmmethod +  tmp + filename
    print command
    if debug == 'no':
	    os.system(command)

    nfiles+=1

    if debug == 'yes':
	    break

print 'Done. Total files: ', (nfiles-1)

