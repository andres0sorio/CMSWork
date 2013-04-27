#!/usr/bin/python
# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...

import os,sys
import string

from optparse import OptionParser
#---------------------------------------------------------------------------
#---------------------------------------------------------------------------
parser = OptionParser()
parser.add_option("-t", type = "string", dest="tag",
                  help="Tag applied to skim", metavar="TAG" )

(options, args) = parser.parse_args()

if options.tag is None:
        parser.error("please give a run number")

#---------------------------------------------------------------------------
#---------------------------------------------------------------------------

tag  = options.tag
list = 'list_of_Bit25-MuBkg_skims.txt'
runs = 'list_of_first_collisions_runs.txt'
prefix = 'rfio:'
outname = 'list_first_collisions_runs_with_GMT.txt'
exe  = 'edmDumpEventContent'
stager = 'stager_get -M '

#---------------------------------------------------------------------------

first = 122294
last  = 124275

runlist  = open( runs ,  'r' )
outfile  = open( outname, 'w' )

for info in runlist:
	run = info[:-1]
	cmd = 'cat ./' + run + '/' + list
	files = os.popen(cmd,'r').readlines()
	if len(files) > 0:
		fileA = files[0][:-1]
		cmd = exe + ' ' + prefix + fileA
		prestage = stager + fileA
		os.system(prestage)
		print cmd
		content = []
		content = os.popen(cmd,'r').readlines()
		for line in content:
			pos = line.find( tag )
			if pos > 1:
				print 'Found collection in run:', run
				outfile.writelines(run)

outfile.close()
#---------------------------------------------------------------------------

print 'Done.'

#---------------------------------------------------------------------------
