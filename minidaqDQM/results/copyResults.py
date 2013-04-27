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

type    = options.type
runlist = options.runid.split(',')

nfiles    = 0
castor    = '/castor/cern.ch/user/a/aosorio/gridfiles/ganga/'
targetdir = ''
cpmethod = ['cp ','rfcp ']

listofresults = []

for runid in runlist:
	
	prevstep =  type + '.fullmdaq.'+ runid
	
	seljobs  = jobs.select(name=prevstep)

	if len( seljobs ) != 1:
		sys.exit
		
	prevstepjob = seljobs[-1]
	jobid       = prevstepjob.id

	for jb in prevstepjob.subjobs:
		jbs  = jb.status
		jbid = jb.id

		outputdata = []
		
		if jbs == 'completed':
			
			if jb.outputdata != None:
				#modify this one
				tmp = jb.outputdata.names[0]
				outdata = tmp.split('.')
				sourcedir   = castor + str(jobid) + '/' + str(jb.id) + '/outputdata/'
				cpcmd = cpmethod[1]
			else:
				sourcedir = jb.outputdir
				cpcmd     = cpmethod[0]
				for outfile in jb.outputsandbox:
					outputdata.append(outfile)

			for fname in outputdata:
				source = sourcedir + fname
				newfname  = fname.split('.')[0] + '-' + runid + '-' + str(jb.id) + '.root'
				cmd = cpcmd + source + ' ' + targetdir + newfname
				print cmd
 			        os.system(cmd)
				nfiles=nfiles+1
				listofresults.append(newfname)


source = ' '.join(listofresults)
target = ' cmsusr1.cern.ch:miniDAQ/'
cmd = 'scp ' + source + target
print cmd
os.system(cmd)

print 'Total files: ', nfiles, '. All done'

