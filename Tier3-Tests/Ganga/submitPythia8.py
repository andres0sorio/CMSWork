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

CElement='cale.uniandes.edu.co:8443/cream-pbs-uniandes'
SEpath=''
outfile = 'eventos_pythia8_singlediff.root'

ff = File(name = 'pythia8_singleDiff_A.C')

app = Root()
app.script = ff

myjob = Job( application = app, backend = 'LCG' )
myjob.name = 'ganga.pythia'

myjob.backend.middleware = 'GLITE'
myjob.backend.CE = CElement
myjob.outputsandbox = [outfile]

sp = ArgSplitter()
sp.args = [[10],[10]]

myjob.splitter = sp

#create a Root Merger
rm = RootMerger()
rm.files = [outfile]         # Files to merge
rm.overwrite = True          # Overwrite output files
rm.ignorefailed = True       # ignore root files that failed to open

myjob.merger = rm

myjob.submit()

