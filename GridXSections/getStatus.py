#!/usr/bin/python

import os,sys
import string
from time import time
from optparse import OptionParser

#-------------------------------------------------------------------------
#-------------------------------------------------------------------------
parser = OptionParser()
parser.add_option("-o", type = "string", dest="getoutput",
                help="get output path(yes/no)", metavar="OUTPUT" )

(options, args) = parser.parse_args()

#-------------------------------------------------------------------------

jobids = open('jobids.log','r')

ce = 'cale.uniandes.edu.co:8443/cream-pbs-uniandes'

opt1 = ''
opt2 = ''

if options.getoutput == None:
      opt1 = ' '
else:
      opt1 = ' -L 2 '
      outdir =  options.getoutput
      if not os.path.exists( outdir ):
            os.mkdir( outdir )

cream_status = 'glite-ce-job-status'

get_output = 'uberftp cale.uniandes.edu.co '

#-------------------------------------------------------------------------

id = 0

for job in jobids.readlines():
      
      cream_status_cmd = cream_status + opt1 + job 

      loginfo = os.popen(cream_status_cmd ,'r').readlines()

      outdir = ''

      if options.getoutput == None:
            print loginfo

      if options.getoutput != None:      
            outdir = options.getoutput + '/' + str(id)
            if not os.path.exists( outdir ):
                  os.mkdir( outdir )
      
            for item in loginfo:
                  if item.find('CREAM OSB URI') >= 0:
                        path = item.split()[-1].replace('[','').replace(']','')
                        OSB  = path[29:]
                        OSB_path = OSB.replace('/','\/')
                        get_cmd = '\"get -r ' + OSB_path + '\"'
                        cream_get_cmd = 'cd ' + outdir + '; ' + get_output + get_cmd + '; cd ../../'
                        print cream_get_cmd
                        loginfo = os.popen(cream_get_cmd ,'r').readlines()

      id = id + 1            


 
jobids.close()

#-------------------------------------------------------------------------


