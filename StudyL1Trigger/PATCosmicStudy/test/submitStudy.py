import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="dataset",
                  help="Run id (dataset)" )

(options, args) = parser.parse_args()

if options.dataset is None:
        parser.error("please give a run ID dataset type")

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

runid     = options.dataset
runlist   = runid.split(',')

cmsswver  = 'CMSSW_3_1_2'

prefix    = os.environ['PWD'] + '/'
cfg_file  = prefix + 'patcosmicstudy_cfg.py' 

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

for run in runlist:

	myjob = Job( application = app, backend = 'LSF' )
	myjob.name = 'pat.craft2.study.' + run

        infile = run + '/list_of_files.txt'
        
        fdata = CMSDataset( File( name=infile ) , 'castor' )
	myjob.inputdata = fdata
	
	myjob.outputsandbox = ['histo.root']
        
	myjob.splitter = sp
        
        myjob.merger = rm
	
	myjob.backend.queue = 'cmscaf1nd'
        
	myjob.submit()

print "job submission done."


