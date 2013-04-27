import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-j", type = "string", dest="jobid",
                  help="Job id to run over the analyzer" )

(options, args) = parser.parse_args()

if options.jobid is None:
        parser.error("please give a job id")
#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

cmsconfig = Ganga.Utility.Config.getConfig('CMSSW')

jb = jobs( int(options.jobid) )

joboutdir   = cmsconfig['dataOutput']

app = cmsRun()
app.uselibs = 1
app.cfgfile = File(name='/afs/cern.ch/user/a/aosorio/scratch0/CMSSW_3_1_0_pre7/src/StudyL1Trigger/L1GtTechTrig/test/l1gttechtrig_cfg.py')
app.version = 'CMSSW_3_1_0_pre7'

myjob = Job( application = app, backend = 'LSF' )
myjob.name = 'l1gttbits.vis.' + options.jobid

fdata = CMSDataset()

if len ( jb.subjobs ) > 1:
	for jbs in jb.subjobs:
		infile = 'rfio:' + joboutdir + '/' + str(jb.id) + '/' + str(jbs.id) + '/outputdata/rpcttbits.root' 
		fdata.names.append( infile )
		fdata.location = 'castor'

myjob.inputdata = fdata
myjob.inputdata.type = 'PoolSource'

myjob.outputsandbox = ['rpctt_results.root']

sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1

myjob.splitter = sp

rm = RootMerger()
rm.files = ['rpctt_results.root']
rm.overwrite = True
rm.ignorefailed = True

myjob.merger = rm

myjob.backend.queue = '1nh'

myjob.submit()

