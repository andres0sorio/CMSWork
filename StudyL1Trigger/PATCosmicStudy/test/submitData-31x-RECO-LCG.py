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

dataset   = options.dataset
runlist   = dataset.split(',')
dttype    = options.tag

cmsswver  = 'CMSSW_3_1_2'

outputdir = '/castor/cern.ch/user/a/aosorio/gridfiles/ganga/PATtest'
#outputdir = '/dpm/uniandes.edu.co/home/cms/user/a/aosorio/gridfiles/PATtest'

prefix    = os.environ['PWD'] + '/'
cfg_file  = prefix + 'patLayer1_CRAFT2_cfg.py' 

app = cmsRun()
app.uselibs = 0
app.version = cmsswver
app.cfgfile = File( name=cfg_file )
app.add_cfg_Parameter('process.source.fileName','cms.untracked.vstring')
app.add_cfg_Parameter('process.out.fileName','cms.untracked.string')

for runid in runlist:

	dbs = DBSSearch()
	dbs.searchFiles( int(runid), dttype )
	fdata = dbs.getCMSDataset()
	#fdata.SetMaxFiles(1)
	
	k=0
	arguments = []
	outputnames = []
	for file in fdata.names:
		outfile = 'PATLayer1_Output.from.CRAFT2_' + runid + '_' + str(k) + '.root'
		arguments.append( [ file, outfile ] )
		outputnames.append(outfile)
		k=k+1

	myjob = Job( application = app, backend = 'LCG' )
	myjob.name = 'pat.craft2.data.' + runid
	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'
	
	foutdata = CMSDataset()
	foutdata.names = outputnames
	foutdata.subdir = outputdir
	myjob.outputdata = foutdata

	myjob.splitter = ArgSplitter( args = arguments )
	
	#myjob.backend.CE = 'ce01-lcg.cr.cnaf.infn.it:8443/cream-lsf-cms'
	
	myjob.backend.CE = 'cmsosgce2.fnal.gov:2119/jobmanager-condor-default'

	myjob.backend.middleware = 'GLITE'

	myjob.submit()

print "job submission done."


