import sys, os
from optparse import OptionParser
#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-n", type = "string", dest="step1",
                  help="Job Id for step1" )

(options, args) = parser.parse_args()

if options.step1 is None:
        parser.error("please give a job ID")

#--------------------------------------------------------
#--------------------------------------------------------

from GangaCMS.Lib.CMSexe import *
tmp_file = 'step1-dataset.dat'
step1 = options.step1
cfgfile   = 'step2_example.py'
dataset = open(tmp_file,'w')

#--------------------------------------------------------

#--------------------------------------------------------

cmsswver = 'CMSSW_3_8_1'

app = cmsRun()
app.uselibs = 0
app.version = cmsswver
#app.platform = 'slc5_amd64_gcc434'
app.platform = 'slc5_ia32_gcc434'
app.cfgfile = File( name=cfgfile )

#List of Arguments for this job

#Job declarion and initialisation:
myjob = Job( application = app, backend = 'PBS' )
myjob.name = 'prod.step2.susy.reco'
myjob.outputsandbox = ['step2_RAW2DIGI_L1Reco_RECO.root']

#Set the Splitter for this job
for js in jobs(step1).subjobs:
	if js.status == 'completed':
		outdir = js.outputdir
		data = js.outputsandbox[0]
		infile = outdir+data
		dataset.writelines( infile + '\n')

dataset.close()

ff = File(name = tmp_file )
fdata = CMSDataset( ff , 'local' )
myjob.inputdata = fdata

#create a splitter
sp = SplitByFiles()
sp.filesPerJob = 20
sp.maxFiles = -1

myjob.splitter = sp

myjob.backend.queue = 'cms'

myjob.submit()

print "job submission done."

