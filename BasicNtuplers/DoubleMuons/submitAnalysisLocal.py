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
cfgfile   = 'doublemuons_cfg.py'

#--------------------------------------------------------

outfile  = 'ntupler_output.root'
cmsswver = 'CMSSW_4_4_4'

app = cmsRun()
app.uselibs = 1
app.version = cmsswver
app.platform = 'slc5_amd64_gcc434'
app.cfgfile = File( name=cfgfile )

#List of Arguments for this job

#Job declarion and initialisation:
myjob = Job( application = app, backend = 'Local' )
myjob.name = 'ntupler.analysis'

myjob.outputsandbox = [outfile]

fdata = CMSDataset( File( name = filelist ), 'local' )
myjob.inputdata = fdata

#create a splitter
sp = SplitByFiles()
sp.filesPerJob = 20
sp.maxFiles = -1
myjob.splitter = sp

#create a Root Merger
rm = RootMerger()
rm.files = [outfile]         # Files to merge
rm.overwrite = True          # Overwrite output files
rm.ignorefailed = True       # ignore root files that failed to open

myjob.merger = rm            

myjob.submit()

print "job submission done."

