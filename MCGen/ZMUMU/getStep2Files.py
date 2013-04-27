import sys, os
from optparse import OptionParser
#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-j", type = "string", dest="step2",
                  help="Job Id for step1" )

(options, args) = parser.parse_args()

if options.step2 is None:
        parser.error("please give a job ID")

#--------------------------------------------------------
#--------------------------------------------------------

from GangaCMS.Lib.CMSexe import *

step2 = options.step2
dataset = open('step2-dataset.dat','w')

#--------------------------------------------------------
#--------------------------------------------------------

for js in jobs(step2).subjobs:
	if js.status == 'completed':
		outdir = js.outputdir
		data = js.outputsandbox[0]
		infile = outdir+data
		dataset.writelines( infile + '\n')

dataset.close()

print "Done!"

