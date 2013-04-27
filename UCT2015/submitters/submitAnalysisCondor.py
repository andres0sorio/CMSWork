import sys, os
from optparse import OptionParser
#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="files",
                  help="List of files" )

parser.add_option("-c", type = "string", dest="config",
                  help="List of files" )

(options, args) = parser.parse_args()

if options.files is None:
        parser.error("please give a job ID")

if options.config is None:
        parser.error("please give a config file")


#--------------------------------------------------------

infile = open( options.files, 'r' )
cfgfile = options.config.split(',')
outfile = 'uct_efficiency_tree.root'

#--------------------------------------------------------

app = Executable(exe=File('./job.csh') )

#Job declarion and initialisation:
myjob = Job( application = app, backend = 'Condor' )
myjob.name = 'l1upg.analysis'

for cfgpy in cfgfile:
	myjob.inputsandbox.append( File(cfgpy) )

myjob.outputsandbox = [outfile]

#Set the Splitter for this job

jobargs = []

for ff in infile.readlines():
	ff[:-1]
	jobargs.append( [ ff[:-1], cfgfile[0] ] )


myjob.splitter = ArgSplitter( args = jobargs )

#create a Root Merger
rm = RootMerger()
rm.files = [outfile]         # Files to merge
rm.overwrite = True          # Overwrite output files
rm.ignorefailed = True       # ignore root files that failed to open

myjob.merger = rm
myjob.submit()

print "job submission done."

