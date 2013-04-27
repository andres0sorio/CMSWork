import sys, os
from optparse import OptionParser
#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="cfgfile",
                  help="Configuration file" )

parser.add_option("-m", type = "string", dest="firstev",
                  help="First event")

(options, args) = parser.parse_args()

if options.cfgfile is None:
        parser.error("please give the configuration file")

if options.firstev is None:
        parser.error("please give the first event")
#--------------------------------------------------------
#--------------------------------------------------------

from GangaCMS.Lib.CMSexe import *

cfgfile   = options.cfgfile
fstevt    = int( options.firstev )

#--------------------------------------------------------
maxjobs   = 100
arguments = [ ]

delta = 100 # events per jobs

for i in range(0,maxjobs):
        evt = (i*delta) + fstevt
        arguments.append([evt])
#--------------------------------------------------------

cmsswver = 'CMSSW_3_8_7'

app = cmsRun()
app.uselibs = 0
app.version = cmsswver
#app.platform = 'slc5_amd64_gcc434'
app.platform = 'slc5_ia32_gcc434'
app.cfgfile = File( name=cfgfile )

#First Event parameter:
app.add_cfg_Parameter('process.source.firstEvent','cms.untracked.uint32')

#List of Arguments for this job

#Job declarion and initialisation:
myjob = Job( application = app, backend = 'PBS' )
myjob.name = 'prod.step1.zmumu.raw'
myjob.outputsandbox = ['step1_ZMM_RAW.root']

#Set the Argument Splitter for this job
myjob.splitter = ArgSplitterX()
myjob.splitter.args = arguments
myjob.splitter.AddRndSeed()

myjob.backend.queue = 'cms'

myjob.submit()

print "job submission done."

