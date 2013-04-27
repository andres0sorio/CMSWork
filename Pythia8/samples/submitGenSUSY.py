import sys, os
from optparse import OptionParser
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="cfgfile",
                  help="Configuration file" )

(options, args) = parser.parse_args()

if options.cfgfile is None:
        parser.error("please give the configuration file")
#--------------------------------------------------------

script = options.cfgfile
nevts = 100000

#--------------------------------------------------------

slha = ['SUSY_LM0_sftsht.slha','SUSY_LM5_sftsht.slha','SUSY_LM10_sftsht.slha']

arguments = []

for file in slha:
	arguments.append( [nevts,file] )

#--------------------------------------------------------

app = Root()
app.script = File( script )
app.args = []

sp = ArgSplitter()
sp.args = arguments


#Job declarion and initialisation:
myjob = Job( application = app, backend = 'Local' )
myjob.name = 'susy.gen1'
myjob.inputsandbox = slha
myjob.outputsandbox = ['eventos_pythia8_SUSY_100kev.root']
myjob.splitter = sp

myjob.submit()

print "job submission done."

