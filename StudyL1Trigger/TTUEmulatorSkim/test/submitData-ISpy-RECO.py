import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="inputfile",
                  help="Run info list" )

parser.add_option("-g", type = "string", dest="globaltag",
                  help="Global Tag" )

(options, args) = parser.parse_args()

if options.inputfile is None:
        parser.error("please provide an inputfile")

if options.globaltag is None:
        parser.error("please provide a globaltag")

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

infile    = options.inputfile
globaltag = options.globaltag

#development area instead of analysis
cmsconf = getConfig('CMSSW')
workarea = '/afs/cern.ch/user/a/aosorio/scratch0/Development/'
cmsconf.setUserValue('workArea',workarea)

#-----------------------------------------------------

cmsswver  = 'CMSSW_3_6_0_pre3'
outputdir = '/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUEmulatorSkims/'
config    = 'ispy_36X_cfg.py'
prefix    = os.environ['PWD'] + '/'
cfg_file  = prefix + config

app = cmsRun()
app.uselibs = 1
app.version = cmsswver
app.platform = 'slc5_ia32_gcc434'

app.cfgfile = File( name=cfg_file )
app.add_cfg_Parameter('process.source.fileNames','cms.untracked.vstring')
app.add_cfg_Parameter('process.ISpyService.outputFileName','cms.untracked.string')
app.add_cfg_Parameter('process.GlobalTag.globaltag','cms.string')
		
ff = File( name=infile )
fdata = CMSDataset( ff , 'castor' )
	
arguments  = []
outputnames = []
options = infile.split('/')

runid = options[0] + '-' + options[1]

k=0
for file in fdata.names:
	outfile = 'TTUEmu'+ runid + '_' + str(k) + '.ig'
	arguments.append( [ file, outfile, globaltag ] )
	outputnames.append( outfile )
	k=k+1
	
myjob = Job( application = app, backend = 'LSF' )
myjob.name = 'ttu.emu.ispy'
myjob.inputdata = fdata
myjob.inputdata.type = 'PoolSource'
myjob.inputsandbox.append( File(name='rpcTechnicalTrigger_cfi.py', subdir=cmsswver) )
	
foutdata = CMSDataset()
foutdata.names = ['TTUEmu*']
foutdata.subdir = outputdir + runid + '/'
myjob.outputdata = foutdata
myjob.splitter = ArgSplitter( args = arguments )
myjob.backend.queue = 'cmscaf1nd'
myjob.submit()

print "job submission done."
