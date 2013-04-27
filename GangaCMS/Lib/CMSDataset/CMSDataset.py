##############################################################################
# Ganga Project. http://cern.ch/ganga
# A simple CMS dataset
#
###############################################################################

import os, re

from Ganga.GPIDev.Lib.Dataset import Dataset
from Ganga.GPIDev.Schema import *
from Ganga.Utility.logging import getLogger
from Ganga.Utility.Shell import Shell
from Ganga.GPIDev.Lib.File import File

import Ganga.Utility.Config 

logger = getLogger()
shell  = Shell()

class CMSDataset(Dataset):
    '''Very simple CMS dataset: can be a list of local files, files on CASTOR etc
    Object can be be initiliazed providing a list of files contained in a single text file.
    If not object is passed to the list, then you can add a file by hand setting the
    names attributes to a list of your wish.
    '''

    cmsconfig = Ganga.Utility.Config.getConfig('CMSSW')
    
    _schema = Schema(Version(1,0), {
        'names'     : SimpleItem(defvalue = [], typelist=['str'], sequence = 1,
                                 doc = 'The selected primary file names'),
        'location'  : SimpleItem(defvalue = 'local',
                                 doc = 'Location of files. To configure prefix.'),
        'subdir'    : SimpleItem(defvalue = '.',
                                 doc = 'If the CMSDataset is an output, then it will be put under this subdir'),
        'type'      : SimpleItem(defvalue = 'PoolSource',
                                 doc = 'Source type. Default is PoolSource.'),
        'secondary' : SimpleItem(defvalue = [], typelist=['str'], sequence = 1,
                                 doc = 'The selected secondary file names') 
        } )
    
    _category = 'datasets'
    
    _name = 'CMSDataset'
    
    _exportmethods = ['SetLocation','SetLFNs','SetSecondaryLFNs', 'Prepare','SetDatasetFromTwiki','SetMaxFiles']
    
    _GUIPrefs = [ { 'attribute' : 'names'     , 'widget' : 'String_List' },
                  { 'attribute' : 'secondary' , 'widget' : 'String_List' },
                  { 'attribute' : 'location'  , 'widget' : 'String' },
                  { 'attribute' : 'type'      , 'widget' : 'String' },
                  { 'attribute' : 'subdir'    , 'widget' : 'String' }    ]
        
    prefix     = {}

    fileprefix = ''
    
    prefix['local']    = 'file:'
    prefix['castor']   = 'rfio:'
    prefix['uniandes'] = 'rfio:'
    prefix['caf']      = ''
    prefix['grid']     = ''
        
    def __init__(self, infile = None, location='local'):
        super(CMSDataset,self).__init__()
        self.SetLocation ( location )
        if infile is not None:
            self.SetLFNs( infile )
            
    def add_prefix_to_list(self):
        print "add prefix to list"

    def check_file_prefix(self):
        print "check that given list has an appropiate prefix"

    def SetLocation(self,loc):
        self.location = loc
        try: 
            self.fileprefix = self.prefix[loc]
        except ValueError:
            print 'Location not valid or known'

    def SetLFNs(self, infile):

        filepath=''
        input = open( infile.name , 'r' )

        if infile.subdir != '.':
            filepath = infile.subdir

        try:
            while 1:
                line = input.readline()
                if not line:
                    break
                pass
                tmp  = line.split('\n')
                file = tmp[0]
                if file != '' :
                    self.names.append( self.fileprefix + filepath + file )
        finally:
            input.close()

    def SetSecondaryLFNs(self, infile):
        
        filepath=''
        input = open( infile.name , 'r' )

        if infile.subdir != '.':
            filepath = infile.subdir

        try:
            while 1:
                line = input.readline()
                if not line:
                    break
                pass
                tmp  = line.split('\n')
                file = tmp[0]
                if file != '' :
                    self.names.append( self.fileprefix + filepath + file )
        finally:
            input.close()

    def SetDatasetFromTwiki(self, url, location):

        user = os.environ['USER']
        tmppath = '/tmp/'+ user + '/'
        tmpfile = tmppath + 'list_of_files.txt'
        logfile = tmppath + 'wget-log'
        getopt  = ' -O ' + tmpfile + ' -o ' + logfile

        excode = os.path.isdir(tmppath)
        if excode != True:
            cmd = ('mkdir ' + tmppath)
            os.system(cmd)

        if url.find('http') != 0:
            url = self.cmsconfig['dataTwiki'] + '/' + url

        getcmd  = 'wget ' + url + getopt
        os.system( getcmd )
        ff = File( name=tmpfile )
        ff.subdir = ''
        self.SetLocation( location )
        self.SetLFNs( ff )

        #cleanup termpary area
        cmd = 'rm ' + tmpfile
        os.system(cmd)
        cmd = 'rm ' + logfile
        os.system(cmd)
        
    def SetMaxFiles(self, nfiles):
        ## for testing purposes: only take the first nfiles on the list
        del self.names[(nfiles-1):-1]
        logger.info('SetMaxFiles: list has now nfiles')
        
