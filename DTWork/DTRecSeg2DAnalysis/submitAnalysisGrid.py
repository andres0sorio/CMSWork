import sys, os
from optparse import OptionParser
#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="filelist",
                  help="file list" )

(options, args) = parser.parse_args()

if options.filelist is None:
        parser.error("please give a file list")

#--------------------------------------------------------
#--------------------------------------------------------

from GangaCMS.Lib.CMSexe import *

filelist = options.filelist
cfgfile   = 'dtrecseg2danalysis_cfg.py'

#--------------------------------------------------------

CElement = 'cale.uniandes.edu.co:8443/cream-pbs-uniandes'
outfile  = 'real-data-histos.root'
cmsswver = 'CMSSW_4_2_5'

app = cmsRun()
app.uselibs = 1
app.version = cmsswver
app.platform = 'slc5_amd64_gcc434'
app.cfgfile = File( name=cfgfile )

#List of Arguments for this job

#Job declarion and initialisation:
myjob = Job( application = app, backend = 'LCG' )
myjob.name = 'dt.analysis'
myjob.backend.CE = CElement

myjob.outputsandbox = [outfile]

fdata = CMSDataset( File( name = filelist ), 'castor' )
myjob.inputdata = fdata

#create a splitter
sp = SplitByFiles()
sp.filesPerJob = 10
sp.maxFiles = -1
myjob.splitter = sp

#create a Root Merger
rm = RootMerger()
rm.files = [outfile]         # Files to merge
rm.overwrite = True          # Overwrite output files
rm.ignorefailed = True       # ignore root files that failed to open

## myjob.merger = rm          #cannot run the RootMerger at tado

#myjob.submit()

print "job submission done."

