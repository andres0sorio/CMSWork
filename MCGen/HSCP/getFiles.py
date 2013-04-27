#!/usr/bin/python
import sys, os
from optparse import OptionParser
#--------------------------------------------------------
#--------------------------------------------------------
parser = OptionParser()
parser.add_option("-f", type = "string", dest="filelist",
                 help="File list" )

(options, args) = parser.parse_args()

if options.filelist is None:
        parser.error("File list")
#--------------------------------------------------------
#--------------------------------------------------------

filelist = open( options.filelist, 'r')
outfile = open('local-files.txt','w')

for item in filelist.readlines():
	source = item[:-1].replace('fisica/aosorio','home/aosorio/pbsserver')
	file = source.split('/')[-1]
	id = source.split('/')[-3]
	filename = file.split('.')[0] + '_' + id + '_' + file.split('.')[-1]
	target = filename
	cmd = 'cp -v ' + source + ' ' + target
	g = os.system(cmd)

print 'Done!'	

