###########################################################################
# CMSSWscript.py
# Purpose: Write a script setting up the cmssw release area and environment
#          for cmsRun
# Andres Osorio
###########################################################################
"""
File: CMSSWscript.py
Purpose: Write a script setting up the cmssw release area and environment 
         for cmsRun
"""
#__author__   = 'Andres Osorio'
#__date__     = 'February 2009'
#__revision__ = 0.1

#................	
#... just for testing -- boostrap.py provides the following at runtime:
from Ganga.Utility.Config import Config, makeConfig
shellconfig = makeConfig( "Shell", "configuration parameters for internal Shell utility.")
comment = 'list of env variables not inherited in Shell environment'
shellconfig.addOption('IgnoredVars',['_','SHVL','PWD'], comment)
#................

from Ganga.GPI import *
from Ganga.Utility.Shell import Shell
import Ganga.Utility.logging

import os
import sys
import time
import types
import warnings
import tempfile
import shutil

logger = Ganga.Utility.logging.getLogger()

def CMSSWscript(version='CMSSW_2_2_4'):
   """Function to execute a script that sets a CMSSW release area
   arguments:
      version - String [default 'CMSSW_2_2_4']
   """
   
   cmsswroot = os.getenv('VO_CMS_SW_DIR')
   scramarch  = os.getenv('SCRAM_ARCH')

   if cmsswroot and scramarch :
      print 'CMSSW environment found'
   else:
      cmsswroot = '/opt/CMSSW/local'
      scramarch = 'slc4_ia32_gcc345'
      print 'CMSSW environment set to: ', cmsswroot, ' ', scramarch
      
   warnings.filterwarnings('ignore', 'tempnam', RuntimeWarning)
   tmppath   = tempfile.mktemp()
   tmppath='/tmp/gangacms/'
  
   #. generate shell script
   script='#!/bin/csh\n'
   script+='#.................................................\n'
   script+='cd ' + tmppath + '\n'
   script+='setenv VO_CMS_SW_DIR ' + cmsswroot + '\n'
   script+='setenv SCRAM_ARCH ' + scramarch + '\n'
   script+='source ${VO_CMS_SW_DIR}/cmsset_default.csh' + '\n'
   logger.debug('Will execute the command: ', cmd)
   script+='scram project CMSSW ' + version + '\n'
   script+='cd '+ version + '\n'
   script+='eval `scram runtime -csh`' + '\n' 
   script+='#.................................................\n'
   logger.debug('The full script for execution:\n'+script)
   print script
   
   #.. write file
   try:
      fn = os.path.join(tmppath, 'cmsswenv.csh')
      file1 = open(fn, 'w')
   except Exception, e:
      logger.error("Can not create temporary file %s", fn)
      return
   else:
      try:
         file1.write(script)
      finally:
         file1.close()

   #... make file executable
   os.chmod(fn, 0777)
   
   logger.debug('Executing cmsenv.csh script')
   print 'Executing cmsenv.csh script'
   
   #.... run it
   shell = Shell()
   rc=shell.system(fn)
   
   #if os.path.exists(tmppath) :
   #   shutil.rmtree(tmppath)
      
   return True

