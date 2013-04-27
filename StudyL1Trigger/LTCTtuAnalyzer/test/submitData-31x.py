import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="dataset",
                  help="Run id (dataset)" )

(options, args) = parser.parse_args()

if options.dataset is None:
        parser.error("please give a run ID dataset type for several ids separate them with comma (-r=xxx,xxx)")
#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

dataset = options.dataset
runlist = dataset.split(',')

print 'total runs to be submit: ', len(runlist)

cmsswver = 'CMSSW_3_1_1'
prefix   = '/afs/cern.ch/user/a/aosorio/scratch0/'+ cmsswver +'/src/StudyL1Trigger/LTCTtuAnalyzer/test/'
cfg_file = prefix + 'ltcttuanalyzer_cfg.py' 

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
	myjob.name = 'ttultc.ltcdata.' + runid
	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'
	myjob.outputsandbox = ['histo.root','ltcinformation.txt.gz']
	myjob.splitter = sp
	myjob.backend.queue = 'cmscaf1nd'
	myjob.submit()

print "job submission done."

