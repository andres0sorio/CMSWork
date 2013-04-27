#!/usr/bin/python

import os,sys
import string

# ...
# Andres Osorio - aosorio@uniandes.edu.co
# .

if len(sys.argv) >= 2:
    cmsswver = sys.argv[1]
    
workarea = os.environ['HOME']+'/scratch0/'

target = workarea + cmsswver
excode  = os.path.isdir( target )

if excode == False:
    cmd = 'cd ' + workarea + ';' + 'scramv1 project CMSSW ' + cmsswver
    excode = os.system(cmd)

srcpath = workarea + cmsswver + '/src/'

cvsop = '-f '
cvsop = '-r V00-04-09 '
cvsco = 'cvs co ' + cvsop

packages = ['L1Trigger/RPCTechnicalTrigger']

for pack in packages:
    cmd = 'cd ' + srcpath + '; '  + cvsco + pack
    excode = os.system(cmd)
    cmd = 'cd ' + srcpath + '; '  + 'eval `scramv1 runtime -sh`'
    print cmd
    excode = os.system(cmd)
    cmd = 'cd ' + srcpath + pack + '; ' + 'scram b -j 4'
    print cmd
    excode = os.system(cmd)

packages = ['StudyL1Trigger']
project  = ['L1GtTechTrig']

svnco  = os.environ['HOME']+'/bin/svnco.sh '

prefix = 'Users/aosorio/Code/'

for pack in packages:
    cmd = 'cd ' + srcpath + '; '  + svnco + prefix + pack
    excode = os.system(cmd)
    cmd = 'cd ' + srcpath + pack + '/' + project[0] + '; ' + 'scram b -j 4'
    excode = os.system(cmd)
    
print 'Done.'
