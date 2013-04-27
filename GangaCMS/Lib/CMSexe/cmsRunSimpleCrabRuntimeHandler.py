################################################################################
#     Ganga Project. http://cern.ch/ganga                                      #
#     cmsRunSimpleCrab                                                         #      
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
from GangaCMS.Lib.CRAB.ConfigFile import *

crabconf = Ganga.Utility.Config.getConfig('CRAB')
gridconf = Ganga.Utility.Config.getConfig('LCG')

#...
import sys,os,os.path

#.................................................................................
#
# ... Define the Runtime Handlers
#
#.................................................................................

class cmsRunSimpleCrabRuntimeHandler(IRuntimeHandler):
  """ Runtime Handler for SimpleCrab system """

  sandbox  = []
  outsbox  = []
  datasets = []
  
  def __init__(self):
    config=Ganga.Utility.Config.getConfig('CMSSW') 
    
  def prepare(self,app,appsubconfig,appmasterconfig,jobmasterconfig):
    logger.debug("prepare method for SimpleCrab job submission")

    job = app._getParent() # Returns job or subjob object
    logger.debug("cmsRunSimpleCrabRTHandler prepare called, %s", job.id )

    jobsandbox = []
    jobsandbox = self.sandbox[:]
    
    script  = self.create_runscript( app )

    crabcfg = self.create_crabcfg( app)
    jobsandbox.append ( crabcfg )

    return StandardJobConfig(FileBuffer('crabwrapper',script,executable=1),inputbox=jobsandbox,args=[],outputbox=unique(self.outsbox))
    
  def master_prepare(self, app, appconfig):
    logger.debug("master_prepare method for SimpleCrab job submission")

    job = app._getParent() # Returns job or subjob object

    self.sandbox  += job.inputsandbox
    self.outsbox  += job.outputsandbox    

    if len( job.inputdata.names ) != 0 :
      self.datasets += job.inputdata.names

    return StandardJobConfig( '', inputbox = self.sandbox, args=[])
  
  def jobid_as_string(self):
    return 'jobid_as_string'

  def create_crabcfg(self, app ):

    job = app._getParent()
    pathto   = job.outputdir
    filename = pathto + '/crab.cfg'
    
    ff = ConfigFile(filename)
    
    ff.append('CRAB' ,'jobtype='   + str(job.backend.apptype) )
    ff.append('CRAB' ,'scheduler=' + str(job.backend.scheduler) )
    ff.append('CRAB' ,'server_name='    + str(job.backend.server) )

    outputdata = job.outputdata.names

    infiles  = ','.join( self.datasets )
    outfiles = ','.join( outputdata )
    
    ff.append('CMSSW','datasetpath=' + infiles )
    ff.append('CMSSW','pset=' + app.cfgfile.name)
    ff.append('CMSSW' ,'output_file=' + outfiles )
    ff.append('CMSSW' ,'events_per_job=' + str(job.splitter.evtsperjob) )
    ff.append('CMSSW' ,'number_of_jobs=' + str(job.splitter.njobs) )
    
    ff.append('USER' , 'return_data='     + str(job.outputdata.return_data) )
    ff.append('USER' , 'copy_data='       + str(job.outputdata.copy_data) )
    ff.append('USER' , 'storage_element=' +     job.outputdata.storage_element )
    ff.append('USER' , 'user_remote_dir=' +     job.outputdata.user_remote_dir)
    ff.append('USER' , 'publish_data='    + str(job.outputdata.publish_data) )
    ff.append('USER' , 'storage_path='    +     job.outputdata.storage_path )
        
    ff.write()
    
    cfgfile = File( name = filename )

    return cfgfile
    

  def create_runscript(self, app ):

    logger.debug("Entering the master_prepare of SimpleCrab Runtimehandler") 

    crabver   = crabconf['version']
    crabenv   = '/afs/cern.ch/cms/ccs/wm/scripts/Crab/CRAB_'+ crabver +'/crab.csh'

    version   = app.version
    cmsswroot = app.cmsswroot
    scramarch = app.platform
    userarea  = app.user_release_area

    job = app._getParent()
    workdir   = job.outputdir
    
    #--------------------------------------------------------------
    #. generate shell script
    #.    
    script ='#!/bin/csh\n'
    script+='#..................................................\n'
    script+='#.. Andres Osorio - aosorio@uniandes.edu.co        \n'
    script+='#..................................................\n'
    script+='#...\n'
    script+='echo \"${X509_CERT_DIR}:${EDG_WL_LOCATION}:${X509_USER_PROXY}\" \n'
    script+='#...\n'
    #.
    #. CMSSW ENV
    script+='setenv VO_CMS_SW_DIR ' + cmsswroot +              '\n'
    script+='setenv SCRAM_ARCH ' + scramarch +                 '\n'
    script+='source ${VO_CMS_SW_DIR}/cmsset_default.csh' +     '\n'
    script+='cd '+ userarea + '/' + version +                  '\n'
    script+='eval `scram runtime -csh`' +                      '\n' 
    script+='#...\n'
    #.
    #. CRAB ENV
    script+='source ' + crabenv + ' \n'
    #. 
    script+='echo "Environment ready"  \n'
    script+='#...\n'
    #--------------------------------------------------------------
    #.
    script+='#... run Crab on the given crab.cfg file ......\n'
    script+='cd ' + workdir + ' \n'
    script+='crab -create \n'
    script+='crab -submit \n'
    script+='#...\n'
    #--------------------------------------------------------------
    #.
    script+='#... get results ..............................\n'
    #--------------------------------------------------------------
    #.
    script+='#... clean the area ...........................\n'
    
    #--------------------------------------------------------------
    
    return script


allHandlers.add('cmsRun','SimpleCrab', cmsRunSimpleCrabRuntimeHandler)
logger.debug('added cmsRun SimpleCrab backend')



#.................................................................................


