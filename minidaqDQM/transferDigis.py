# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...

import sys,os
from optparse import OptionParser
#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="runid",
                  help="Run Id number", metavar="RUNID")

parser.add_option("-t", type = "string", dest="tag",
                  help="Global run tag", default='minidaq', metavar="GLOBAL RUN TAG" )

parser.add_option("-o", type = "string", dest="type",
                  help="Type of job (dqm,ttu)", default='ttu' )

(options, args) = parser.parse_args()

if options.runid is None:
        parser.error("please give a run number")

if options.tag is None:
        parser.error("please give a tag (minidaq,MWGR_X,...)")


#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------

from GangaCMS.Lib.CMSexe import *

type    = options.type
runstr  = options.runid
mwgrid  = options.tag
runlist = runstr.split(',')

outputdir   = '/castor/cern.ch/user/a/aosorio/gridfiles/ganga/'

for runid in runlist:

	prevstep =  type + '.step1.'+ runid

	seljobs = jobs.select(name=prevstep)

	if len( seljobs ) != 1:
		sys.exit

	prevstepjob = seljobs[-1] #...select the newest on the list
	jobid  = prevstepjob.id

	nfiles=0

	targetdir   = ''

	if mwgrid == 'minidaq':
		targetdir   = '/castor/cern.ch/user/c/ccmuon/RPC/minidaq/' + runid + '/'
	else:
		targetdir   = '/castor/cern.ch/user/c/ccmuon/RPC/GlobalRuns/' + mwgrid + '/' + runid + '/'

	outfilename = runid+'/list_of_digis.txt'

	excode = os.path.isdir( runid )
	if excode != True:
		os.mkdir( runid )
	outfile = open( outfilename, 'w' )

	argvs = []

	for jb in jobs(jobid).subjobs:
		jbs  = jb.status
		jbid = jb.id
		if jbs == 'completed':
			indata = jb.inputdata.names[0]
			tmp1   = indata.split('/')
			tmp2   = tmp1[-1]
			tmp3   = tmp2.split('.')
			pos    = len(tmp3[1]) - len( runid )
			head   = tmp3[1][pos:len(tmp3[1])]
			newfname  = 'digis.'+head+'.'+tmp3[2]+'.'+tmp3[5]+'.'+tmp3[6]+'.root'
			sourcedir = outputdir + str(jobid) + '/' + str(jbid) + '/outputdata/'
			source = sourcedir + 'digis.root'
			target = targetdir + newfname
			
			source = [ source , target ]
			argvs.append( source )
			
			outfile.writelines( newfname + '\n' )
			
			nfiles=nfiles+1
		
		else:
			print 'job has not yet finished ...'


	outfile.close()

	app      = Executable()
	app.exe  = 'rfcp'
	app.args = []

	sp = ArgSplitter( args = argvs )

	myjob = Job( application = app, backend = 'LSF' )
	myjob.name = type + '.transfer.' + runid
	myjob.backend.queue = 'cmscaf1nh'
	myjob.splitter = sp

	myjob.submit()



print nfiles
