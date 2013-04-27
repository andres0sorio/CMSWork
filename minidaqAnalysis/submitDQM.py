# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...

import sys
from optparse import OptionParser
#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="runid",
                  help="Run Id number", metavar="RUNID")

parser.add_option("-t", type = "string", dest="tag",
                  help="Global run tag", default='minidaq', metavar="GLOBAL RUN TAG" )

parser.add_option("-o", type = "string", dest="type",
                  help="Type of job (dqm,ttu)", default='ttu' )

(options, args) = parser.parse_args()

if options.runid is None:
        parser.error("please give a run number")
	
#-------------------------------------------------------------------------------------
#-------------------------------------------------------------------------------------

from GangaCMS.Lib.CMSexe import *

type   = options.type
runid  = options.runid
infile = runid + '/list_of_digis.txt'
mwgrid = options.tag

cmsswver = 'CMSSW_3_1_1'

app = cmsRun()
app.uselibs = 0
app.cfgfile = File(name='/afs/cern.ch/user/a/aosorio/scratch0/'+ cmsswver +'/src/DQM/dqm_digi.py')
app.version = cmsswver


myjob = Job( application = app, backend = 'LSF' )
myjob.name = type + '.step2.' + runid

myjob.backend.queue = 'cmscaf1nh'
myjob.backend.queue = 'cmscaf1nd'

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

#foutdata = CMSDataset()
#foutdata.names=['RPCDQM.root']
#myjob.outputdata = foutdata

myjob.outputsandbox = ['RPCDQM.root']

sp = SplitByFiles()
sp.filesPerJob = 10
sp.maxFiles = -1

rm = RootMerger()
rm.files = ['RPCDQM.root']
rm.overwrite = True
rm.ignorefailed = True

if len( myjob.inputdata.names ) > 1:
	myjob.merger = rm

myjob.splitter = sp
	
myjob.submit()

