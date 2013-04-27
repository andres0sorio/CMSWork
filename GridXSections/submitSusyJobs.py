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

def get_script( id, exe, args):


      fileopt = 'susy_var' + str(args)
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
      script += 'InputSandbox = {\"sandbox.tgz\"};' + '\n' 
      script += 'OutputSandboxBaseDestURI=\"gsiftp://localhost\";' + '\n'
      return script

#-------------------------------------------------------------------------

script_name = options.executable
inputsandbox = options.sandbox.split(',')
outfile = open ('jobids.log','w')

ce = 'cale.uniandes.edu.co:8443/cream-pbs-uniandes'
jdl_name = 'susyxsec-var.jdl'

cream_submit = 'glite-ce-job-submit -a -r ' + ce + ' ' + jdl_name

x = 0
dx = 1
max_x = 1

#-------------------------------------------------------------------------

id = 0

while x < max_x:

      jdl_script = open(jdl_name,'w')

      slha_file = 'SLHA/SUSY_LM0_var' + str(x) + '_sftsht.slha'

      inputsandbox.append(slha_file)
      sandbox = (' ').join(inputsandbox)
      tar_isb_cmd = 'tar czvf sandbox.tgz ' + sandbox 
      
      loginfo = os.popen(tar_isb_cmd ,'r').readlines()

      print inputsandbox

      script = get_script( id, script_name, x)

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


