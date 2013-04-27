import sys, os
from optparse import OptionParser
#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-j", type = "string", dest="step1",
                  help="Job Id for step1" )

(options, args) = parser.parse_args()

if options.step1 is None:
        parser.error("please give a job ID")

#--------------------------------------------------------
#--------------------------------------------------------

from GangaCMS.Lib.CMSexe import *

step1 = options.step1
cfgfile   = 'dtrecseg2danalysis_cfg.py'
dataset = open('step1-dataset.dat','w')

#--------------------------------------------------------

#--------------------------------------------------------

outfile = 'ZMM-histos.root'

cmsswver = 'CMSSW_4_2_5'

app = cmsRun()
app.uselibs = 1
app.version = cmsswver
app.platform = 'slc5_amd64_gcc434'
app.cfgfile = File( name=cfgfile )

#List of Arguments for this job

#Job declarion and initialisation:
myjob = Job( application = app, backend = 'PBS' )
myjob.name = 'dt.analysis'
myjob.outputsandbox = [outfile]

#Set the Splitter for this job
for js in jobs(step1).subjobs:
	if js.status == 'completed':
		outdir = js.outputdir
		data = js.outputsandbox[0]
		infile = outdir+data
		dataset.writelines( infile + '\n')

dataset.close()

ff = File(name = 'step1-dataset.dat')
fdata = CMSDataset( ff , 'local' )
myjob.inputdata = fdata

#create a splitter
sp = SplitByFiles()
sp.filesPerJob = 1
sp.maxFiles = -1
myjob.splitter = sp

#create a Root Merger
rm = RootMerger()
rm.files = [outfile]         # Files to merge
rm.overwrite = True          # Overwrite output files
rm.ignorefailed = True       # ignore root files that failed to open

##myjob.merger = rm          #cannot run the RootMerger at tado

myjob.backend.queue = 'cms'

myjob.submit()

print "job submission done."

