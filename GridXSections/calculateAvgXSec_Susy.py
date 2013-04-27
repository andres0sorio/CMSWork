#!/usr/bin/python

import os,sys
import string
from time import time
from optparse import OptionParser

#-------------------------------------------------------------------------
#-------------------------------------------------------------------------
parser = OptionParser()
parser.add_option("-m", type = "string", dest="points",
                help="max number of points", metavar="POINTS" )

parser.add_option("-o", type = "string", dest="variation",
                help="variation number", metavar="VARIATION" )

(options, args) = parser.parse_args()

if options.points is None:
      parser.error("please give the number of max points")

if options.variation is None:
      parser.error("please give the variation id")

#-------------------------------------------------------------------------
#-------------------------------------------------------------------------

varId = options.variation

fileopt = 'susy_var' + varId

slha_file = 'SUSY_LM0_var' + varId + '_sftsht.slha'

process = 'q qbar\' -> ~chi_1+ ~chi_20'

logfile = open('pythia8.log','w')

filename = 'pythia8_xsecs_'+ fileopt + '.dat'

outfile = open(filename,'w')

xsec = 0.0
xsecErr = 0.0
points = int ( options.points )

for pts in range(0,points):
      
      current_time = str( time() ).split('.')
      timestamp = ''.join( current_time )[4:]

      rndseed = int ( timestamp )
      
      pythia_options = []
      pythia_options.append(str(rndseed))
      pythia_options.append(str(slha_file))
      
      cmd_pythia = './run_susy ' + (' ').join(pythia_options)

      print cmd_pythia

      pythia = os.popen(cmd_pythia,'r').readlines()
      
      for line in pythia:
            if line.find(process) >= 0:
                  xsecinfo = line.split()
                  xsec = xsecinfo[-3]
                  xsecErr = xsecinfo[-2]
                  #print len(xsecinfo)
                  if len(xsecinfo) > 10:
                        output = str(pts) + '\t' + str(rndseed) + '\t' + str(xsec) + '\t' + str(xsecErr) + '\n'
                        outfile.writelines( output )
            else:
                  logfile.writelines(line)
                  


logfile.close()
outfile.close()
#-------------------------------------------------------------------------


#-------------------------------------------------------------------------
