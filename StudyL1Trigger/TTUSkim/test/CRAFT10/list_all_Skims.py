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

tag      = options.tag
outfile  = 'selected_runs.txt'
skimlist = 'list_of_skim_files_' + tag + '.txt'

#---------------------------------------------------------------------------

skim = 'list_of_' + tag + '_skims.txt'
cmd  = 'find . -name \"*' + skim + '*\" > ' + outfile 
excode = os.system(cmd)


runlist  = open( outfile ,  'r' )
k = 0
for run in runlist:
	run = run[:-1]
	print run
	if k == 0:
		op = ' > '
	else:
		op = ' >> '
		
	cmd = 'cat ' + run + op + skimlist
	excode = os.system(cmd)
	k=k+1
	
#---------------------------------------------------------------------------

print 'Done.'

#---------------------------------------------------------------------------
