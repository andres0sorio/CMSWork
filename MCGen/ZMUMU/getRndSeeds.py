import sys, os
from optparse import OptionParser
#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-n", type = "string", dest="njob",
                 help="N job" )

(options, args) = parser.parse_args()

if options.njob is None:
        parser.error("N job")
#--------------------------------------------------------
#--------------------------------------------------------

from GangaCMS.Lib.CMSexe import *

filename = 'rndseed_job_' + options.njob + '.txt'

outfile = open(filename,'w')

njob = int ( options.njob )

j = jobs(njob)

for sj in j.subjobs:
	idjob = sj.id
	fstev = sj.application.args[0]
	seed = sj.application.args[1]
	data = str(idjob) + '\t' + str(fstev) + '\t' + str(seed)
	outfile.writelines( data + '\n' )
	
outfile.close()


