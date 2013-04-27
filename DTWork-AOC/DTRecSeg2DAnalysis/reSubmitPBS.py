import sys, os
from optparse import OptionParser
#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-j", type = "string", dest="jobid",
                  help="Job Id" )

parser.add_option("-s", type = "string", dest="jobstatus",
                  help="Job Status" )

(options, args) = parser.parse_args()

if options.jobid is None:
        parser.error("please give a job ID")

#--------------------------------------------------------
#--------------------------------------------------------

from GangaCMS.Lib.CMSexe import *

jobid = options.jobid
jobstatus = options.jobstatus

#--------------------------------------------------------
#--------------------------------------------------------

counter = 0

for js in jobs(jobid).subjobs:
        if (js.status == jobstatus) :
                if ( jobstatus == 'submitted' ):
                     js.kill()
	        js.resubmit()
		counter = counter + 1
	else:
		print "This job is fine"

print "Total jobs resubmitted: ", counter



