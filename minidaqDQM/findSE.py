#!/usr/bin/python
# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...

import sys,os
from optparse import OptionParser
#-----------------------------------------------------
#-----------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="tier",
                  help="Tier alias" )

parser.add_option("-t", type = "string", dest="file",
                  help="Logical file name", metavar="LFN" )

(options, args) = parser.parse_args()

if options.tier is None:
        parser.error("please provide a tier alias")
#-----------------------------------------------------
#-----------------------------------------------------

tier      = options.tier
lfn       = options.file


prefix  = 'http://cmsweb/phedex/datasvc/xml/prod/lfn2pfn\?protocol=srmv2\&node='
fullcmd = prefix + tier + '\&lfn=' + lfn
wgetopt = ' -O pfn.xml'
wgetcmd = 'wget '

cmd     = wgetcmd + fullcmd + wgetopt
excode  = os.system(cmd)

