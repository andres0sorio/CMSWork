import sys
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

tools     = cmsRunTools()
cmsswver  = tools.getSW( os.environ['PWD'] )

prefix   = os.environ['PWD']
cfg_file = prefix + '/' + 'l1gtttuanalyzer-data_cfg.py' 

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
	print run
	runid = run[0]
	globaltag = run[4]
	ce = run[8]
	
	datafile = './CRAFT2/' + runid + '/list_of_files.txt'

	ff = File( name=datafile )
	fdata = CMSDataset( ff , 'grid' )
	
	myjob = Job( application = app, backend = 'LCG' )
	myjob.application.add_cfg_Parameter('process.GlobalTag.globaltag','cms.string')
	myjob.application.args = [ globaltag ]
	
	myjob.name = 'ttugt.data.' + runid
	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'
	myjob.outputsandbox = ['histo.root','l1Gtinformation.txt.gz']
	myjob.splitter = sp
	myjob.merger = rm
	myjob.backend.middleware = 'GLITE'
	myjob.backend.CE = ce

	break
	myjob.submit()

print "job submission done."


