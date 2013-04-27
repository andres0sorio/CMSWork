##############################################################################
# Ganga Project. http://cern.ch/ganga
# A simple CMS/CRAB dataset
#
###############################################################################

import os, re

from Ganga.GPIDev.Lib.Dataset import Dataset
from Ganga.GPIDev.Schema import *
from Ganga.Utility.logging import getLogger
logger = getLogger()
   
class CrabDataset(Dataset):
    '''Very simple CMS/CRAB dataset: this class sumarises files and output
    options for a given output data'''
    
    schemadic={}
    schemadic['return_data']=SimpleItem(defvalue=0, doc='Return data with job')
    schemadic['copy_data']=SimpleItem(defvalue=1, doc='Copy data to SE')
    schemadic['publish_data']=SimpleItem(defvalue=0, doc='Publish data to DB')
    schemadic['storage_element']=SimpleItem(defvalue='srm-cms.cern.ch', doc='Storage element')
    schemadic['user_remote_dir']=SimpleItem(defvalue='', doc='User remote directory(must have grid write permissions')
    schemadic['storage_path']=SimpleItem(defvalue='/srm/managerv2?SFN=/castor/cern.ch/', doc='Storage path in SE')
    schemadic['names']=SimpleItem(defvalue = [], typelist=['str'], sequence = 1, doc = 'The selected file names')
    
    _schema   = Schema( Version(1,0), schemadic ) 

    _category = 'datasets'

    _name = 'CrabDataset'
    
    ###_exportmethods = ['SetLocation','SetLFNs','Prepare']

    _GUIPrefs = [ { 'attribute' : 'names'    , 'widget' : 'String_List' },
                  { 'attribute' : 'storage_element' , 'widget' : 'String' },
                  { 'attribute' : 'storage_path'     , 'widget' : 'String' }]
    
    def __init__(self, infile = None, location='local'):
        super(CrabDataset,self).__init__()
        
        
