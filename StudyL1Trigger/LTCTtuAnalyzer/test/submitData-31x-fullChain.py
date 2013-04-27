import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="dataset",
                  help="Run ID (dataset) name" )

(options, args) = parser.parse_args()

if options.dataset is None:
        parser.error("please give a run ID number (dataset)")
#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

dataset  = options.dataset
runlist = dataset.split(',')

print 'total runs to be submit: ', len(runlist)

cmsswver = 'CMSSW_3_1_1'
prefix   = '/afs/cern.ch/user/a/aosorio/scratch0/'+ cmsswver +'/src/StudyL1Trigger/LTCTtuAnalyzer/test/'
cfg_file = prefix + 'ltcttuanalyzer_allsec_Data_cfg.py'

app = cmsRun()
app.uselibs = 1
app.version = cmsswver
app.cfgfile = File( name=cfg_file )

runpath = '/castor/cern.ch/user/c/ccmuon/RPC/minidaq/'

sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1

rm = RootMerger()
rm.files = ['histo.root']
rm.overwrite = True
rm.ignorefailed = True

for runid in runlist:

	infile = runid + '/list_of_digis.txt'
	ff = File( name=infile )
	ff.subdir = ff.subdir = runpath + runid + '/'
	fdata = CMSDataset( ff , 'castor' )
	
	myjob = Job( application = app, backend = 'LSF' )
	myjob.name = 'ttultc.emu.data.' + runid
	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'
	
	dbfileA = File( name='myrbconfig.db' )
	dbfileA.subdir = 'CMSSW_3_1_1'
	dbfileB = File( 'hardware-pseudoconfig-TTU-5.txt' )
	dbfileB.subdir = 'CMSSW_3_1_1'
	dbfileC = File( 'rpcTechnicalTrigger_cfi.py' )
	dbfileC.subdir = 'CMSSW_3_1_1'
	
	myjob.inputsandbox.append( dbfileA )
	myjob.inputsandbox.append( dbfileB )
	myjob.inputsandbox.append( dbfileC )
	myjob.outputsandbox = ['histo.root','ltcinformation.txt.gz']
	myjob.splitter = sp
	myjob.backend.queue = 'cmscaf1nd'
	myjob.submit()


print "job submission done."

