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
parser.add_option("-r", type = "string", dest="runid",
                  help="Run Id number", metavar="RUNID" )

parser.add_option("-o", type = "string", dest="altpath",
                  help="Use alternative path(yes)", metavar="ALTPATH" )

(options, args) = parser.parse_args()

if options.runid is None:
        parser.error("please give a run number")

#-----------------------------------------------------
#-----------------------------------------------------

runid = options.runid
altpath = options.altpath

lsmethod = 'rfdir'

prefix = '/castor/cern.ch/user/a/aosorio/gridfiles/ganga/PATOutput/'
fullpath = prefix + runid
cmd = lsmethod + ' ' + fullpath
excode = os.system(cmd)

outfilename = runid + '/list_of_files.txt'

if excode == 0:
        excode = os.path.isdir( runid )
        if excode != True:
                cmd = ('mkdir '+ runid )
                os.system(cmd)

        cmd  = 'rfdir ' + fullpath + ' | awk \' { print $9 } \' '
        files = os.popen(cmd,'r').readlines()

        outfile = open(outfilename,'w')
        for ff in files:
                outfile.write(fullpath + '/' + ff)
        outfile.close()
        
print 'Done.'
