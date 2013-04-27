import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="dataset",
                  help="Run id (dataset)" )

parser.add_option("-t", type = "string", dest="tag",
                  help="Global run tag", metavar="GLOBAL RUN TAG" )

parser.add_option("-g", type = "string", dest="globaltag",
                  help="GlobalTag", metavar="GLOBAL TAG" )

(options, args) = parser.parse_args()

if options.dataset is None:
        parser.error("please give a run ID dataset type")

if options.tag is None:
        parser.error("please give a global run tag (ex. MWGR_25, CRUZET_II)")

if options.globaltag is None:
        parser.error("please give a Global Tag (ex.GR09_P_V4::All)")

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

dataset   = options.dataset
runlist   = dataset.split(',')
mwgrid    = options.tag
globaltag = options.globaltag

tools     = cmsRunTools()
cmsswver  = tools.getSW( os.environ['PWD'] )

prefix   = os.environ['PWD'] + '/'
cfg_file = prefix + 'l1gtttuanalyzer-with-data-manual_cfg.py' 

app = cmsRun()
app.uselibs = 1
app.version = cmsswver
app.cfgfile = File( name=cfg_file )
app.add_cfg_Parameter('process.GlobalTag.globaltag','cms.string')

runpath = '/castor/cern.ch/user/c/ccmuon/RPC/'+ mwgrid + '/'

if mwgrid != 'minidaq':
	runpath = '/castor/cern.ch/user/c/ccmuon/RPC/GlobalRuns/'+ mwgrid + '/'
	
sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1

rm = RootMerger()
rm.files = ['histo-data.root']
rm.overwrite = True
rm.ignorefailed = True

for runid in runlist:

	infile   = runid + '/list_of_digis.txt'
	ff = File( name=infile )
	ff.subdir = ff.subdir = runpath + runid + '/'
	fdata = CMSDataset( ff , 'castor' )

	myjob = Job( application = app, backend = 'LSF' )
	myjob.name = 'ttugt.data.' + runid
	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'
	myjob.outputsandbox = ['histo-data.root','l1Gtinformation.txt.gz']
	myjob.application.args = [ globaltag ]
	myjob.splitter = sp
	myjob.merger = rm
	myjob.backend.queue = 'cmscaf1nd'

	myjob.submit()

print "job submission done."


