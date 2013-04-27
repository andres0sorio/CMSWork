import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()

parser.add_option("-f", type = "string", dest="skims",
                  help="Skim list" )

parser.add_option("-t", type = "string", dest="tag",
                  help="Tag this selection" )

parser.add_option("-g", type = "string", dest="globaltag",
                  help="Global Tag" )

(options, args) = parser.parse_args()

if options.skims is None:
        parser.error("please give Skim list")

if options.tag is None:
        parser.error("please provide a tag")

if options.globaltag is None:
        parser.error("please provide a global tag")

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

infile    = options.skims

globaltag = options.globaltag

tag       = options.tag
tag = '_' + tag + '_'

tools     = cmsRunTools()
cmsswver  = tools.getSW( os.environ['PWD'] )

outputdir = '/castor/cern.ch/user/a/aosorio/gridfiles/ganga/TTUSkims/'

prefix    = os.environ['PWD'] + '/'
cfg_file  = prefix + 'ttuSkims_alg124_cfg.py' 

app = cmsRun()
app.uselibs = 1
app.version = cmsswver

app.cfgfile = File( name=cfg_file )
app.add_cfg_Parameter('process.source.fileNames','cms.untracked.vstring')
app.add_cfg_Parameter('process.out.fileName','cms.untracked.string')
app.add_cfg_Parameter('process.GlobalTag.globaltag','cms.string')

runlist  = []
filelist = []

runinfo = open(infile,'r')

for line in runinfo.readlines():
	run = line.split('/')
	runlist.append( run[-2] )
	filelist.append( 'rfio:' + line[:-1] )
runinfo.close()

k=0
for runid in runlist:

	outpath  = './COLLISIONS/' + runid + '/'

	datafile = infile
	ff = File( name=datafile )
	fdata = CMSDataset( ff , 'castor' )

	arguments = []
	outputnames = []
	
	outfile = 'TTUMergedSkim' + tag + runid + '_' + str(k) + '.root'

	file = filelist[k]
	print runid, file
	
	arguments.append( file )
	arguments.append( outfile )
	arguments.append( globaltag )

	outputnames.append(outfile)

	newlist = outpath + 'list_of' + tag + 'skims.txt'
	localoutput = open( newlist, 'w' )
	localoutput.writelines( outputdir + runid + '/' + outfile + '\n' )
	localoutput.close()
	
	myjob = Job( application = app, backend = 'LSF' )
	myjob.name = 'ttu.skim' + tag + '.'  + runid
	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'
	myjob.application.args = arguments
	
	foutdata = CMSDataset()
	foutdata.names = outputnames
	foutdata.subdir = outputdir + runid
	myjob.outputdata = foutdata

	myjob.backend.queue = 'cmscaf1nd'

	myjob.submit()

	k=k+1

print "job submission done."


