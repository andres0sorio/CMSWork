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
tmp1 = runid
tmp2 = tmp1[0:len(tmp1)-3]

if len(tmp2) < 3:
    pathA = '0'+tmp2
else:
    pathA = tmp2
#---------------------------------------------------------------------------
pathB = tmp1[len(tmp1)-3:len(tmp1)]
#---------------------------------------------------------------------------

runpath = pathA + '/' + pathB +'/'

print runpath

prefix   = '/castor/cern.ch/cms'

path = '/store/data/Commissioning10/MinimumBias/RECO/v9/000/'

#path  = '/store/express/Commissioning10/OfflineMonitor/FEVTHLTALL/v7/000/'
#path = '/store/express/Commissioning10/ExpressPhysics/FEVT/v7/000/'

fullpath = prefix + path + runpath

excode = os.path.isdir(runid)
if excode != True:
        cmd = mkdircmd + ' ' + runid
        os.system(cmd)
	
outfilename = runid + '/list_of_files.txt'
	
cmd  = lsmethod + ' ' + fullpath
cmd += ' | awk \'{ print \"' + path + runpath  + '\"$9 }\' > ' + outfilename
print cmd

excode = os.system(cmd)

#---------------------------------------------------------------------------




#---------------------------------------------------------------------------
print 'Done.'
#---------------------------------------------------------------------------
