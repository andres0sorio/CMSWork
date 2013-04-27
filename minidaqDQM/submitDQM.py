# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...

import sys
from optparse import OptionParser
#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="runid",
                  help="Run Id number", metavar="RUNID")

parser.add_option("-o", type = "string", dest="type",
                  help="Type of job (dqm,ttu)", default='ttu' )

(options, args) = parser.parse_args()

if options.runid is None:
        parser.error("please give a run number")
	
#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------

from GangaCMS.Lib.CMSexe import *

type     = options.type
runlist  = options.runid.split(',')

cmsswver = 'CMSSW_3_5_0_patch1'

prefix   = os.environ['PWD']
cfg_file = prefix + '/' + 'dqm_digi.py'

app = cmsRun()
app.uselibs  = 1
app.platform = 'slc5_ia32_gcc434'
app.cfgfile  = File(name=cfg_file)
app.version  = cmsswver


for runid in runlist:

	myjob = Job( application = app, backend = 'LSF' )
	myjob.name = type + '.step2.' + runid
	myjob.backend.queue = 'cmscaf1nd'
	
	infile   = runid + '/list_of_digis.txt'
	sourcedir   = '/castor/cern.ch/user/c/ccmuon/RPC/minidaq/' + str(runid) + '/'

	ff = File( name=infile )
	ff.subdir = ff.subdir = sourcedir
	fdata = CMSDataset( ff , 'castor' )

	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'

	myjob.outputsandbox = ['RPCDQM.root','histo.root']

	sp = SplitByFiles()
	sp.filesPerJob = 10
	sp.maxFiles = -1

	rm = RootMerger()
	rm.files = ['RPCDQM.root']
	rm.overwrite = True
	rm.ignorefailed = True

	if len( myjob.inputdata.names ) > 1:
		myjob.merger = rm

	myjob.splitter = sp
		
	myjob.submit()

