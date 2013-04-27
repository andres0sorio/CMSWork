
def getEnvironment( config = {} ):
    import sys
    import os.path
    import PACKAGE
   
    PACKAGE.standardSetup()
    print 'GangaCMS> getEnvironment : done'
    return 

def loadPlugins( config = {} ):
    import Lib.CMSexe
    import Lib.CRAB
    import Lib.CMSDataset
    import Lib.DBS
    print 'GangaCMS> loadPlugins : done'

