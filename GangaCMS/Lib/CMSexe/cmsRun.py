################################################################################
# Ganga Project. http://cern.ch/ganga                                          #
# cmsRun : Andres Osorio                                                       #
#                                                                              #
################################################################################
#__author__   = 'Andres Osorio'
#__date__     = 'February 2009'
#__revision__ = 0.1
"""
CMSSW application that runs cmsRun on a configuration file
"""

#... From Ganga
from Ganga.GPIDev.Adapters.IApplication import IApplication
from Ganga.GPIDev.Adapters.IRuntimeHandler import IRuntimeHandler
from Ganga.GPIDev.Schema import FileItem, Schema, SimpleItem, Version
from Ganga.GPIDev.Lib.File import File
from Ganga.Utility.Config import makeConfig, getConfig, ConfigError
from Ganga.Utility.root import getrootsys,getpythonhome

import Ganga.Utility.logging

import sys,os

scratch = os.environ.get("HOME") + '/scratch0'
vocmssw = os.environ.get("VO_CMS_SW_DIR")

if vocmssw == None:
    vocmssw = '/afs/cern.ch/cms/sw'

dbsPath = '/afs/cern.ch/cms/sw/slc4_ia32_gcc345/cms/dbs-client/DBS_2_0_6/lib/DBSAPI'

cmsconfig = makeConfig('CMSSW',"Options for CMSSW application")
cmsconfig.addOption('arch','slc5_amd64_gcc434','Architecture of CMSSW')
cmsconfig.addOption('cmsswdir',vocmssw,'Default location of CMSSW at LXPLUS')
cmsconfig.addOption('version','CMSSW_3_8_1','Version of CMSSW')
cmsconfig.addOption('dataOutput',os.environ['HOME']+'/scratch0','The place where OutputData should go')
cmsconfig.addOption('dataTwiki','','Repository of data sets')
cmsconfig.addOption('workArea',os.environ['HOME'],'The top directory where user creates its CMSSW working area')
cmsconfig.addOption('dbsPath',dbsPath,'Path to dbsCommandLine.py script')
cmsconfig.addOption('dbsCommand','dbsCommandLine.py','The dbs-client command')
                    
cafconfig = makeConfig('CMSCAF',"Options for CMSCAF batch system")
cafconfig.addOption('copyCmd','rfcp','The copy command to be used in the CAF batch system')
cafconfig.addOption('mkdirCmd','rfmkdir','The make dir command to be used in the CAF batch system')

crabconfig = makeConfig('CRAB', "parameters of the simple Crab backend")
crabconfig.addOption('CrabEnable', False, 'Enable Crab backend or not')
crabconfig.addOption('remove_workdir', False, 'remove automatically the local working directory when the job completed')
crabconfig.addOption('version', '2_5_0', 'CRAB version')

cmslcgconfig = makeConfig('CMSLCG',"Options for CMS-LCG system")
cmslcgconfig.addOption('copyCmd','srmcp','The copy command to be used in the Grid')
cmslcgconfig.addOption('mkdirCmd','srmmkdir','The make dir command to be used in the Grid')

srmcpopts = '\"-srm_protocol_version=2 -use_urlcopy_script=true -urlcopy=${SRM_PATH}/sbin/url-copy.sh\"'
cmslcgconfig.addOption('copyCmdOpts', srmcpopts,'Options to be used with the copy command')

logger = Ganga.Utility.logging.getLogger()

#.................................................................................
# ... Define the Application
#.................................................................................

class cmsRun(IApplication):
    """
    CMSSW application: cmsRun
    cmsRun executable takes a python configuration file
    """

    comments=[]
    comments.append('A File object specifying the configuration file to execute when cmsRun starts')
    comments.append('The version of CMSSW to run')
    comments.append('Are user libs needed? default = 0')
    comments.append('Platform the application is configured for (e.g. "slc5_amd64_gcc434")')
    comments.append('List of arguments for the job. Accepted types are numerics and strings')
    
    schemadic={}
    schemadic['cfgfile']=FileItem(defvalue=File(),doc=comments[0])
    schemadic['version']=SimpleItem(defvalue='CMSSW_3_2_5',doc=comments[1])
    schemadic['uselibs']=SimpleItem(defvalue=0,doc=comments[2])
    schemadic['platform']=SimpleItem(defvalue = 'slc5_amd64_gcc434', typelist=['str'], doc=comments[3])
    schemadic['args']=SimpleItem(defvalue=[],typelist=['str','int'],sequence=1,doc=comments[4])

    _schema   = Schema( Version(2,1), schemadic )

    _name     = 'cmsRun'

    _category = 'applications'
    
    _GUIPrefs = [ { 'attribute' : 'cfgfile', 'widget' : 'FileOrString' },
                  { 'attribute' : 'version', 'widget' : 'String' } ]
    
    _GUIAdvancedPrefs = [ { 'attribute' : 'cfgfile', 'widget' : 'FileOrString' },
                          { 'attribute' : 'version', 'widget' : 'String' } ]

    _exportmethods = ['add_cfg_XOption','print_cfg_XOptions','add_cfg_Parameter']
    
    mylibsname           = 'mylibs.tgz'
    flat_cfg_filename    = 'job_cfg.py'
    cfgfilename          = ''
    usermodules          = ''
    cmsswroot            = ''
    user_release_area    = ''
    extraopts            = []
    cfg_parameters       = []
    cfg_parameters_type  = []
    

    def __init__(self):
        super(cmsRun,self).__init__()

    def configure(self,master_appconfig):
        """
        The configure method configures the application. Here, the application
        handler simply flattens the configuration file.
        """
        #.....
        logger.debug('starting cmsRun::configure()')
        
        job=self.getJobObject()
        
        #print "cmsRun::configure", job.id, self.args
        #print "cmsRun::configure", job.id, job.inputdir
        
        self.cfgfilename = job.inputdir + self.flat_cfg_filename
        
        res = os.path.isfile( self.cfgfilename )
        if res == True :
            cmd = 'rm ' + self.cfgfilename
            os.system( cmd )

        cmd = 'cp ' + self.cfgfile.name + ' ' + self.cfgfilename
        os.system( cmd )
            
        if job.inputdata and job.inputdata.type != 'pset':
            logger.debug('cmsRun append inputdata to end of new config file')
            status = self.introduce_dataset( job.inputdata )
            
        if len ( self.extraopts ) > 0:
            logger.debug('cmsRun append extra options to end of new config file')
            status = self.introduce_extraopts( )
            
        if len ( self.cfg_parameters ) > 0:
            logger.debug('cmsRun append parameters to end of new config file')
            status = self.introduce_parameters( )

        ### create flat cfg file:
        
        self.flatcfgfile = File ( name = self.cfgfilename )
        self.flatcfgfile.subdir = self.version
            
        return (None,None)
        
    def master_configure(self):

        logger.debug('starting cmsRun::master_configure() ')

        if self.platform == '':
            self.platform = cmsconfig['arch']
        
        self.cmsswroot = cmsconfig['cmsswdir']
        self.user_release_area = cmsconfig['workArea']
        self.usermodules = self.user_release_area + '/' + self.version + '/' + self.mylibsname
        
        job=self.getJobObject()
        
        #.....
        if self.uselibs == 1:
            # ... pack shared libraries found in release area
            cmd  = 'cd ' + self.user_release_area + '/' + self.version + ';'
            cmd += 'tar czhf ' + self.mylibsname + ' lib/ python/'
            os.system( cmd )
            logger.debug(self.mylibsname + ' created in ' +  self.user_release_area + '/' + self.version )
        else:
            logger.debug( 'user libraries will not be send with job' )

        #.....
        if self.cfgfile.name != '':
            fullpath = self.cfgfile.name.split('/')
            last = len(fullpath)
            self.cfgfilename = fullpath[last-1]
            
        #.....
        if self.uselibs == 1:
            usermodules = File( name=self.usermodules , subdir=self.version )
            job.inputsandbox.append( usermodules )
            logger.debug('cmsRun usermodules added to sandbox')

        #.....
        if job.outputdata:
            logger.debug('cmsRun process outputdata')

        return (0,None)
        
    #... methods for interactive manipulation of CMSSW modules
    
    def build(self):
        print 'Building CMSSW module'
        
    def scram(self):
        """Execute the script that sets the environment for cmsRun"""
        CMSSWscript.CMSSWscript(self.version)

    #... methods for modification of the configuration file

    def introduce_dataset(self, dataset ):
        logger.debug("append to configuration file a given data set")

        #--------------------------------------------------------------

        tmpfile = open( self.cfgfilename, 'a' )

        line  = ''
        line  = '\n#... CMSDataset \n\n'
        line += 'readFiles = cms.untracked.vstring() \n'
        line += 'secFiles = cms.untracked.vstring() \n'
        line += 'process.source = cms.Source (\"' + dataset.type + '\",fileNames = readFiles, secondaryFileNames = secFiles) \n \n'
        
        #--------------------------------------------------------------
        # primary dataset
        line += 'readFiles.extend( [ \n'
        tmpfile.writelines( line )
        
        maxfiles = len(dataset.names)
        nf = 0
        for file in dataset.names:
            tmpfile.writelines( '\'' + file + '\'' )
            nf+=1
            if nf != maxfiles:
                tmpfile.writelines( ',\n' )
            else:
                tmpfile.writelines( ' ] ) \n' )
        
        #--------------------------------------------------------------
        # secondary dataset
        if len(dataset.secondary) < 1:
            return 1
        
        line  = ''
        line += '\n#... Secondary CMSDataset \n\n'
        line += 'secFiles.extend( [ \n'
        tmpfile.writelines( line )
        
        maxfiles = len(dataset.secondary)
        nf = 0
        for file in dataset.secondary:
            tmpfile.writelines( '\'' + file + '\'' )
            nf+=1
            if nf != maxfiles:
                tmpfile.writelines( ',\n' )
            else:
                tmpfile.writelines( ' ] ) \n' )
                
        #--------------------------------------------------------------
        
        tmpfile.close()
            
        return 1

    def introduce_extraopts(self):
        logger.debug("append to configuration file some user defined extra options")

        #--------------------------------------------------------------
        
        tmpfile = open( self.cfgfilename,'a')

        line  = ''
        line  = '\n#... User extra options \n\n'
        
        for opt in self.extraopts:
            line += opt + ' \n'

        tmpfile.writelines( line )
        
        #--------------------------------------------------------------
        tmpfile.close()

        return 1

    def introduce_parameters(self):
        logger.debug("append to configuration file some user defined parameter and its value")
        
        #--------------------------------------------------------------
        
        #...check first that for each parameter there is an arguments:
        #print self.cfg_parameters
        if len( self.cfg_parameters ) != len ( self.args ):
            logger.info("Parameter-Argument mistmatch: will not introduce parameters")
            return 0

        tmpfile = open( self.cfgfilename ,'a')

        line  = ''
        line  = '\n#... User extra parameters \n\n'
        
        k=0
        for opt in self.cfg_parameters:
            if isinstance( self.args[k], int ):
                line += opt + ' = ' + self.cfg_parameters_type[k] + '(' + str(self.args[k]) + ')' + ' \n'
            else:
                line += opt + ' = ' + self.cfg_parameters_type[k] + '(\'' + str(self.args[k]) + '\')' + ' \n'

            k=k+1
            
        tmpfile.writelines( line )
            
        #--------------------------------------------------------------
        tmpfile.close()

        return 1
    
    def add_cfg_XOption(self, aoption):
        self.extraopts.append( aoption )

    def print_cfg_XOptions(self):
        for i in self.extraopts:
            line = i + '\n'
            logger.info(line)

    def add_cfg_Parameter(self, aparam, atype):
        """
        Add a parameter string to the configuration file. The value given to this parameter should go in the Argument list.
        Example:
        """
        logger.debug('append to configuration file some user defined parameters: will require argument')
        self.cfg_parameters.append( aparam )
        self.cfg_parameters_type.append( atype )


