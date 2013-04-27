import sys,os
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="dataset",
                  help="Run id (dataset)" )

(options, args) = parser.parse_args()

if options.dataset is None:
        parser.error("please give a run ID dataset type")

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

dataset  = options.dataset

cmsswver = 'CMSSW_3_1_2'

prefix   = os.environ['PWD']
cfg_file = prefix + '/' + 'dqmttuanalyzer_cfg.py' 

app = cmsRun()
app.uselibs = 1
app.version = cmsswver
app.cfgfile = File( name=cfg_file )
app.add_cfg_Parameter('process.TFileService.fileName','cms.untracked.string')
app.add_cfg_Parameter('process.GlobalTag.globaltag','cms.string')

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
	ce = run[7]
	##ce = 'ce128.cern.ch:2119/jobmanager-lcglsf-grid_cms'
	
	datafile = './CRAFT2/' + runid + '/list_of_files.txt'

	ff = File( name=datafile )
	fdata = CMSDataset( ff , 'grid' )
	fdata.SetMaxFiles(5)

	myjob = Job( application = app, backend = 'LCG' )
	
	outfile = 'dqm_histos_CRAFT2_' + runid + '.root'

	myjob.application.args = [ outfile, globaltag ]
	
	myjob.name = 'ttu.dqm.' + runid
	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'

	dbfileB = File( 'hardware-pseudoconfig.txt' )
	dbfileB.subdir = cmsswver
	dbfileC = File( 'rpcTechnicalTrigger_cfi.py' )
	dbfileC.subdir = cmsswver

	myjob.inputsandbox.append( dbfileB )
	myjob.inputsandbox.append( dbfileC )
	
	myjob.outputsandbox = [outfile]
	myjob.splitter = sp
	myjob.merger = rm
	myjob.backend.middleware = 'GLITE'
	myjob.backend.CE = ce

	myjob.submit()

print "job submission done."


