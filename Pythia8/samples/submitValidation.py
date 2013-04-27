import sys, os
from optparse import OptionParser
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-n", type = "string", dest="njobs",
                  help="Number of jobs" )

parser.add_option("-f", type = "string", dest="infile",
                  help="Input file" )

parser.add_option("-c", type = "string", dest="pdgcode",
                  help="PDG code" )

parser.add_option("-m", type = "string", dest="nevts",
                  help="Maximum number of events in sample" )

(options, args) = parser.parse_args()

if options.njobs is None:
        parser.error("please give a number of jobs")

if options.infile is None:
        parser.error("please give the input file")

if options.pdgcode is None:
        parser.error("please give the pdg code")

if options.nevts is None:
        parser.error("please give maximum number of events")

#--------------------------------------------------------

infile  = options.infile
njobs   = int( options.njobs )
pdgcode = int( options.pdgcode )
nevts   = int( options.nevts )

script  = 'validate.C'
outfile = 'output.root'

#--------------------------------------------------------

arguments = []

rest = nevts % njobs
ievt = 0
devt = (nevts / njobs)  - 1

for k in range(0,njobs):
        last = ievt + devt
	if k == (njobs-1):
		last += rest
        arguments.append( [infile, outfile, pdgcode, ievt, last] )
        ievt += devt + 1

print arguments
#--------------------------------------------------------

app = Root()
app.script = File( script )
app.args = []

sp = ArgSplitter()
sp.args = arguments

rm = RootMerger()
rm.files = [outfile] 
rm.overwrite = True
rm.ignorefailed = True

#Job declarion and initialisation:
myjob = Job( application = app, backend = 'Local' )
myjob.name = 'analysis'
myjob.inputsandbox = [File('Histograms_C.so'), File('PythiaAnalysis_C.so')]
myjob.outputsandbox = [outfile]
myjob.splitter = sp
myjob.merger = rm

myjob.submit()

print "job submission done."

