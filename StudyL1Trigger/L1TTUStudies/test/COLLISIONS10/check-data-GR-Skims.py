#!/usr/bin/python
# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...

import os,sys
import string

from optparse import OptionParser
#---------------------------------------------------------------------------
#---------------------------------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="runid",
                  help="Run Id number", metavar="RUNID" )

parser.add_option("-s", type = "string", dest="subdirs",
                  help="Subdirs", metavar="SUBDIRS" )

(options, args) = parser.parse_args()

if options.runid is None:
        parser.error("please give a run number")

if options.subdirs is None:
        parser.error("please give a list of subdirs")

#---------------------------------------------------------------------------
#---------------------------------------------------------------------------

runid = options.runid
subdirs = options.subdirs.split(',')

lsmethod = 'rfdir'
mkdircmd = 'mkdir'

prefix   = '/castor/cern.ch/cms'
path     = '/store/data/Commissioning10/MinimumBias/RAW-RECO/'

excode = os.path.isdir(runid)
if excode != True:
        cmd = mkdircmd + ' ' + runid
        os.system(cmd)

outfilename = runid + '/list_of_files.txt'

operation = '> '

#---------------------------------------------------------------------------
pathA = runid
#---------------------------------------------------------------------------

for subdir in subdirs:

	pathB = subdir
        #---------------------------------------------------------------------------
	runpath = pathA + '/' + pathB +'/'
	print runpath
	fullpath = prefix + path + runpath
	cmd  = lsmethod + ' ' + fullpath
	cmd += ' | awk \'{ print \"' + path + runpath  + '\"$9 }\' ' + operation + outfilename
	print cmd
	operation = '>> '
	excode = os.system(cmd)
        #---------------------------------------------------------------------------


#---------------------------------------------------------------------------
print 'Done.'
#---------------------------------------------------------------------------
