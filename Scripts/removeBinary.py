#!/usr/bin/python
# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...

import os,sys
import string
from optparse import OptionParser
#-----------------------------------------------------

parser = OptionParser()
parser.add_option("-d", type = "string", dest="dir",
                  help="DIR", metavar="DIR" )

(options, args) = parser.parse_args()

if options.dir is None:
        parser.error("please give a directory")
	
#-----------------------------------------------------

path = options.dir

extension = ['o','so','d','pyc']

for ext in extension:
	
	cmd = 'find '+ path + ' -name \"*.' + ext + '\"'
	files = os.popen(cmd,'r').readlines()
	#print cmd
	for f in files:
		
		file = f[:-1]
		cmd = 'rm -v ' + file
		#print cmd
		os.system(cmd)
		

