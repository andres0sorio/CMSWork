import sys
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

runid  = options.runid
infile = runid + '/list_of_digis.txt'

app = cmsRun()
app.uselibs = 1
app.cfgfile = File(name='/afs/cern.ch/user/a/aosorio/scratch0/CMSSW_3_1_0_pre7/src/L1Trigger/RPCTechnicalTrigger/test/lsftest_cfg.py')
app.version = 'CMSSW_3_1_0_pre7'

myjob = Job( application = app, backend = 'LSF' )
myjob.name = 'rpctt.test.' + runid
myjob.backend.queue = '1nh'

ff = File( name=infile )
ff.subdir = ff.subdir = '/castor/cern.ch/user/c/ccmuon/RPC/minidaq/' + runid
fdata = CMSDataset( ff , 'castor' )

myjob.inputdata = fdata
myjob.inputdata.type = 'PoolSource'

dbfile = File( name='myrbconfig.db' )
dbfile.subdir = 'CMSSW_3_1_0_pre7'
myjob.inputsandbox.append( dbfile )

myjob.outputsandbox.append('rpcttbits.root')

sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1

myjob.splitter = sp

##myjob.submit()

