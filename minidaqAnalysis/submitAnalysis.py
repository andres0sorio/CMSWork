# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...

import sys,os
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="runid",
                  help="Run Id number" )

parser.add_option("-t", type = "string", dest="tag",
                  help="Global run tag", default='minidaq', metavar="GLOBAL RUN TAG" )

(options, args) = parser.parse_args()

if options.runid is None:
        parser.error("please give a run number")
#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

runid      = options.runid
jobname    = 'ttu.digiAnalyzer.' + runid
mwgrid     = options.tag

cmsswver   = 'CMSSW_2_2_13'

infile = runid + '/list_of_digis.txt'

app = cmsRun()
app.uselibs = 1
app.cfgfile = File(name='/afs/cern.ch/user/a/aosorio/scratch0/'+ cmsswver +'/src/RPCDigiAnalyzer/TTUAnalyzer/test/ttuanalyzer_cfg.py')
app.version = cmsswver

##myjob.outputsandbox.append('histo.root')
##myjob.outputsandbox.append('checkdata.out')

myjob = Job( application = app, backend = 'LSF' )
myjob.name = jobname
myjob.backend.queue = 'cmscaf1nh'

foutdata = CMSDataset()
foutdata.names=['histo.root','checkdata.out']
myjob.outputdata = foutdata

sourcedir = ''

if mwgrid == 'minidaq':
	sourcedir   = '/castor/cern.ch/user/c/ccmuon/RPC/minidaq/' + str(runid) + '/'
else:
	sourcedir   = '/castor/cern.ch/user/c/ccmuon/RPC/GlobalRuns/' + mwgrid + '/' + str(runid) + '/'

ff = File( name=infile )
ff.subdir = ff.subdir = sourcedir
fdata = CMSDataset( ff , 'castor' )

myjob.inputdata = fdata
myjob.inputdata.type = 'PoolSource'

sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1

myjob.splitter = sp

myjob.submit()

