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
cfg_file = prefix + '/' + 'goldenbit25_cfg.py'

app = cmsRun()
app.uselibs = 1
app.platform = 'slc5_ia32_gcc434'
app.version = cmsswver
app.cfgfile = File( name=cfg_file )
app.add_cfg_Parameter('process.GlobalTag.globaltag','cms.string')

sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1

rm = TextMerger()
rm.files = ['l1Gtinformation.csv']
rm.overwrite = True
rm.ignorefailed = True
rm.compress = True

runlist = open(dataset,'r')

for line in runlist:

	run = line.split()
	runid = run[0]
	globaltag = run[4]

	if runid != selrun:
		continue
	
	datafile = './COLLISIONS10/' + runid + '/list_of_files.txt'

	ff = File( name=datafile )
	fdata = CMSDataset( ff , 'grid' )
	
	myjob = Job( application = app, backend = 'LSF' )
	myjob.application.args = [ globaltag ]

	myjob.name = 'ttugt.data.' + runid
	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'
	myjob.outputsandbox = ['l1Gtinformation.csv']
	myjob.splitter = sp
	myjob.merger = rm
	myjob.backend.queue = 'cmscaf1nd'
		
	myjob.submit()

print "job submission done."


