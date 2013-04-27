import sys
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()

parser.add_option("-r", type = "string", dest="selrun",
                  help="Select a run" )

(options, args) = parser.parse_args()

if options.selrun is None:
        parser.error("please give a run ID dataset type")

#-----------------------------------------------------
#-----------------------------------------------------

from GangaCMS.Lib.CMSexe import *

tag = 'Express'
selruns  = options.selrun.split(',')

for run in selruns:

	for j in jobs:
		if j.name.find( run ) > 0:
			
			outputdir = j.outputdir
			outputfile = j.merger.files[0]
			source = outputdir + outputfile
			rootname = outputfile.split('.')[0]
			newfilename = rootname + '-' + run + '-' + tag + '.root'

			cmd = 'cp -v ' + source + ' ' + newfilename
			os.system(cmd)


