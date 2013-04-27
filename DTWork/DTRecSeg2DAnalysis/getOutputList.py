import sys, os
from optparse import OptionParser
#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-j", type = "string", dest="jobid",
                  help="Job Id" )

parser.add_option("-o", type = "string", dest="option",
                  help="Job Status" )

(options, args) = parser.parse_args()

if options.jobid is None:
        parser.error("please give a job ID")

if options.option is None:
        parser.error("please give an option")


#--------------------------------------------------------
#--------------------------------------------------------

from GangaCMS.Lib.CMSexe import *

jobid = options.jobid
option = options.option
jobstatus = 'completed'
filename = 'list_of_results_' + option + '.dat'

output = open( filename, 'w')

#--------------------------------------------------------
#--------------------------------------------------------

for js in jobs(jobid).subjobs:
        if (js.status == jobstatus) :
		outputdir = js.outputdir
		sandbox = js.outputsandbox[0]
		outfile = outputdir + sandbox
		output.writelines(outfile + '\n')

output.close()

print "All done. Output contains list of files"





