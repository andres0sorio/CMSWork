import sys, os
from optparse import OptionParser
#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="cfgfile",
                  help="Configuration file" )

(options, args) = parser.parse_args()

if options.cfgfile is None:
        parser.error("please give the configuration file")
#--------------------------------------------------------
#--------------------------------------------------------

from GangaCMS.Lib.CMSexe import *

cfgfile  = options.cfgfile

cmsswver = 'CMSSW_3_8_1'

cfg_file = cfgfile

app = cmsRun()
app.uselibs = 0
app.version = cmsswver
app.platform = os.environ['SCRAM_ARCH']
app.cfgfile = File( name=cfg_file )

#First Event parameter:
app.add_cfg_Parameter('process.source.firstEvent','cms.untracked.uint32')

#List of Arguments for this job
arguments = [ [1],[2] ]

#Job declarion and initialisation:
myjob = Job( application = app, backend = 'Local' )
myjob.name = 'test.prod.step1.raw'
myjob.outputsandbox = ['step1_SUSY_LM2_RAW.root']

#Set the Argument Splitter for this job
myjob.splitter = ArgSplitterX()
myjob.splitter.args = arguments
myjob.splitter.AddRndSeed()

myjob.submit()

print "job submission done."

