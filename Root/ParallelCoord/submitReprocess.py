import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="runid",
                  help="Run Id number", metavar="RUNID" )

parser.add_option("-t", type = "string", dest="type",
                  help="Type of job (repro,..)", default='repro')

(options, args) = parser.parse_args()

if options.runid is None:
        parser.error("please give a run number")

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

type    = options.type
runid   = options.runid
infile  = runid + '/list_of_files.txt'
prefix  = 'i.'+ runid + '.'
afspath     = os.getcwd() + '/'

ScriptArguments = []

cmd  = 'ls ' + runid + '/' + prefix +'*'
files = os.popen(cmd,'r').readlines()

app = Root()
app.version='5.18.00'
app.script='processFile.C'

myjob = Job( application = app, backend = 'LSF' )
myjob.name = type + '.l1gt.' + runid

input = File( name= afspath + infile )
myjob.inputsandbox.append( input )

input = File( name=afspath + 'L1GtExtractedInfo_cc.so')
myjob.inputsandbox.append( input )

input = File( name= afspath + 'ReconstructData_C.so')
myjob.inputsandbox.append( input )

for ff in files:
    source = ff[:-1] #...remove the annoying '\n'
    inmap = source.split('/')[-1]
    tmparg = [ 'list_of_files.txt' , inmap ]
    ScriptArguments.append( tmparg )
    input = File ( name = afspath + ff[:-1] )
    myjob.inputsandbox.append( input )

foutdata = 'l1Gtinformation.txt.gz'
myjob.outputsandbox.append( foutdata )

sp = ArgSplitter( args=ScriptArguments )
myjob.splitter = sp

myjob.backend.queue = 'cmscaf1nd'
###myjob.backend.queue = '1nh'

myjob.submit()

