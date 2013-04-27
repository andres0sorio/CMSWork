import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="dataset",
                  help="Run id (dataset)" )

parser.add_option("-r", type = "string", dest="selrun",
                  help="Select a run" )

parser.add_option("-t", type = "string", dest="tag",
                  help="Select a tag" )

parser.add_option("-c", type = "string", dest="cfgfile",
                  help="Select a cfg file" )

(options, args) = parser.parse_args()

if options.dataset is None:
        parser.error("please give a run ID dataset type")

if options.cfgfile is None:
        parser.error("please give a cfg file")

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

dataset  = options.dataset
selrun   = options.selrun
tag      = options.tag
cfg      = options.cfgfile

tools     = cmsRunTools()
cmsswver  = tools.getSW( os.environ['PWD'] )

prefix   = os.environ['PWD']
cfg_file = prefix + '/' + cfg

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

	##print globaltag
	
	if runid != selrun:
		continue
	
	datafile = './COLLISIONS10/' + runid + '/list_of_' + tag + '_skims.txt'

	ff = File( name=datafile )
	fdata = CMSDataset( ff , 'castor' )
	
	myjob = Job( application = app, backend = 'LSF' )
	myjob.application.args = [ globaltag ]

	myjob.name = 'ttugt.data.skim.' + runid
	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'
	myjob.outputsandbox = ['histo-data.root','l1Gtinformation.txt.gz','l1Gtinformation.csv.gz']
	myjob.splitter = sp
	myjob.merger = rm
	myjob.backend.queue = 'cmscaf1nd'
		
	myjob.submit()

print "job submission done."


