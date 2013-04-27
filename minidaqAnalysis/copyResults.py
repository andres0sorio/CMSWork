# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...

import sys,os
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="runid",
                  help="Run Id number", metavar="RUNID")

parser.add_option("-o", type = "string", dest="type",
                  help="Type of job (dqm,ttu)", default='ttu' )

(options, args) = parser.parse_args()

if options.runid is None:
        parser.error("please give a run number")

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

type   = options.type
runid  = int( options.runid )

prevstep =  type + '.step2.'+ options.runid

seljobs = jobs.select(name=prevstep)

if len( seljobs ) != 1:
	sys.exit

prevstepjob = seljobs[-1]

jobid  = prevstepjob.id

nfiles=0

cpmethod = ['cp ','rfcp '] 

for jb in jobs(jobid).subjobs:
	jbs  = jb.status
	jbid = jb.id
	if jbs == 'completed':
		
		if jb.outputdata != None:
			tmp = jb.outputdata.names[0]
			outdata = tmp.split('.')
			sourcedir   = '/castor/cern.ch/user/a/aosorio/gridfiles/ganga/' + str(jobid) + '/' + str(jb.id) + '/outputdata/'
			cpcmd = cpmethod[1]
		else:
			tmp = jb.outputsandbox[0]
			outdata = tmp.split('.')
			sourcedir = jb.outputdir
			cpcmd = cpmethod[0]
		
		source = sourcedir + tmp
		newfname  = outdata[0] + '.' + options.runid + '.' + str(jb.id) + '.root'
		cmd = cpcmd + source + ' ' + newfname
		print cmd
		os.system(cmd)
		nfiles=nfiles+1

print nfiles
