import sys,os
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="dataset",
                  help="Samples name" )

parser.add_option("-v", type = "string", dest="cmsswver",
                  help="CMSSW version" )

(options, args) = parser.parse_args()

if options.dataset is None:
        parser.error("please give a dataset type")

if options.cmsswver is None:
        parser.error("please give a CMSSW version")
	
#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

dataset  = options.dataset
cmsswver  = options.cmsswver

hwconfigs=[]
hwconfigs.append( 'hardware-pseudoconfig.txt' )        # majority 4
hwconfigs.append( 'hardware-pseudoconfig-TTU-3.txt' )  # majority 3
hwconfigs.append( 'hardware-pseudoconfig-TTU-2.txt' )  # majority 2

prefix   = os.environ['PWD'] + '/'
cfg_file = prefix + 'l1gttechtrig_allseq_RelValCosmics_cfg.py' 

dbfileA = File( name='myrbconfig.db' )
dbfileA.subdir = cmsswver

dbfileC = File( name='rpcTechnicalTrigger_cfi.py' )
dbfileC.subdir = cmsswver

app = cmsRun()
app.uselibs = 1
app.version = cmsswver
app.cfgfile = File( name=cfg_file)
app.add_cfg_Parameter('process.TFileService.fileName','cms.string')
app.add_cfg_Parameter('process.rpcTechnicalTrigger.ConfigFile','cms.untracked.string')

sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1

rm = RootMerger()
rm.overwrite = True
rm.ignorefailed = True

ff = File( name=dataset )
ff.subdir = '/castor/cern.ch/user/b/boudoul/COSM_312_RECO/'
fdata = CMSDataset( ff , 'castor' )


for config in hwconfigs:
	
	myjob = Job( application = app, backend = 'LSF' )
	myjob.name = 'rpctt.private.cosmics'
	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'

	dbfileB = File( name=config )
	dbfileB.subdir = cmsswver
	
	myjob.inputsandbox.append( dbfileA )
	myjob.inputsandbox.append( dbfileB )
	myjob.inputsandbox.append( dbfileC )
	
	output = 'rpctt_results_PrivProd.root'
	
	rm.files = [output]
	myjob.application.args = [ output , config ]
	myjob.outputsandbox = [output]

	myjob.splitter = sp
	myjob.merger = rm
	myjob.backend.queue = 'cmscaf1nd'

	myjob.submit()

print "job submission done."
	



