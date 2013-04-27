################################################################################
#     Ganga Project. http://cern.ch/ganga                                      #
#     cmsRunLocal                                                              #      
#                                                                              #   
################################################################################
#__author__   = 'Andres Osorio'
#__date__     = 'February 2009'
#__revision__ = 0.1

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

import sys,os,os.path

#.................................................................................
#
# ... Define the Runtime Handlers
#
#.................................................................................

class cmsRunLocalRuntimeHandler(IRuntimeHandler):
  """ Runtime Handler for Local system """

  sandbox = []
  outsbox = []

  def __init__(self):
    config=Ganga.Utility.Config.getConfig('CMSSW') 
    
  def prepare(self,app,appsubconfig,appmasterconfig,jobmasterconfig):
    logger.debug("prepare method for Local job submission")

    job = app._getParent() # Returns job or subjob object
    logger.debug("cmsRunLocalRTHandler prepare called, %s", job.id )

    jobsandbox = []
    jobsandbox = self.sandbox[:]
    jobsandbox.append ( app.flatcfgfile )
    
    script  = self.create_runscript( app )

    return StandardJobConfig(FileBuffer('myscript',script,executable=1),inputbox=jobsandbox,args=[],outputbox=unique(self.outsbox))
    
  def master_prepare(self, app, appconfig):
    logger.debug("master_prepare method for Local job submission")

    job = app._getParent() # Returns job or subjob object

    self.sandbox += job.inputsandbox
    self.outsbox += job.outputsandbox    
    
    return StandardJobConfig( '', inputbox = self.sandbox, args=[])
  
  def jobid_as_string(self):
    return 'jobid_as_string'

  def create_runscript(self, app ):
    logger.debug("create runscript method for Local job submission")
    
    job = app.getJobObject()
    config = Ganga.Utility.Config.getConfig('CMSSW')
    logger.debug("Entering the master_prepare of Local Runtimehandler") 
    
    version     = app.version
    theApp      = app._name
    cmsswroot   = app.cmsswroot
    scramarch   = app.platform
    cfgfilename = app.flat_cfg_filename
    usermodules = app.mylibsname

    #--------------------------------------------------------------
    #. generate shell script
    #.    
    script='#!/bin/csh\n'
    script+='#..................................................\n'
    script+='#.. Andres Osorio - aosorio@uniandes.edu.co        \n'
    script+='setenv VO_CMS_SW_DIR ' + cmsswroot +              '\n'
    script+='setenv SCRAM_ARCH ' + scramarch +                 '\n'
    script+='source ${VO_CMS_SW_DIR}/cmsset_default.csh' +     '\n'
    script+='scram project CMSSW ' + version +                 '\n'
    script+='cd '+ version +                                   '\n'
    script+='eval `scram runtime -csh`' +                      '\n' 
    script+='#..................................................\n'
    script+='# ...... untar users module .......................\n'
    
    #--------------------------------------------------------------
    #.
    if app.uselibs == 1:
      script+='tar xzvf ' + usermodules +                      '\n'
    else:
      script+='# user libs not selected'

    #--------------------------------------------------------------
    #.
    script+='# ...... run cmsRun on given cfg.py file ..........\n'
    script+=theApp + ' ' + cfgfilename +                       '\n'
    #--------------------------------------------------------------
    #.
    script+='# ...... get results ..............................\n'
    if len( self.outsbox ) != 0 :
      for outfile in self.outsbox :
        script+='mv -v ' + outfile + ' ../' +                  '\n'
    #--------------------------------------------------------------
    #.
    script+='# ...... clean the area ...........................\n'

    #--------------------------------------------------------------
    
    return script


allHandlers.add('cmsRun','Local', cmsRunLocalRuntimeHandler)
logger.debug('added cmsRun Local backend')



#.................................................................................


