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

tools     = cmsRunTools()
cmsswver  = tools.getSW( os.environ['PWD'] )

prefix   = os.environ['PWD']
cfg_file = prefix + '/' + 'ltc2dqm_digi.py'

app = cmsRun()
app.uselibs  = 1
app.platform = 'slc5_ia32_gcc434'
app.cfgfile  = File(name=cfg_file)
app.version  = cmsswver

prefix='/castor/cern.ch/cms/store/streamer/Minidaq/A/000/'

for runid in runlist:

	myjob = Job( application = app, backend = 'LSF' )
	####myjob = Job( application = app, backend = 'Local' )
	myjob.name = type + '.fullmdaq.' + runid
	myjob.backend.queue = 'cmscaf1nd'
	
	infile   = runid + '/list_of_files.txt'

	runpath = runid[0:3]+'/'+runid[3:6]
	fullpath = prefix + runpath + '/'
	
	ff = File( name=infile )
	ff.subdir = fullpath
	fdata = CMSDataset( ff , 'castor' )

	myjob.inputdata = fdata
	myjob.inputdata.type = 'NewEventStreamFileReader'

	myjob.outputsandbox = ['RPCDQM.root','histo.root']

	sp = SplitByFiles()
	sp.filesPerJob = 1
	sp.maxFiles = -1

	rm = RootMerger()
	rm.files = ['RPCDQM.root']
	rm.overwrite = True
	rm.ignorefailed = True

	if len( myjob.inputdata.names ) > 1:
		myjob.merger = rm

	myjob.splitter = sp
		
	myjob.submit()

