################################################################################
#     Ganga Project. http://cern.ch/ganga                                      # 
#     cmsRunLCG                                                                #
#                                                                              #
################################################################################
#__author__   = 'Andres Osorio'
#__date__     = 'July 2009'
#__revision__ = 0.1

import sys, os, os.path

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
# ... Define the Runtime Handler
#
#.................................................................................

class cmsRunLCGRuntimeHandler(IRuntimeHandler):
  """ Runtime Handler for LCG batch system """

  sandbox = []
  outsbox = []
  data2se = []
  data2se_subdir = '.'

  cmsconfig = Ganga.Utility.Config.getConfig('CMSSW')
  cafconfig = Ganga.Utility.Config.getConfig('CMSCAF')
  lcgconfig = Ganga.Utility.Config.getConfig('CMSLCG')
  
  def __init__(self):
    logger.debug("ready for LCG job submission")
    
  def prepare(self,app,appsubconfig,appmasterconfig,jobmasterconfig):
    from Ganga.Lib.LCG import LCGJobConfig
    
    logger.debug("prepare method for LCG job submission")
    
    job = app._getParent() # Returns job or subjob object
    logger.debug("cmsRunLCGRTHandler prepare called, %s", job.id )
    
    jobsandbox = []
    jobsandbox = self.sandbox[:]
    jobsandbox.append ( app.flatcfgfile )
    
    script  = self.create_runscript( app )
    
    return LCGJobConfig( FileBuffer('myscript',script,executable=1), inputbox=jobsandbox, args=[], outputbox=unique(self.outsbox) )
    
  def master_prepare(self, app, appconfig):
    logger.debug("master_prepare method for LCG job submission")

    job = app._getParent() # Returns job or subjob object

    self.sandbox += job.inputsandbox
    self.outsbox += job.outputsandbox    

    if job.outputdata != None:
      self.data2se += job.outputdata.names
      self.data2se_subdir = job.outputdata.subdir
      
    return StandardJobConfig( '', inputbox = self.sandbox, args=[] )
  
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
    logger.debug("create runscript method for LCG job submission")
    
    job = app.getJobObject()
    logger.debug("Entering the master_prepare of LCG Runtimehandler") 
    
    version     = app.version
    theApp      = app._name
    cmsswroot   = app.cmsswroot
    scramarch   = app.platform
    cfgfilename = app.flat_cfg_filename
    usermodules = app.mylibsname
    jstr        = self.jobid_as_string(app)
    joboutdir   = self.cmsconfig['dataOutput']
    
    #-----------------------------------------------------------------
    #. generate shell script
    #.    
    script='#!/bin/csh\n'
    script+='#..................................................\n'
    script+='#.. Andres Osorio - aosorio@uniandes.edu.co        \n'
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
    #.
    script+='# ...... get results to SE joboutputdir ..............\n'

    if len( self.data2se ) != 0:
      script+='\n'
      script+='set CP=###COPY###                                       \n'
      script+='set MKDIR=###MKDIR###                                   \n'
      script+='set CPOPT=###CPOPT###                                   \n'
      script+='set SEHEAD=###SEHEAD###                                 \n'
      script+='\n'
      
      if self.data2se_subdir == '.':
        script+='set JOBOUTPUTDIR=###JOBOUTDIR###/###JOBID###/outputdata \n'
        script+='$MKDIR ${SEHEAD}' + joboutdir + '/' + str(job.master.id) + ' \n'
        script+='$MKDIR ${SEHEAD}' + joboutdir + '/' + jstr + ' \n'
        script+='$MKDIR ${SEHEAD}${JOBOUTPUTDIR} \n'
        script+='# ....................................................\n'

      else:
        script+='set JOBOUTPUTDIR=###JOBOUTDIR### \n'
        script+='$MKDIR ${SEHEAD}${JOBOUTPUTDIR} \n'
        script+='# ....................................................\n'

      script+='\n'
      script+='\n'
      script+='foreach file ( '
      
      for outfile in self.data2se :
        script+=str(outfile) + ' '
        
      script+=') \n'
      script+='   if ( -f $file ) then \n'
      script+='      ${CP} ${CPOPT} file:///${PWD}/${file} ${SEHEAD}${JOBOUTPUTDIR}/${file} \n'
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

    LCGconfig = Ganga.Utility.Config.getConfig('LCG')
    selem = LCGconfig['DefaultSE']

    #... temporary fix=
    if selem == 'moboro.uniandes.edu.co':
      sehead = 'srm://' + selem + ':8446'
    else:
      sehead = 'srm://' + selem
      
    if self.data2se_subdir != '.':
      joboutdir = self.data2se_subdir
      
    script=script.replace('###JOBOUTDIR###',joboutdir)
    script=script.replace('###JOBID###',jstr)
            
    copy_cmd    = self.lcgconfig['copyCmd']
    mkdir_cmd   = self.lcgconfig['mkdirCmd']
    cp_opts     = self.lcgconfig['copyCmdOpts']
        
    script=script.replace('###COPY###',copy_cmd)
    script=script.replace('###MKDIR###',mkdir_cmd)
    script=script.replace('###CPOPT###',cp_opts)
    script=script.replace('###SEHEAD###', sehead)
    
    return script


allHandlers.add('cmsRun','LCG', cmsRunLCGRuntimeHandler)
logger.debug('added cmsRun LCG backend')


#.................................................................................


