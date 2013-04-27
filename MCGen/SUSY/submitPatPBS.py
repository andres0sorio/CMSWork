import sys, os
from optparse import OptionParser
#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-n", type = "string", dest="step2",
                  help="Job Id for step2" )

(options, args) = parser.parse_args()

if options.step2 is None:
        parser.error("please give a job ID")

#--------------------------------------------------------
#--------------------------------------------------------

from GangaCMS.Lib.CMSexe import *

tmp_file = 'step2-dataset.dat'
step2 = options.step2
cfgfile   = 'patTuple_standard_cfg.py'
dataset = open(tmp_file,'w')

#--------------------------------------------------------
#--------------------------------------------------------

cmsswver = 'CMSSW_3_8_7'

app = cmsRun()
app.uselibs = 0
app.version = cmsswver
app.platform = 'slc5_ia32_gcc434'
app.cfgfile = File( name=cfgfile )

#Job declaration and initialisation:
myjob = Job( application = app, backend = 'PBS' )
myjob.name = 'prod.susy.pattuple'
myjob.outputsandbox = ['susy_patTuple.root']

#Set the Splitter for this job
for js in jobs(step2).subjobs:
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
sp.filesPerJob = 1
sp.maxFiles = -1

myjob.splitter = sp

myjob.backend.queue = 'cms'

myjob.submit()

print "job submission done."

os.system('rm -v ' + tmp_file )

