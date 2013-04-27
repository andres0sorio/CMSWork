################################################################################
# Ganga Project. http://cern.ch/ganga                                          #
# cmsRun : Andres Osorio                                                       #
#                                                                              #
################################################################################
#__author__   = 'Andres Osorio'
#__date__     = 'March 2009'
#__revision__ =  0.1

"""
SimpleCrabExtras.py: Suplementary objects for this simple backend handler for Crab
"""

from Ganga.Utility.logging import getLogger
logger = getLogger()

class SimpleCrabExtras:
    """This class encapsulates additional options that can be given to the
    Simple Crab backend.This allows us to add more to the application
    object than is defined in the schema."""
 
    whitelist=[]
    blacklist=[]
    
    _name = "SimpleCrabExtras"
    
    _category = "extras"
    
    def __init__(self):
        logger.debug( 'SimpleCrabExtas: ready' )
