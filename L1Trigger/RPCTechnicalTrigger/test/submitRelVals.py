import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-d", type = "string", dest="dataset",
                  help="Dataset name" )

(options, args) = parser.parse_args()

if options.dataset is None:
        parser.error("please give a dataset type")
#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

hwconfigs=[]
hwconfigs.append( 'hardware-pseudoconfig-RBC-3.txt' )
hwconfigs.append( 'hardware-pseudoconfig-RBC-4.txt' )
hwconfigs.append( 'hardware-pseudoconfig-RBC-5.txt' )
hwconfigs.append( 'hardware-pseudoconfig-TTU-4.txt' )
hwconfigs.append( 'hardware-pseudoconfig-TTU-5.txt' )
hwconfigs.append( 'hardware-pseudoconfig-TtuOrRbc-45.txt' )

prefix   = '/afs/cern.ch/user/a/aosorio/scratch0/CMSSW_3_1_0_pre7/src/L1Trigger/RPCTechnicalTrigger/test/'
cfg_file = prefix + 'lsfRelVal_cfg.py' 
tmpfile  = prefix + 'tmpfile.py'

dataset  = options.dataset
infile = dataset + '/list_of_digis.txt'

app = cmsRun()
app.uselibs = 1
app.version = 'CMSSW_3_1_0_pre7'


dbfileA = File( name='myrbconfig.db' )
dbfileA.subdir = 'CMSSW_3_1_0_pre7'

foutdata = CMSDataset()
foutdata.names=['rpcttbits.root']

ff = File( name=infile )
ff.subdir = ff.subdir = '/castor/cern.ch/cms'
fdata = CMSDataset( ff , 'castor' )

sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1


for hconf in hwconfigs:

	cmd = 'cp ' + cfg_file + ' ' + tmpfile
	os.system(cmd)
	
	outfile = open(tmpfile,'a')
	cmd = 'process.rpcTechnicalTrigger.ConfigFile=cms.untracked.string(\"' + hconf + '\") \n'
	print cmd
	outfile.writelines(cmd)
	outfile.writelines('#...........')
	outfile.close()
	
	app.cfgfile = File( name=tmpfile )
	
	dbfileB = File( name= hconf )
	dbfileB.subdir = 'CMSSW_3_1_0_pre7'
	
	myjob = Job( application = app, backend = 'LSF' )
	myjob.name = 'rpctt.relval.' + dataset
	myjob.inputdata = fdata
	myjob.inputdata.type = 'PoolSource'
	
	myjob.inputsandbox.append( dbfileA )
	myjob.inputsandbox.append( dbfileB )
	myjob.outputdata = foutdata

	myjob.splitter = sp
	myjob.backend.queue = 'cmscaf1nh'
	myjob.submit()
	print "job submission done."
	os.system('rm ' + tmpfile )



