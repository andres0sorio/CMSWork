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

#cpmethod = 'srmcp '
#cpopts   = '-srm_protocol_version=2 -use_urlcopy_script=true -urlcopy= ${SRM_PATH}/sbin/url-copy.sh -debug'

cpmethod = 'lcg-cp '
cpopts = ''

#............... TO

tprefix  = ' srm://moboro.uniandes.edu.co:8446/srm/managerv2\?SFN=/dpm/uniandes.edu.co/home/cms'
tdir     = '/user/a/aosorio/gridfiles/SKIMS/Run2011A/MET/'

#............... FROM

sprefix = ' srm://srm-dcache.rcac.purdue.edu:8443/srm/managerv2\?SFN='
 
while 1:
    line     = fh.readline()
    if not line:
        break
    pass
    lfn      = line[8:-3]
    info     = lfn.split('/')
    filename = info[-1]

    source   = sprefix  + lfn
    target   = tprefix + tdir + filename
    command  = cpmethod + cpopts + source + target
    print command
    if debug == 'no':
	    os.system(command)

    nfiles+=1
    if debug == 'yes':
	    break

print 'Done. Total files: ', (nfiles-1)

