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

(options, args) = parser.parse_args()

if options.runid is None:
        parser.error("please give a run number")

#---------------------------------------------------------------------------
#---------------------------------------------------------------------------

runid = options.runid

lsmethod = 'rfdir'
mkdircmd = 'mkdir'

#---------------------------------------------------------------------------
pathA = runid

#---------------------------------------------------------------------------

runpath = pathA + '/'

print runpath

prefix   = '/castor/cern.ch/cms'

path  = '/store/mc/Spring10/MinBias/GEN-SIM-RECO/START3X_V25B-v1/'

fullpath = prefix + path + runpath

excode = os.path.isdir('./Spring10-MinBias/' + runid)
if excode != True:
        cmd = mkdircmd + ' ' + './Spring10-MinBias/' + runid
        os.system(cmd)
	
outfilename = './Spring10-MinBias/' + runid + '/list_of_files.txt'
	
cmd  = lsmethod + ' ' + fullpath
cmd += ' | awk \'{ print \"' + path + runpath  + '\"$9 }\' > ' + outfilename
print cmd

excode = os.system(cmd)

#---------------------------------------------------------------------------




#---------------------------------------------------------------------------
print 'Done.'
#---------------------------------------------------------------------------
