#######################################################################
#     CRAB Splitters                                                  #
#     Andres Osorio                                                   #
#                                                                     #
#######################################################################
#__author__   = 'Andres Osorio'
#__date__     = 'April 2009'
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
from GangaCMS.Lib.CMSDataset import CMSDatasetPath

######################################################################
#..
#.. Use the basic CRAB splitter (as part of the config file)
#..
######################################################################

class BasicCrabSplitter(ISplitter):
    """ This is just a wrapper around the three options to be inserted
    in Crab's configuration file:

    total_number_of_events=1
    events_per_job = 1000
    number_of_jobs = 1

    a single Ganga job will be submitted, leaving to CRAB to deal with the splitting
    according to its rules.
    
    """

    comments=[]
    comments.append('Events per job')
    comments.append('Number of jobs')
    
    _name = 'BasicCrabSplitter'
    _schema = Schema(Version(1,0),{
        'evtsperjob' : SimpleItem(defvalue=1000, doc=comments[0] ),
        'njobs'      : SimpleItem(defvalue=1   , doc=comments[1] )  } )
    
    def split(self,job):
        logger.debug("Splitting job")

        from Ganga.GPIDev.Lib.Job import Job
        
        subjobs=[]
        
        j = self.createSubjob(job)
        j.application = job.application
        j.application.uselibs = job.application.uselibs
        j.application.version = job.application.version
        j.backend = job.backend
        j.inputdata = job.inputdata
        j.splitter = job.splitter
        j.outputsandbox = job.outputsandbox[:]
        
        #... 
        subjobs.append( j )
        
        return subjobs

#.................................................................................

#.................................................................................
