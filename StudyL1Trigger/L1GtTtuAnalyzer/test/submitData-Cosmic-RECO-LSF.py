import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="dataset",
                  help="Run id (dataset)" )

parser.add_option("-r", type = "string", dest="selrun",
                  help="Select a run" )

parser.add_option("-c", type = "string", dest="cfgfile",
                  help="Select a cfg file", default='l1gtttuanalyzer-with-cosmicdata_cfg.py' )

(options, args) = parser.parse_args()

if options.dataset is None:
        parser.error("please give a run ID dataset type")

#-----------------------------------------------------
#-----------------------------------------------------

def isSelected( run, selruns ):
	for selec in selruns:
		if run == selec:
			return True
	return False

from GangaCMS.Lib.CMSexe import *

dataset  = options.dataset
selruns  = options.selrun.split(',')

tools     = cmsRunTools()
cmsswver  = tools.getSW( os.environ['PWD'] )

prefix   = os.environ['PWD']
cfg_file = prefix + '/' + options.cfgfile

app = cmsRun()
app.uselibs = 1
app.platform = 'slc5_ia32_gcc434'
app.version = cmsswver
app.cfgfile = File( name=cfg_file )
app.add_cfg_Parameter('process.GlobalTag.globaltag','cms.string')

sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1

rm = RootMerger()
rm.files = ['histo-data.root']
rm.overwrite = True
rm.ignorefailed = True

runlist = open(dataset,'r')

for line in runlist:

	run = line.split()
	runid = run[0]
	globaltag = run[4]

	if not isSelected( runid, selruns ):
		continue
	
	datafile = './CRAFT10/' + runid + '/list_of_files.txt'

	ff = File( name=datafile )
	fdata = CMSDataset( ff , 'grid' )
	
	myjob = Job( application = app, backend = 'LSF' )
	myjob.application.args = [ globaltag ]

	myjob.name = 'ttugt.data.' + runid
	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'
	myjob.outputsandbox = ['histo-data.root','l1Gtinformation.txt.gz','l1Gtinformation.csv.gz']
	myjob.splitter = sp
	myjob.merger = rm
	myjob.backend.queue = 'cmscaf1nd'
		
	myjob.submit()

print "job submission done."


