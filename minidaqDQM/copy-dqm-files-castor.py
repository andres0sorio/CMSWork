#!/usr/bin/python

import os,sys
import string

# ...
# Andres Osorio - aosorio@uniandes.edu.co
# .

print 'Copying files: '

if len(sys.argv) >= 2:
    infile= str(sys.argv[1])

fh    = open(infile)
nfiles=0

cpmethod = 'rfcp'
cpopts   = ' '
tprefix  = ' /castor/cern.ch/user/a/aosorio/miniDAQ/DQM/'
sprefix  = ' '

while 1:
    line     = fh.readline()
    if not line:
        break
    pass
    info     = line.split('/')
    filename = info[len(info)-1]
    source   = sprefix  + string.replace(line,"\n","")
    target   = tprefix  + filename
    command  = cpmethod + cpopts + source + target  
    print command
    os.system(command)
    nfiles+=1

print 'Done. Total files: ', (nfiles-1)

