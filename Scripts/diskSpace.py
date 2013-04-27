#!/usr/bin/python

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

cmd = 'ls '+ path 
users = os.popen(cmd,'r').readlines()

for us in users:
    user = us[:-1]
    cmd ='du -hs ' + path + '/' + user
    result = os.popen(cmd,'r').readlines()
    info = result[0].split()
    space = info[0]
    print user, space




    
    
