import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="dataset",
                  help="Run id (dataset)" )

parser.add_option("-t", type = "string", dest="tag",
                  help="Tag this selection" )

(options, args) = parser.parse_args()

if options.dataset is None:
        parser.error("please give a run ID dataset type")

if options.tag is None:
        parser.error("please provide a tag")

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

dataset   = options.dataset
runlist   = dataset.split(',')
tag       = options.tag

tag = '_' + tag + '_'
		
cmsswver  = 'CMSSW_3_3_6_patch3'

outputdir = '/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/'

prefix    = os.environ['PWD'] + '/'
cfg_file  = prefix + 'ttuMergeSkims_cfg.py' 

app = cmsRun()
app.uselibs = 0
app.version = cmsswver
app.add_cfg_Parameter('process.out.fileName','cms.untracked.string')
app.cfgfile = File( name=cfg_file )

for runid in runlist:
	
	outpath  = './COLLISIONS/' + runid + '/'
	
	datafile = outpath + 'list_of' + tag + 'skims.txt'
	fs = os.path.isfile(datafile)
	
	if fs == False:
		print datafile + ' not found'
		continue
	
	ff = File( name=datafile )
	fdata = CMSDataset( ff , 'castor' )
	
	outputnames = []
	arguments = []
	outfile = 'TTUMergedSkim' + tag + runid + '.root'
	outputnames.append(outfile)
	arguments.append( outfile )
	
	myjob = Job( application = app, backend = 'LSF' )
	myjob.name = 'ttu.mergeSkim.data.' + runid
	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'
	myjob.application.args = arguments
	
	foutdata = CMSDataset()
	foutdata.names = outputnames
	foutdata.subdir = outputdir + runid
	myjob.outputdata = foutdata
	
	myjob.backend.queue = 'cmscaf1nd'

	myjob.submit()

print "job submission done."


