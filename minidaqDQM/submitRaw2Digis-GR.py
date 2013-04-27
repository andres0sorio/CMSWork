# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...

import sys,os
from optparse import OptionParser
#---------------------------------------------------------------------------
#---------------------------------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="runid",
                  help="Run Id number", metavar="RUNID" )

parser.add_option("-t", type = "string", dest="tag",
                  help="Global run tag", metavar="GLOBAL RUN TAG" )

parser.add_option("-o", type = "string", dest="type",
                  help="Type of job (dqm,ttu)", default='ttu')

parser.add_option("-s", type = "string", dest="stream",
                  help="Stream (A,Express,HLT,...)", metavar="A", default='A')

(options, args) = parser.parse_args()

if options.runid is None:
        parser.error("please give a run number")

if options.tag is None:
        parser.error("please give a global run tag (ex. MWGR_25, CRUZET_II)")

#---------------------------------------------------------------------------
#---------------------------------------------------------------------------

from GangaCMS.Lib.CMSexe import *

type      = options.type
runstr    = options.runid
mwgrid    = options.tag
subprefix = options.stream

cmsswver = 'CMSSW_3_1_1'

app = cmsRun()
app.uselibs = 0
app.cfgfile = File(name='/afs/cern.ch/user/a/aosorio/scratch0/'+ cmsswver +'/src/EventFilter/L1GlobalTriggerRawToDigi/test/r2d-l1Gt-andres.py')
app.version = cmsswver

foutdata = CMSDataset()
foutdata.names=['digis.root']

sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1

runlist = runstr.split(',')

for runid in runlist:
	
	sz = len(runid)
	if sz < 7:
		runpath = runid[0:3]+'/'+runid[3:6]
	option = mwgrid
	prefix='/castor/cern.ch/cms/store/streamer/' + option + '/' + subprefix + '/000/'
	fullpath = prefix + runpath + '/'

	infile = runid + '/list_of_files.txt'
	ff = File( name=infile )
	ff.subdir = fullpath
	fdata = CMSDataset( ff , 'castor' )
	
	myjob = Job( application = app, backend = 'LSF' )
	myjob.name = type + '.step1.' + runid
	myjob.outputdata = foutdata
	myjob.inputdata = fdata

	if len ( myjob.inputdata.names ) > 500:
		myjob.inputdata.SetMaxFiles(500)

	myjob.inputdata.type = 'NewEventStreamFileReader'
	myjob.splitter = sp
	myjob.backend.queue = 'cmscaf1nd'
	
	myjob.submit()

