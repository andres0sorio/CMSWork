#######################################################################
#     CMS Splitters (SplitByFile: based upon LHCb's Gaudi Splitter)   #
#     Andres Osorio                                                   #
#                                                                     #
#######################################################################
#__author__   = 'Andres Osorio'
#__date__     = 'February 2009'
#__revision__ = 0.1

#... From Ganga
from Ganga.GPIDev.Base import GangaObject
from Ganga.Core import ApplicationConfigurationError
from Ganga.GPIDev.Schema import *
from Ganga.GPIDev.Lib.File import  File
from Ganga.GPIDev.Adapters.ISplitter import ISplitter,SplittingError
import Ganga.Utility.logging

logger = Ganga.Utility.logging.getLogger()

#... From GangaCMS
from GangaCMS.Lib.CMSDataset import *

import datetime

######################################################################
#..
#.. SplitByFiles                                                    
#..
######################################################################

class SplitByFiles(ISplitter):
    """Splits a job into sub-jobs by partitioning the input data.
       SplitByFiles can be used to split a job into multiple subjobs, where
       each subjob gets an unique subset of the inputdata files.
    """

    comments=[]
    comments.append('Number of files per subjob')
    comments.append('Maximum number of files to use in a masterjob. A value of "-1" means all files')

    _name = 'SplitByFiles'
    _schema = Schema(Version(1,0),{
        'filesPerJob' : SimpleItem(defvalue=10, doc=comments[0] ),
        'maxFiles'    : SimpleItem(defvalue=-1, doc=comments[1] )  } )
    
    def _splitFiles(self, inputs):
        #split the files
        splitter = _simpleSplitter( self.filesPerJob, self.maxFiles )
        return splitter.split(inputs)
    
    def split(self,job):
        logger.debug("Splitting job")
        if self.filesPerJob < 1:
            logger.error('filesPerJob must be greater than 0.')
            raise SplittingError('filesPerJob < 1 : %d' % self.filesPerJob)
        
        from Ganga.GPIDev.Lib.Job import Job
        
        subjobs=[]
        inputs = CMSDataset()
        inputs.type = job.inputdata.type
        
        if int(self.maxFiles) == -1:
            inputs.names = job.inputdata.names[:]
            logger.debug("Using all %d input files for splitting" % len(inputs.names))
        else:
            inputs.names=job.inputdata.names[:self.maxFiles]
            logger.debug("Only using a maximum of %d inputfiles" %int(self.maxFiles))
            
        datasetlist = self._splitFiles(inputs)

        for dataset in datasetlist:

            j = self.createSubjob(job)
            j.application = job.application
            j.application.uselibs = job.application.uselibs
            j.application.version = job.application.version
            j.application.args    = job.application.args
            j.backend = job.backend
            j.inputdata = dataset
            j.outputsandbox = job.outputsandbox[:]

            #... 
            subjobs.append( j )
            
        return subjobs

#.................................................................................

class _abstractSplitter(object):
    """Abstract baseclass for splitters"""

    def __init__(self,filesPerJob,maxFiles):
        self.filesPerJob = filesPerJob
        self.maxFiles = maxFiles

    def split(self,inputs):
        raise NotImplementedError

#.................................................................................

class _simpleSplitter(_abstractSplitter):

    def split(self,inputs):
        """Just splits the files in the order they came"""

        result = []
        end = 0
        inputs_length = len(inputs.names)

        for i in range(inputs_length // self.filesPerJob):

            start = i * self.filesPerJob
            end = start + self.filesPerJob

            #add a sublist of files
            dataset = CMSDataset()
            dataset.type = inputs.type
            dataset.names = inputs.names[start:end]
            result.append(dataset)

        if end < (inputs_length):
            dataset = CMSDataset()
            dataset.type = inputs.type
            dataset.names = inputs.names[end:]
            result.append(dataset)

        #catch file loss
        result_length = 0
        for r in result:
            result_length += len(r.names)
        if result_length != inputs_length:
            raise SplittingError('Data files have been lost during splitting. Please submit a bug.')
        return result

######################################################################
#..
#.. ArgSplitterX (based upon Ganga's ArgSplitter)                    #
#     Andres Osorio
#..
######################################################################

class ArgSplitterX(ISplitter):

    """
    Reimplementation of Ganga ArgSplitter to have some extra features
    
    This splitter allows the creation of a series of subjobs where
    the only difference between different jobs are their
    arguments.

    """    


    comments=[]
    comments.append('A list of lists of arguments to pass to script')

    _name = "ArgSplitterX"
    _schema = Schema(Version(1,0),{
        'args' : SimpleItem(defvalue=[],typelist=['list','Ganga.GPIDev.Lib.GangaList.GangaList.GangaList'],
                            sequence=1,checkset='_checksetNestedLists', doc = comments[0] ) } )
    _exportmethods = ['AddRndSeed']

    isMCGeneration = False

    rndseeds = []

    def split(self,job):
        
        subjobs = []

        if self.isMCGeneration :
            app = job.application
            app.add_cfg_Parameter('process.RandomNumberGeneratorService.generator.initialSeed','cms.untracked.uint32')

        for arg in self.args:
            j = self.createSubjob(job)
            #... Add new arguments to subjob
                        
            if self.isMCGeneration :
                self.addRandomSeed( j , arg)

            j.application.args=arg

            logger.debug('Arguments for split job is: ' + str(arg))
            
            subjobs.append(j)

        return subjobs

    def AddRndSeed(self):
        """
        AddRndSeed assumes that you are generating some MC samples within CMSSW. This method appends to each subjob
        configuration file a unique random seed.
        """
        self.isMCGeneration = True

    def getSeed(self, subjob):
        sjid    = subjob.id
        now     = datetime.datetime.now()
        nt      = now.timetuple()
        ms      = now.microsecond
        strms   = str(ms)[1:]
        #... format of rnd seed: min + second + ('stripped')microseconds time
        strseed = str(nt[4]) + str(nt[5]) + strms
        self.rndseeds.append(strseed)
        return int(strseed)

    def addRandomSeed( self, subjob , arguments):
        rndseed = self.getSeed(subjob)
        arguments.append( rndseed )

