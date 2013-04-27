import sys,os
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="samples",
                  help="Samples name" )

parser.add_option("-v", type = "string", dest="cmsswver",
                  help="CMSSW version" )


(options, args) = parser.parse_args()

if options.samples is None:
        parser.error("please give a dataset type")

if options.cmsswver is None:
        parser.error("please give a CMSSW version")
	
#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

samples   = options.samples
sample_list   = samples.split(',')

cmsswver  = options.cmsswver

hwconfigs=[]
hwconfigs.append( 'hardware-pseudoconfig.txt' )

prefix   = os.environ['PWD'] + '/'
cfg_file = prefix + 'l1gttechtrig_allseq_RelValCosmics_cfg.py' 

relvals_dir  = os.environ['HOME'] + '/scratch0/RelVals/RelVals-Datasets/' + cmsswver + '/'

dbfileA = File( name='myrbconfig.db' )
dbfileA.subdir = cmsswver
dbfileB = File( name=hwconfigs[0] )
dbfileB.subdir = cmsswver
dbfileC = File( name='rpcTechnicalTrigger_cfi.py' )
dbfileC.subdir = cmsswver

app = cmsRun()
app.uselibs = 1
app.version = cmsswver
app.cfgfile = File( name=cfg_file)
app.add_cfg_Parameter('process.TFileService.fileName','cms.string')

sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1

rm = RootMerger()
rm.overwrite = True
rm.ignorefailed = True

for sample in sample_list:

	infile = relvals_dir + sample + '/list_of_files.txt'
	ff = File( name=infile )
	fdata = CMSDataset( ff , 'grid' )
	
	myjob = Job( application = app, backend = 'LSF' )
	myjob.name = 'rpctt.relval.' + sample
	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'
	
	myjob.inputsandbox.append( dbfileA )
	myjob.inputsandbox.append( dbfileB )
	myjob.inputsandbox.append( dbfileC )

	output = 'rpctt_results_' + cmsswver + '_' + sample + '.root'
	
	rm.files = [output]
	myjob.application.args = [ output ]
	myjob.outputsandbox = [output]
		
	myjob.splitter = sp
	myjob.merger = rm
	myjob.backend.queue = 'cmscaf1nd'

	myjob.submit()

	print "job submission done."
	



