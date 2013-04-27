# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...
import sys,os
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

#select all jobs with name=
jobname = 'HSCP.KKTau'

seljobs = jobs.select(name=jobname)

if len( seljobs ) < 1:
	sys.exit

nfiles=0
cpmethod = 'rfcp '

for mainjob in seljobs:
	jobid  = mainjob.id

	for mcjob in mainjob.subjobs:
		status  = mcjob.status
		sjobid  = mcjob.id

		if status == 'completed':
			tmp = mcjob.outputdata.names[0]
			outdata = tmp.split('.')
			sourcedir   = mcjob.backend.sandboxcache.se_rpath + '/' + str(jobid) + '/' + str(sjobid) + '/outputdata/'
			targetdir   = mcjob.backend.sandboxcache.se_rpath + '/' + 'MCPROD-' + mainjob.name + '/'
			source = sourcedir + tmp
			newfname  = outdata[0] + '.' + mainjob.name + '.' + str(jobid) + '.' +  str(sjobid) + '.root'
			cmd = cpmethod + source + ' ' + targetdir + newfname
			print cmd
			#os.system(cmd)
			nfiles=nfiles+1

print nfiles
