import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="dataset",
                  help="Run id (dataset)" )

parser.add_option("-t", type = "string", dest="tag",
                  help="Global run tag", metavar="Dataset TAG" )

(options, args) = parser.parse_args()

if options.dataset is None:
        parser.error("please give a run ID dataset type")

if options.tag is None:
        parser.error("please give a global run tag (ex. /Cosmics/CRAFT09-PromptReco-v1/RECO, ...)")

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

dataset  = options.dataset
runlist  = dataset.split(',')
dttype   = options.tag

tools     = cmsRunTools()
cmsswver  = tools.getSW( os.environ['PWD'] )

prefix   = os.environ['PWD']
cfg_file = prefix + 'l1gtttuanalyzer-with-data_cfg.py' 

app = cmsRun()
app.uselibs = 1
app.version = cmsswver
app.cfgfile = File( name=cfg_file )

sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1

rm = RootMerger()
rm.files = ['histo-data.root']
rm.overwrite = True
rm.ignorefailed = True

for runid in runlist:

	dbs = DBSSearch()
	dbs.searchFiles( int(runid), dttype )
	fdata = dbs.getCMSDataset()
	#fdata.SetMaxFiles(1)
	
	myjob = Job( application = app, backend = 'LSF' )
	myjob.name = 'ttugt.data.' + runid
	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'
	myjob.outputsandbox = ['histo-data.root','l1Gtinformation.txt.gz']
	myjob.splitter = sp
	myjob.merger = rm
	myjob.backend.queue = 'cmscaf1nd'

	myjob.submit()

print "job submission done."


