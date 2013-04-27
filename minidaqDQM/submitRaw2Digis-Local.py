# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...

import sys,os
from optparse import OptionParser

#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="runid",
                  help="Run Id number", metavar="RUNID" )

parser.add_option("-o", type = "string", dest="type",
                  help="Type of job (dqm,ttu)", default='ttu')

(options, args) = parser.parse_args()

if options.runid is None:
        parser.error("please give a run number")

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

type   = options.type
runid  = options.runid
infile = runid + '/list_of_files.txt'

cmsswver = 'CMSSW_3_5_0_patch1'

prefix   = os.environ['PWD']
cfg_file = prefix + '/' + 'r2d-ltc-andres.py'

app = cmsRun()
app.uselibs = 0
app.platform = 'slc5_ia32_gcc434'
app.cfgfile = File(name=cfg_file)
app.version = cmsswver

myjob = Job( application = app, backend = 'Local' )
myjob.name = type + '.step1.' + runid

sz = len(runid)

#...................
if sz <  6:
	runpath = '0'+runid[0:2]+'/'+runid[2:5]
if sz == 6:
	runpath = runid[0:3]+'/'+runid[3:6]
#...................

prefix='/castor/cern.ch/cms/store/streamer/Minidaq/A/000/'
fullpath = prefix + runpath + '/'

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

jobid = myjob.id

#.......................................................................
# put data back to castor
#

