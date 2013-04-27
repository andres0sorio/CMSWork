##############################################################################
# Ganga Project. http://cern.ch/ganga
# DBS - Data Bookkeeping System Utility
#
###############################################################################

import os, re

from Ganga.GPIDev.Lib.Dataset import Dataset
from Ganga.GPIDev.Schema import *
from Ganga.GPIDev.Lib.File import File
from Ganga.GPIDev.Base import GangaObject
from Ganga.Utility.logging import getLogger
from Ganga.Utility.Shell import Shell

import Ganga.Utility.Config 

logger = getLogger()

from GangaCMS.Lib.CMSDataset import *

class DBSSearch(GangaObject):
    """
    Data Bookkeeping System Utility: Ganga wrapper around the DBS-CLI Utilities
    
    """

    comments=[]
    comments.append('DBS Server')
    comments.append('DBS instance name')

    schemadic={}
    schemadic['dbsServer']=SimpleItem(defvalue='cmsdbsprod.cern.ch', doc=comments[0])
    schemadic['dbsInstance']=SimpleItem(defvalue='cms_dbs_prod_global', doc=comments[1])
    
    _schema   =  Schema( Version(1,0), schemadic )
    _name     = 'DBSSearch'
    _category = 'Tools'
    
    _exportmethods = ['searchFiles',
                      'searchMCFiles',
                      'searchSites',
                      'exploreDbs',
                      'getCMSDataset',
                      'getSites',
                      'exportFiles',
                      'dumpResults',
                      'updateUrl',
                      'findFileWithLS']
    
    cmsconf = Ganga.Utility.Config.getConfig('CMSSW')
    dbsPath = cmsconf['dbsPath'] + '/'
    
    def __init__(self):
        super(DBSSearch, self).__init__()
        #... Default url address where to find the DBSServlet

        self.files   = []
        self.sites   = []
        self.run     = 1000
        self.dataset = '/Cosmics/CRAFT09-PromptReco-v1/RECO' #... example
        self.asearchCLI = self.cmsconf['dbsCommand']
        self.asearchCMD = ' --notwril --query='

        self.exploreResults = []
        
        #... Default search pattern
        
        self.default_file_search = 'find file where run=###RUN### AND dataset=###DATASET### AND file.status = VALID'
        self.default_site_search = 'find site.name where run=###RUN### AND dataset=###DATASET### AND file.status = VALID'
        
        self.url = 'http://' + self.dbsServer + '/' + self.dbsInstance + '/servlet/DBSServlet'

        print 'Defaults:'
        print self.url

    def searchFiles(self, runid, dataset):
        """
        searchFile: Given a run number and a dataset, find a list of VALID files
        """
        self.run = runid
        
        if dataset != None:
            self.dataset = dataset
            
        findcmd = self.default_file_search.replace('###RUN###',str( runid ) )
        findcmd = findcmd.replace('###DATASET###', str( self.dataset) )
        cmd = 'python ' + self.dbsPath + self.asearchCLI + self.asearchCMD + '\"' + findcmd + '\"' + ' --url=' + self.url

        raw_result = os.popen(cmd,'r').readlines()

        self.files = []
        
        for line in raw_result:
            pos = line.find('.root')
            if pos > 1:
                rm = -1* ( len(line) - (pos+5) )
                self.files.append(line[:rm]) # each line contains [tab + newline] in dbs-client: ver. DBS_2_0_6

        if len ( self.files ) > 1:
            return True

        return False

    def searchSites(self, runid, dataset):
        """
        searchSites:  Given a run number and a dataset, find a list of Sites for which files are VALID
        """
        self.run = runid

        if dataset != None:
            self.dataset = dataset

        findcmd = self.default_site_search.replace('###RUN###',str( runid ) )

        if runid == 1:
            self.default_site_search = 'find site.name where dataset=###DATASET### AND file.status = VALID'
            findcmd = self.default_site_search.replace('###DATASET###', str( self.dataset) )
        else:
            findcmd = findcmd.replace('###DATASET###', str( self.dataset) )
            
        cmd = 'python ' + self.dbsPath + self.asearchCLI + self.asearchCMD + '\"' + findcmd + '\"' + ' --url=' + self.url
        raw_result = os.popen(cmd,'r').readlines()

        self.sites = []

        del raw_result[0:3]

        for line in raw_result:
            self.sites.append(line[:-2])

        if len ( self.sites ) > 1:
            return True

        return False
    
    def getCMSDataset(self):
        dataset = CMSDataset()        
        
        for file in self.files:
            dataset.names.append(file)

        dataset.location = 'grid'
        
        return dataset

    def getSites(self):
        
        return self.sites
    

    def exportFiles(self,outfile):
        if len ( self.files ) <= 0:
            return False
        
        out = open(outfile,'w')
        for file in self.files:
            out.writelines(file + '\n')
        out.close()
        return True

    def dumpResults(self,outfile):
        """
        dumpResults: results obtained with exploreDBS() are dump to a file
        """
        if len ( self.exploreResults ) <= 0:
            return False

        out = open(outfile,'w')
        for file in self.exploreResults:
            out.writelines(file + '\n')
        out.close()
        return True

    def updateUrl(self):
        self.url = 'http://' + self.dbsServer + '/' + self.dbsInstance + '/servlet/DBSServlet'
        print 'New Url:'
        print self.url

    def searchMCFiles(self, dataset):
        """
        searchFile: Given a dataset, find a list of VALID files
        """
        self.run = 1
        
        if dataset != None:
            self.dataset = dataset

        self.default_file_search = 'find file where dataset=###DATASET### AND file.status = VALID'
    
        findcmd = self.default_file_search.replace('###DATASET###', str( self.dataset) )
        cmd = 'python ' + self.dbsPath + self.asearchCLI + self.asearchCMD + '\"' + findcmd + '\"' + ' --url=' + self.url

        raw_result = os.popen(cmd,'r').readlines()

        self.files = []
        
        for line in raw_result:
            pos = line.find('.root')
            if pos > 1:
                rm = -1* ( len(line) - (pos+5) )
                self.files.append(line[:rm]) # each line contains [tab + newline] in dbs-client: ver. DBS_2_0_6

        if len ( self.files ) > 1:
            return True

        return False

    def exploreDbs(self, query):
        """
        exploreDbs: send your own query to DBS
        """
        
        findcmd = query
        cmd = 'python ' + self.dbsPath + self.asearchCLI + self.asearchCMD + '\"' + findcmd + '\"' + ' --url=' + self.url

        raw_result = os.popen(cmd,'r').readlines()

        if len(raw_result) <= 1:
            print 'No results found'
            return False
        
        self.exploreResults = []
        for line in raw_result:
            print line[:-2]
            self.exploreResults.append( line[:-2] )
            
        return True

    def findFileWithLS(self, dataset, runid, lumi):
        """
        findFileWithLS: make a query to find the file(s) which contain a specific Lumisection; useful to remove from file list files that have not the
        specific lumisection
        """
        
        findcmd = 'find file where run.number='+ str(runid) + ' AND dataset like *' + dataset + '* AND lumi=' + str(lumi)
        cmd = 'python ' + self.dbsPath + self.asearchCLI + self.asearchCMD + '\"' + findcmd + '\"' + ' --url=' + self.url

        raw_result = os.popen(cmd,'r').readlines()

        if len(raw_result) <= 1:
            print 'No results found'
            return False
        
        for line in raw_result:
            fpos = line.find('.root')
            if fpos > 0:
                self.files.append(line[:-1])
                print line
        
        return True
    

#............................................................................................
