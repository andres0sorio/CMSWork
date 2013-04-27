import sys
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
jobname    = 'ttudata.step1.' + runid
steponejob = -1

digifilelist = open('digi_file_list.txt','w')

for j in jobs:
	if j.name == jobname:
		steponejob = j.id

steponejob = 22

if steponejob != -1:
	pjob = jobs(steponejob)
	for sj in pjob.subjobs:
		filename = sj.outputdir + 'digis.root'
		isfileok = os.path.isfile(filename)
		if isfileok:
			digifilelist.writelines(filename+'\n')

digifilelist.close()

app = cmsRun()
app.uselibs = 1
app.cfgfile = File(name='/afs/cern.ch/user/a/aosorio/scratch0/CMSSW_2_1_9/src/RPCDigiAnalyzer/TTUAnalyzer/test/ttuanalyzer_cfg.py')
app.version = 'CMSSW_2_1_9'

myjob = Job( application = app, backend = 'LSF' )
myjob.name = 'ttudata.step2.' + runid
myjob.backend.queue = '1nh'

myjob.outputsandbox.append('results.root')

ff = File( name=digifilelist.name )
fdata = CMSDataset( ff , 'local' )

myjob.inputdata = fdata

sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1

rm = RootMerger()
rm.files = ['results.root']
rm.overwrite = True
rm.ignorefailed = True

myjob.splitter = sp
myjob.merger = rm

##myjob.submit()

