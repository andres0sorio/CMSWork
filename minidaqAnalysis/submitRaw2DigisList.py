import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="filelist",
                  help="Run id list", metavar="RUN LIST" )

parser.add_option("-o", type = "string", dest="type",
                  help="Type of job (dqm,ttu)", default='ttu')

(options, args) = parser.parse_args()

if options.filelist is None:
        parser.error("please give a run number")

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

type   = options.type

filelist = open ( options.filelist , 'r' )

cmsswver = 'CMSSW_2_2_13'

app = cmsRun()
app.uselibs = 0
app.cfgfile = File(name='/afs/cern.ch/user/a/aosorio/scratch0/'+ cmsswver +'/src/DQM/r2d-andres.py')
app.version = cmsswver

prefix='/castor/cern.ch/cms/store/streamer/PrivMuon/A/000/'

runs = filelist.readlines()

for i in runs:

	runid = i[:-1]

	sz     = len(runid)

	if sz <  6:
		runpath = '0'+runid[0:2]+'/'+runid[2:5]
	if sz == 6:
		runpath = runid[0:3]+'/'+runid[3:6]

	myjob = Job( application = app, backend = 'LSF' )
	myjob.name = type + '.step1.' + runid
	myjob.backend.queue = 'cmscaf1nd'

	fullpath = prefix + runpath + '/'
	infile = runid + '/list_of_files.txt'

	ff = File( name=infile )
	ff.subdir = fullpath

	fdata = CMSDataset( ff , 'castor' )

	foutdata = CMSDataset()
	foutdata.names=['digis.root']
	myjob.outputdata = foutdata

	myjob.inputdata = fdata
	myjob.inputdata.type = 'NewEventStreamFileReader'

	sp = SplitByFiles()
	sp.filesPerJob = 1
	sp.maxFiles = -1

	myjob.splitter = sp

	myjob.submit()

