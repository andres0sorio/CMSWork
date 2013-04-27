import sys, os
from optparse import OptionParser
#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-j", type = "string", dest="jobid",
                  help="Job Id" )

(options, args) = parser.parse_args()

if options.jobid is None:
        parser.error("please give a job ID")

#--------------------------------------------------------
#--------------------------------------------------------

from GangaCMS.Lib.CMSexe import *

jobid = options.jobid

#--------------------------------------------------------
#--------------------------------------------------------

counter = 0

for js in jobs(jobid).subjobs:
        if (js.status == 'killed') or (js.status == 'failed'):
	        js.resubmit()
		counter = counter + 1
	elif (js.status == 'submitted'):
		js.kill()
		js.resubmit()
		counter = counter + 1
	else:
		print "this job is fine"

print "Total jobs resubmitted: ", counter


