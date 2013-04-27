import sys, os
from time import time
from optparse import OptionParser
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="script",
                  help="script file" )

parser.add_option("-n", type = "string", dest="nevts",
                  help="Number of events per event" )

(options, args) = parser.parse_args()

if options.script is None:
        parser.error("please provide the script to run over")

if options.nevts is None:
        parser.error("please provide the number of events per job")


#--------------------------------------------------------

script = options.script
nevts = int(options.nevts)
outfile = 'eventos_pythia8_100kev.root'
#--------------------------------------------------------

arguments = []

for k in range(0,10):
	current_time = str( time() ).split('.')
	print current_time
	timestamp = ''.join( current_time )[4:]
	rndseed = timestamp + str(k)
	print rndseed
	arguments.append( [nevts, rndseed] )

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
myjob.name = 'sm.gen1'
myjob.outputsandbox = [outfile]
myjob.splitter = sp
myjob.merger = rm

myjob.submit()

print "job submission done."

