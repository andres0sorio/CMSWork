import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="dataset",
                  help="Run id (dataset)" )

parser.add_option("-f", type = "string", dest="runlist",
                  help="Run info list" )

parser.add_option("-c", type = "string", dest="config",
                  help="Configuration file" )

(options, args) = parser.parse_args()

if options.dataset is None:
        parser.error("please give a run ID dataset type")

if options.config is None:
        parser.error("please provide a cfg file")

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

dataset   = options.dataset
runlist   = dataset.split(',')
infile    = options.runlist
config    = options.config

cmsswver  = 'CMSSW_3_3_6_patch3'

prefix   = os.environ['PWD'] + '/'
cfg_file = prefix + config

app = cmsRun()
app.uselibs = 1
app.version = cmsswver
app.cfgfile = File( name=cfg_file )
app.add_cfg_Parameter('process.GlobalTag.globaltag','cms.string')

sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1

rm = RootMerger()
rm.files = ['histo.root']
rm.overwrite = True
rm.ignorefailed = True

runList = []
runinfo = open(infile,'r')
for line in runinfo:
	run = line.split()
	runList.append( [ run[0],run[4] ] )
	
for runid in runlist:

	globaltag = ''
	for run in runList:
		if runid == run[0]:
			globaltag = run[1]
			print 'We submit for this run'

	if globaltag == '':
		continue

	outpath  = './CRAFT/' + runid + '/'
	datafile = outpath + 'list_of_bit24-Bx-1_skims.txt'
	ff = File( name=datafile )
	fdata = CMSDataset( ff , 'castor' )
	
	myjob = Job( application = app, backend = 'LSF' )
	myjob.name = 'digi.analyzer.' + runid
	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'
	myjob.outputsandbox.append('histo.root')
	myjob.outputsandbox.append('checkdata.out')
	myjob.application.args = [ globaltag ]
	myjob.splitter = sp
	myjob.merger = rm
	myjob.backend.queue = 'cmscaf1nd'

	myjob.submit()

print "job submission done."


