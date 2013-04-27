from Ganga.GPIDev.Base import GangaObject
from Ganga.GPIDev.Schema import *

class cmsRunTools(GangaObject):

    schemadic={}

    _schema   =  Schema( Version(1,0), schemadic )
    _name     = 'cmsRunTools'
    _category = 'Tools'
    
    _exportmethods = ['getSW']
                      
    def __init__(self):
        super(cmsRunTools, self).__init__()
        self.apath = ''
        
    def getSW( self, path ):
	posi = path.find('CMSSW')
        if posi <= 0:
            return ''
	posf = path.find('/', posi)
        return path[posi:posf]
    
