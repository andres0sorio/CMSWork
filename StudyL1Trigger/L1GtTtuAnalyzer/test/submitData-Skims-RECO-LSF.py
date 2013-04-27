import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="dataset",
                  help="Run id (dataset)" )

parser.add_option("-r", type = "string", dest="selrun",
                  help="Select a run" )

parser.add_option("-i", type = "string", dest="input",
                  help="Select an input file" )

(options, args) = parser.parse_args()

if options.dataset is None:
        parser.error("please give a run ID dataset type")
	
#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

dataset  = options.dataset
selrun   = options.selrun
input    = options.input

tools     = cmsRunTools()
cmsswver  = tools.getSW( os.environ['PWD'] )

prefix   = os.environ['PWD']
cfg_file = prefix + '/' + 'l1gtttuanalyzer-with-data_cfg.py' 

app = cmsRun()
app.uselibs = 1
app.version = cmsswver

app.cfgfile = File( name=cfg_file )
app.add_cfg_Parameter('process.GlobalTag.globaltag','cms.string')
app.platform = 'slc5_ia32_gcc434'
sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1

runlist = open(dataset,'r')

for line in runlist:

	run = line.split()
	runid = run[0]
	globaltag = run[4]
	
	if runid != selrun:
		continue
	
	#datafile = 
	if input != None:
		datafile = input
	else:
		'./PREBEAM/' + runid + '/list_of_files.txt'
		
	ff = File( name=datafile )

	#fdata = CMSDataset( ff , 'grid' )
	fdata = CMSDataset( ff , 'castor' )
	
	myjob = Job( application = app, backend = 'LSF' )
	myjob.application.args = [ globaltag ]

	myjob.name = 'ttugt.data.' + runid
	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'

	foutdata = CMSDataset()
	foutdata.names = ['histo-data.root','l1Gtinformation.txt.gz','l1Gtinformation.csv.gz']
	myjob.outputdata = foutdata

	myjob.splitter = sp
	myjob.backend.queue = 'cmscaf1nd'
		
	myjob.submit()

print "job submission done."


