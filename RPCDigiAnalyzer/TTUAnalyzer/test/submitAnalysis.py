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
jobname    = 'digi.analyzer.' + runid

infile = runid + '/'

cmsswver  = 'CMSSW_3_3_6_patch3'

prefix   = os.environ['PWD'] + '/'
cfg_file = prefix + config

app = cmsRun()
app.uselibs = 1
app.cfgfile = File(name='cfg_file')
app.version = cmsswver

myjob = Job( application = app, backend = 'LSF' )
myjob.name = jobname
myjob.backend.queue = 'cmscaf8nh'

myjob.outputsandbox.append('histo.root')
myjob.outputsandbox.append('checkdata.out')

dbfile = File( name='list_of_events_100282.txt' )
dbfile.subdir = cmsswver
myjob.inputsandbox.append( dbfile )

ff = File( name=infile )
ff.subdir = ff.subdir = '/castor/cern.ch/user/c/ccmuon/RPC/minidaq/' + runid + '/'
fdata = CMSDataset( ff , 'castor' )

myjob.inputdata = fdata
myjob.inputdata.type = 'PoolSource'

myjob.submit()

