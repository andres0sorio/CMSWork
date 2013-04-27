##############################################################################
# Ganga Project. http://cern.ch/ganga
# The full CMS dataset paths as required by CRAB
# 
###############################################################################

import os, re

from Ganga.GPIDev.Lib.Dataset import Dataset
from Ganga.GPIDev.Schema import *
from Ganga.Utility.logging import getLogger
from Ganga.Utility.Shell import Shell

logger = getLogger()
shell = Shell()
   
class CMSDatasetPath(Dataset):
    """
    CMS dataset path: This is the full path to a dataset
    """
    
    _schema = Schema(Version(1,0), {
        'names'    : SimpleItem(defvalue = [], typelist=['str'], sequence = 1,
                                doc = 'The selected file names'),
        'type' : SimpleItem(defvalue = 'pset', doc = 'Only to be used with CRAB for the moment')
        } )
    
    _category = 'datasets'
    
    _name = 'CMSDatasetPath'
    
    #.._exportmethods = ['set_dataset_type','list_datasets','get_dataset', 'get_dataset_filenames' ]
    _exportmethods = []
    
    _GUIPrefs = [ { 'attribute' : 'names'    , 'widget' : 'String_List' } ]
    
    
    def __init__(self):
        super(CMSDatasetPath,self).__init__()
        
    def addPath(self,path):
        self.names.append(path)

    



