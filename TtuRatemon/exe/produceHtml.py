#!/usr/bin/python
# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...

import os,sys
import string
from optparse import OptionParser
#-----------------------------------------------------

parser = OptionParser()
parser.add_option("-f", type = "string", dest="outdir",
                  help="output dir with plots", metavar="OUTDIR" )

(options, args) = parser.parse_args()

if options.outdir is None:
        parser.error("please point to directory")

#-----------------------------------------------------

outdir = options.outdir

#...Produce a nice html page using 'album'
theme = ' -theme=KDE_Style'

target = os.environ['PWD'] + '/' + outdir
cmd = 'album -index index.html -columns 2 ' + target + theme
os.system(cmd)
