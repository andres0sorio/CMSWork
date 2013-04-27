# Andres Osorio

import sys,os
from optparse import OptionParser

#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-s", type = "string", dest="script",
                  help="script to submit" )

parser.add_option("-f", type = "string", dest="infile",
                  help="input data" )

(options, args) = parser.parse_args()

if options.infile is None:
        parser.error("please give a file containig a list of files")

if options.script is None:
        parser.error("please provide the script")
#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

infile = options.infile
script = options.script
njobs  = 5

CElement='cale.uniandes.edu.co:8443/cream-pbs-cms'

app = Executable()
app.exe = File( name = script )
app.args = ['']

myjob = Job( application = app)
myjob.name = 'SEtransfer.uniandes'

myjob.backend = 'LCG' 
myjob.backend.middleware = 'GLITE'
myjob.backend.CE = CElement

sp = ArgSplitter()

#-----------------------------------------------------
myargs = []

cmd = 'split -d -l ' + str(10) + ' ' + infile
os.system(cmd)

for i in range(njobs):
	tmpfile = 'x0' + str(i)
	myjob.inputsandbox.append( File(name=tmpfile) )
        myargs.append(['-d', 'no', '-f', tmpfile ])

print myargs
sp.args = myargs
#-----------------------------------------------------

myjob.splitter = sp
myjob.submit()

print "Excelent, all done!"

