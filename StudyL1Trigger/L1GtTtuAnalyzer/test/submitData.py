import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-d", type = "string", dest="dataset",
                  help="Dataset name" )

(options, args) = parser.parse_args()

if options.dataset is None:
        parser.error("please give a dataset type")
#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

dataset  = options.dataset
runid  = options.dataset
infile = runid + '/list_of_digis.txt'

tools     = cmsRunTools()
cmsswver  = tools.getSW( os.environ['PWD'] )

prefix   = os.environ['PWD']
cfg_file = prefix + 'l1gtttuanalyzer_cfg.py' 

app = cmsRun()
app.uselibs = 1
app.version = cmsswver

ff = File( name=infile )
ff.subdir = ff.subdir = '/castor/cern.ch/user/c/ccmuon/RPC/minidaq/' + runid + '/'
fdata = CMSDataset( ff , 'castor' )

sp = SplitByFiles()
sp.filesPerJob = 15
sp.maxFiles = -1

app.cfgfile = File( name=cfg_file )

myjob = Job( application = app, backend = 'LSF' )
myjob.name = 'ttugt.data.' + dataset
myjob.inputdata = fdata
myjob.inputdata.type = 'PoolSource'

myjob.outputsandbox = ['histo.root']

myjob.splitter = sp

rm = RootMerger()
rm.files = ['histo.root']
rm.overwrite = True
rm.ignorefailed = True

myjob.merger = rm

myjob.backend.queue = 'cmscaf1nh'
myjob.submit()

print "job submission done."




