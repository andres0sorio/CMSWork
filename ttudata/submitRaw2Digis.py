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
infile = runid + '/list_of_files.txt'

app = cmsRun()
app.uselibs = 0
app.cfgfile = File(name='/afs/cern.ch/user/a/aosorio/scratch0/CMSSW_2_1_9/src/EventFilter/RPCRawToDigi/r2d-andres.py')
app.version = 'CMSSW_2_1_9'

myjob = Job( application = app, backend = 'LSF' )
myjob.name = 'ttudata.step1.' + runid
myjob.backend.queue = '1nh'

myjob.outputsandbox.append('digis.root')

ff = File( name=infile )
ff.subdir = '/afs/cern.ch/user/a/aosorio/scratch0/ttudata/' + runid
fdata = CMSDataset( ff , 'local' )

myjob.inputdata = fdata
myjob.inputdata.type = 'NewEventStreamFileReader'

sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1

myjob.splitter = sp

##myjob.submit()

