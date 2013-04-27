import sys, os
from optparse import OptionParser
#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-j", type = "string", dest="step1",
                  help="Job Id for step1" )

(options, args) = parser.parse_args()

if options.step1 is None:
        parser.error("please give a job ID")

#--------------------------------------------------------
#--------------------------------------------------------

from GangaCMS.Lib.CMSexe import *

step1 = options.step1
dataset = open('step1-dataset.dat','w')

#--------------------------------------------------------
#--------------------------------------------------------

for js in jobs(step1).subjobs:
	if js.status == 'completed':
		outdir = js.outputdir
		data = js.outputsandbox[0]
		infile = outdir+data
		dataset.writelines( infile + '\n')

dataset.close()

print "Done!"

