import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="dataset",
                  help="Run id (dataset)" )

parser.add_option("-r", type = "string", dest="selrun",
                  help="Select a run" )

(options, args) = parser.parse_args()

if options.dataset is None:
        parser.error("please give a run ID dataset type")

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

dataset  = options.dataset
selrun   = options.selrun

tools     = cmsRunTools()
cmsswver  = tools.getSW( os.environ['PWD'] )

prefix   = os.environ['PWD']
cfg_file = prefix + '/' + 'l1gtttuanalyzer-with-data_cfg.py'

app = cmsRun()
app.uselibs = 1
app.version = cmsswver
app.cfgfile = File( name=cfg_file )

sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1

rm = RootMerger()
rm.files = ['histo.root']
rm.overwrite = True
rm.ignorefailed = True

runlist = open(dataset,'r')

for line in runlist:

	run = line.split()
	runid = run[0]
	globaltag = run[4]

	if runid != selrun:
		continue
	
	datafile = './CRAFT2/' + runid + '/list_of_files.txt'

	ff = File( name=datafile )
	fdata = CMSDataset( ff , 'grid' )
	
	myjob = Job( application = app, backend = 'LSF' )
	myjob.application.add_cfg_Parameter('process.GlobalTag.globaltag','cms.string')
	myjob.application.args = [ globaltag ]
	
	myjob.name = 'ttugt.emu.data.' + runid
	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'
	
	dbfileB = File( 'hardware-pseudoconfig.txt' )
	dbfileB.subdir = cmsswver
	dbfileC = File( 'rpcTechnicalTrigger_cfi.py' )
	dbfileC.subdir = cmsswver
	
	myjob.inputsandbox.append( dbfileB )
	myjob.inputsandbox.append( dbfileC )
	myjob.outputsandbox = ['histo.root','l1Gtinformation.txt.gz']
	myjob.splitter = sp
	myjob.merger = rm
	myjob.backend.queue = 'cmscaf1nd'

	myjob.submit()

print "job submission done."

