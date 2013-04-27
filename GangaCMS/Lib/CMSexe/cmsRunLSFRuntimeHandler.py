################################################################################
#     Ganga Project. http://cern.ch/ganga                                      # 
#     cmsRunLSF                                                                #
#                                                                              #
################################################################################
#__author__   = 'Andres Osorio'
#__date__     = 'February 2009'
#__revision__ = 0.1

import sys,os,os.path

#... From Ganga
from Ganga.Core.exceptions import ApplicationConfigurationError
from Ganga.GPIDev.Base import GangaObject
from Ganga.GPIDev.Schema import *
from Ganga.GPIDev.Adapters.IRuntimeHandler import IRuntimeHandler
from Ganga.GPIDev.Lib.File import *
from Ganga.GPIDev.Lib.File import File
from Ganga.Utility.util import unique
from Ganga.Utility.files import expandfilename
from Ganga.GPIDev.Adapters.StandardJobConfig import StandardJobConfig
from Ganga.GPIDev.Adapters.ApplicationRuntimeHandlers import allHandlers

import Ganga.Utility.Config 
import Ganga.Utility.logging

logger = Ganga.Utility.logging.getLogger()

#... From GangaCMS
from GangaCMS.Lib.CMSDataset import *

#.................................................................................
#
# ... Define the LSF Runtime Handler
#
#.................................................................................

class cmsRunLSFRuntimeHandler(IRuntimeHandler):
  """ Runtime Handler for LSF batch system """

  sandbox = []
  outsbox = []
  data2se = []
  data2se_subdir = '.'
  
  cmsconfig = Ganga.Utility.Config.getConfig('CMSSW')
  cafconfig = Ganga.Utility.Config.getConfig('CMSCAF')
  
  def __init__(self):
    logger.debug("ready for LSF job submission")
    
  def prepare(self,app,appsubconfig,appmasterconfig,jobmasterconfig):

    logger.debug("prepare method for LSF job submission")

    job = app._getParent() # Returns job or subjob object
    logger.debug("cmsRunLSFRTHandler prepare called, %s", job.id )
    
    jobsandbox = []
    jobsandbox = self.sandbox[:]
    jobsandbox.append ( app.flatcfgfile )
    
    script  = self.create_runscript( app )

    return StandardJobConfig(FileBuffer('myscript',script,executable=1),inputbox=jobsandbox,args=[],outputbox=unique(self.outsbox))
    
  def master_prepare(self, app, appconfig):
    logger.debug("master_prepare method for LSF job submission")

    job = app._getParent() # Returns job or subjob object

    self.sandbox += job.inputsandbox
    self.outsbox += job.outputsandbox    

    if job.outputdata != None:
      self.data2se += job.outputdata.names
      self.data2se_subdir = job.outputdata.subdir
      
    return StandardJobConfig( '', inputbox = self.sandbox, args=[])
  
  def jobid_as_string(self,app):
      import os.path
      job=app.getJobObject()
      jstr=''
      # test is this is a subjobs or not
      if job.master: # it's a subjob
          jstr=str(job.master.id)+os.sep+str(job.id)
      else:
          jstr=str(job.id)
      return jstr

  def create_runscript(self, app ):
    logger.debug("create runscript method for LSF job submission")
    
    job = app.getJobObject()
    logger.debug("Entering the master_prepare of LSF Runtimehandler") 
    
    version     = app.version
    theApp      = app._name
    cmsswroot   = app.cmsswroot
    scramarch   = app.platform
    cfgfilename = app.flat_cfg_filename
    usermodules = app.mylibsname
    copy_cmd    = self.cafconfig['copyCmd']
    mkdir_cmd   = self.cafconfig['mkdirCmd']
    joboutdir   = self.cmsconfig['dataOutput']
    jstr        = self.jobid_as_string(app)
    
    #-----------------------------------------------------------------
    #. generate shell script
    #.    
    script='#!/bin/csh\n'
    script+='#..................................................\n'
    script+='#.. Andres Osorio - aosorio@uniandes.edu.co        \n'
    #script+='source /afs/cern.ch/cms/caf/setup.csh              \n'
    script+='setenv VO_CMS_SW_DIR ' + cmsswroot +              '\n'
    script+='setenv SCRAM_ARCH ' + scramarch +                 '\n'
    script+='source ${VO_CMS_SW_DIR}/cmsset_default.csh' +     '\n'
    script+='scram project CMSSW ' + version +                 '\n'
    script+='cd '+ version +                                   '\n'
    script+='eval `scram runtime -csh`' +                      '\n' 
    script+='#..................................................\n'
    script+='# ...... untar users module .......................\n'
    #-----------------------------------------------------------------
    #.
    if app.uselibs == 1:
      script+='tar xzvf ' + usermodules +                      '\n'
    else:
      script+='# user libs not selected'
    #-----------------------------------------------------------------
    #.
    script+='# ...... run cmsRun on given cfg.py file ..........\n'
    script+=theApp + ' ' + cfgfilename +                       '\n'
    #-----------------------------------------------------------------
    #.
    script+='# ...... get results ..............................\n'
    if len( self.outsbox ) != 0 :
      for outfile in self.outsbox :
        script+='mv -v ' + outfile + ' ../' +                  '\n'
    #-----------------------------------------------------------------
    #.
    script+='# ...... get results to SE joboutputdir ..............\n'

    if len( self.data2se ) != 0:
      script+='\n'
      script+='set CP=###COPY###                                       \n'
      script+='set MKDIR=###MKDIR###                                   \n'
      script+='\n'
      
      if self.data2se_subdir == '.':
        script+='set JOBOUTPUTDIR=###JOBOUTDIR###/###JOBID###/outputdata \n'
        script+='# ....................................................\n'

      else:
        script+='set JOBOUTPUTDIR=###JOBOUTDIR### \n'
        script+='# ....................................................\n'

      script+='$MKDIR -p $JOBOUTPUTDIR \n'

      script+='\n'
      script+='\n'
      script+='foreach file ( '

      for outfile in self.data2se :
        script+=str(outfile) + ' '
        
      script+=') \n'
      script+='   if ( -f $file ) then \n'
      script+='      ${CP} ${file} ${JOBOUTPUTDIR}/${file} \n'
      script+='      if ( $? != 0 ) then \n'
      script+='          echo \"WARNING: Could not copy file ${file} to ${JOBOUTPUTDIR}\" \n'
      script+='      endif \n'
      script+='   endif \n'
      script+='end \n'

    #-----------------------------------------------------------------
    #.

    script+='# ...... clean the area ............................\n'

    #.
    #. end of script    
    #-----------------------------------------------------------------

    if self.data2se_subdir != '.':
      joboutdir = self.data2se_subdir

    script=script.replace('###JOBOUTDIR###',joboutdir)
    script=script.replace('###JOBID###',jstr)
    script=script.replace('###COPY###',copy_cmd)
    script=script.replace('###MKDIR###',mkdir_cmd)
    
    return script


allHandlers.add('cmsRun','LSF', cmsRunLSFRuntimeHandler)
allHandlers.add('cmsRun','PBS', cmsRunLSFRuntimeHandler)

logger.debug('added cmsRun LSF backend')


#.................................................................................


