#
# Configuration file needed by CRAB
#
#__author__   = 'Andres Osorio'
#__date__     = 'March 2009'
#__revision__ =  0.1

from ConfigSection import *

class ConfigFile:
    """This class creates and edits a configuration file for CRAB"""
    cfgcmds  = ''
    sections = []
    outfile  = None
    
    def __init__(self,filename):

        sec = ConfigSection('CRAB')
        self.sections.append(sec)
        sec = ConfigSection('CMSSW')
        self.sections.append(sec)
        sec = ConfigSection('USER')
        self.sections.append(sec)
        sec = ConfigSection('EDG')
        self.sections.append(sec)

        self.outfile  = open(filename,'w')
                
    def append(self,section,command):
        
        sec = self.getsection(section)
        if sec == None:
            print "Error"
        splcmd = command.split('=')
        att = splcmd[0]
        if len ( splcmd ) > 2:
            tmp = splcmd[1:len(splcmd)]
            val = '='.join(tmp)
        else:
            val = splcmd[1]
        sec.addattribute( att , val ) 
        
    def getsection(self,section):
        for sc in self.sections:
            if section == sc.name:
                return sc
        return None

    def write(self):
        for section in self.sections:
            section.write( self.outfile )
        self.outfile.close()


