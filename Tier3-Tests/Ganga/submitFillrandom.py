import sys,os
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
#parser.add_option("-l", type = "string", dest="filelist",
#                  help="File list" )
#
#(options, args) = parser.parse_args()
#
#if options.filelist is None:
#        parser.error("please give a file containig a list of files")
#-----------------------------------------------------
#-----------------------------------------------------

CElement='cale.uniandes.edu.co:8443/cream-pbs-cms'
SEpath=''

ff = File(name = 'fillrandom.C')

app = Root()
app.script = ff

myjob = Job( application = app, backend = 'LCG' )
myjob.name = 'ganga.root'

myjob.backend.middleware = 'GLITE'
myjob.backend.CE = CElement
myjob.outputsandbox = ['fillrandom.root']

myjob.submit()

