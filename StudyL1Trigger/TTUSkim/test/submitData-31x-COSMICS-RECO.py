import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="dataset",
                  help="Run id (dataset)" )

parser.add_option("-f", type = "string", dest="runlist",
                  help="Run info list" )

parser.add_option("-t", type = "string", dest="tag",
                  help="Tag this selection" )

parser.add_option("-c", type = "string", dest="config",
                  help="Configuration file" )

(options, args) = parser.parse_args()

if options.dataset is None:
        parser.error("please give a run ID dataset type")

if options.tag is None:
        parser.error("please provide a tag")

if options.config is None:
        parser.error("please provide a cfg file")

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

dataset   = options.dataset
runlist   = dataset.split(',')
infile    = options.runlist
tag       = options.tag
config    = options.config

tag = '_' + tag + '_'

tools     = cmsRunTools()
cmsswver  = tools.getSW( os.environ['PWD'] )

outputdir = '/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkimsRaw/'

prefix    = os.environ['PWD'] + '/'
cfg_file  = prefix + config

app = cmsRun()
app.uselibs = 1
app.version = cmsswver
app.platform = 'slc5_ia32_gcc434'
app.cfgfile = File( name=cfg_file )
app.add_cfg_Parameter('process.source.fileNames','cms.untracked.vstring')
app.add_cfg_Parameter('process.out.fileName','cms.untracked.string')
app.add_cfg_Parameter('process.GlobalTag.globaltag','cms.string')

runList = []
runinfo = open(infile,'r')

for line in runinfo:
	run = line.split()
	runList.append( [ run[0],run[4] ] )
	
runinfo.close()

for runid in runlist:

	globaltag = ''
	for run in runList:
		if runid == run[0]:
			globaltag = run[1]
			print 'We submit for this run'

	if globaltag == '':
		continue
	outpath  = './CRAFT10/' + runid + '/'
	datafile = outpath + 'list_of_files.txt'
	ff = File( name=datafile )
	fdata = CMSDataset( ff , 'grid' )
	
	k=0
	arguments = []
	outputnames = []
	outfile = outpath + 'list_of' + tag + 'skims.txt'
	localoutput = open( outfile, 'w' )
	for file in fdata.names:
		outfile = 'TTUSkim' + tag + runid + '_' + str(k) + '.root'
		arguments.append( [ file, outfile, globaltag ] )
		outputnames.append(outfile)
		localoutput.writelines( outputdir + runid + '/' + outfile + '\n' )
		k=k+1
	localoutput.close()
	
	myjob = Job( application = app, backend = 'LSF' )
	myjob.name = 'ttu.skim.data.' + runid
	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'
	
	foutdata = CMSDataset()
	foutdata.names = outputnames
	foutdata.subdir = outputdir + runid
	myjob.outputdata = foutdata

	myjob.splitter = ArgSplitter( args = arguments )
	
	myjob.backend.queue = 'cmscaf1nd'

	myjob.submit()

print "job submission done."


