import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="dataset",
                  help="Run id (dataset)" )

parser.add_option("-g", type = "string", dest="globaltag",
                  help="Global TAG" )

(options, args) = parser.parse_args()

if options.dataset is None:
        parser.error("please give a run ID dataset type")

if options.globaltag is None:
        parser.error("please give a Global TAG")

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

inputfile = options.dataset
globaltag = options.globaltag

cmsswver  = 'CMSSW_3_3_6_patch3'

prefix   = os.environ['PWD']
cfg_file = prefix + '/' + 'makeL1Ntuple_cfg.py'

cfifiles = ['l1EgammaRecoTreeProducer_cfi.py',
	    'l1ExtraTreeProducer_cfi.py',
	    'l1JetRecoTreeProducer_cfi.py',
	    'l1MuonRecoTreeProducer_cfi.py',
	    'l1NtupleProducer_cfi.py']

segments = inputfile.split('/')
runid = segments[2]

app = cmsRun()
app.uselibs = 1
app.version = cmsswver
app.cfgfile = File( name=cfg_file )
app.add_cfg_Parameter('process.GlobalTag.globaltag','cms.string')

sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1

rm = RootMerger()
rm.files = ['L1Tree.root']
rm.overwrite = True
rm.ignorefailed = True

ff = File( name=inputfile )
fdata = CMSDataset( ff , 'grid' )
	
myjob = Job( application = app, backend = 'LSF' )
myjob.application.args = [ globaltag ]

for cfi in cfifiles:
	myjob.inputsandbox.append( File( name=cfi, subdir= cmsswver) )

myjob.name = 'l1dpg.ntuple.' + runid
myjob.inputdata = fdata
myjob.inputdata.type = 'PoolSource'
myjob.outputsandbox = ['L1Tree.root']
myjob.splitter = sp
myjob.merger = rm
myjob.backend.queue = 'cmscaf1nd'

myjob.submit()
	
print "job submission done."
