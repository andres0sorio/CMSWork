#!/usr/bin/python

import os,sys
import string
from time import time
from optparse import OptionParser

#-------------------------------------------------------------------------
#-------------------------------------------------------------------------
parser = OptionParser()
parser.add_option("-s", type = "string", dest="sandbox",
                help="input sandbox", metavar="SANDBOX" )

parser.add_option("-x", type = "string", dest="executable",
                help="script name", metavar="SCRIPT" )

(options, args) = parser.parse_args()

if options.sandbox is None:
      parser.error("please give the sandbox")

if options.executable is None:
      parser.error("please give the script name")

#-------------------------------------------------------------------------

def get_script( id, exe, args, sbox):


      fileopt = 'h0_m' + str(args)
      filename = 'pythia8_xsecs_'+ fileopt + '.dat'

      script  = 'JobName = \"AOxsec_' + str(id) + '\";' + '\n'
      script += 'JobType = \"Normal\";' + '\n'
      script += 'Executable = \"' +  str(exe) + '\";' + '\n'
      script += 'Arguments = \"' + str(args) + '\";' + '\n'
      script += 'CPUTime = \"\";' + '\n'
      script += 'StdOutput = \"std.out\";' + '\n'
      script += 'StdError = \"std.err\";' + '\n'
      script += 'Owner = \"aosorio\";' + '\n'
      script += 'OutputSandbox = {\"std.out\",\"std.err\",\"' + filename +'\"};' + '\n'
      script += 'OutputSE = \"\";' + '\n'
      n = 0
      script += 'InputSandbox = {'
      for file in sbox:
            script += '\"' + file + '\"'
            if n < (len(sbox)-1):
                  script += ','
            n = n + 1      
      script += '};' + '\n'
      script += 'OutputSandboxBaseDestURI=\"gsiftp://localhost\";' + '\n'
      return script

#-------------------------------------------------------------------------

script_name = options.executable
inputsandbox = options.sandbox.split(',')
outfile = open ('jobids.log','w')

ce = 'cale.uniandes.edu.co:8443/cream-pbs-uniandes'
jdl_name = 'xsec-var.jdl'

cream_submit = 'glite-ce-job-submit -a -r ' + ce + ' ' + jdl_name

x = 120.0
dx = 5.0
max_x = 130.0

#-------------------------------------------------------------------------

id = 0

while x < max_x:

      jdl_script = open(jdl_name,'w')
      
      script = get_script( id, script_name, x, inputsandbox)

      print script
      
      jdl_script.writelines(script)

      jdl_script.close()

      loginfo = os.popen(cream_submit ,'r').readlines()
      
      
      for line in loginfo:
            print line
            if line.find('https') >= 0:
                  jobid = line
                  outfile.writelines( jobid )
      
      x = x + dx
      id = id + 1
      
outfile.close()

#-------------------------------------------------------------------------


