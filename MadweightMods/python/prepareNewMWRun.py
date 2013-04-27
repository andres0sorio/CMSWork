#!/usr/bin/python
import sys, os
from optparse import OptionParser
#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()

parser.add_option("-i", type = "string", dest="baseid",
		  help="Base id")

parser.add_option("-o", type = "string", dest="jobid",
		  help="Job id")

(options, args) = parser.parse_args()

if options.jobid is None:
        parser.error("Job Id")

if options.baseid is None:
	parser.error("Base Id")
#--------------------------------------------------------
#--------------------------------------------------------
cpcmd = 'cp -v '
jobid  = options.jobid
baseid = options.baseid

cmd = cpcmd + '-r Template ' + jobid
os.system(cmd)

input_files=['Cards/proc_card.dat',
	     'Events/input.lhco',
	     'Source/MadWeight_File/Python/clean.py',
	     'Source/MadWeight_File/Tools/next_perm.f',
	     'Source/MadWeight_File/MWP_template/driver.f']

for path in input_files:
	source = baseid + '/' + path
	pos = path.rfind('/')
	dir = path[:pos]
	file = path.split('/')[-1]
	target = jobid + '/' + dir + '/' + file
	cmd = cpcmd + source + ' ' + target
	os.system(cmd)

input_files=['Cards/run_card.dat', 'Cards/MadWeight_card.dat']

cmd = 'cd ' + jobid + ' ; ./bin/PassToMadWeight; ./bin/newprocess'
os.system(cmd)

for path in input_files:
	source = baseid + '/' + path
	pos = path.rfind('/')
	dir = path[:pos]
	file = path.split('/')[-1]
	target = jobid + '/' + dir + '/' + file
	cmd = cpcmd + source + ' ' + target
	os.system(cmd)

