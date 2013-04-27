import sys,os
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="runid",
                  help="Run Id number" )

(options, args) = parser.parse_args()

if options.runid is None:
        parser.error("please give a run number")
#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

runid      = options.runid
jobname    = 'ttu.LTCAnal.' + runid

infile = runid + '/list_of_digis.txt'

app = cmsRun()
app.uselibs = 1
app.cfgfile = File(name='/afs/cern.ch/user/a/aosorio/scratch0/CMSSW_2_2_9/src/StudyL1Trigger/LTCTtuAnalyzer/test/ltcttuanalyzer_cfg.py')
app.version = 'CMSSW_2_2_9'

myjob = Job( application = app, backend = 'LSF' )
myjob.name = jobname
myjob.backend.queue = 'cmscaf1nh'

foutdata = CMSDataset()
foutdata.names=['histo.root']
myjob.outputdata = foutdata

ff = File( name=infile )
ff.subdir = ff.subdir = '/castor/cern.ch/user/c/ccmuon/RPC/minidaq/' + runid + '/'
fdata = CMSDataset( ff , 'castor' )

myjob.inputdata = fdata
myjob.inputdata.type = 'PoolSource'

sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1

myjob.splitter = sp

myjob.submit()

