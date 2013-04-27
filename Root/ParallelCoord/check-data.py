#!/usr/bin/python

import os,sys
import string

# ...
# Andres Osorio - aosorio@uniandes.edu.co
# .

if len(sys.argv) >= 2:
    runid = sys.argv[1]
else:
    print 'usage: ' + sys.argv[0] + ' runid'
    sys.exit()

lsmethod = 'rfdir'
cpcmd = 'rfcp '

castor = os.environ['CASTOR_HOME']

option = 'data.'
fullpath = castor + '/promptAnalysis/' + option + runid +'/'
outpath = option + runid
outfilename =  outpath + '/list_of_files.txt'
afspath = os.getcwd() + '/' + outpath + '/'

cmd    = lsmethod + ' ' + fullpath
excode = os.system(cmd)

if excode == 0:
    
    excode = os.path.isdir(outpath)
    if excode != True:
        cmd = ('mkdir '+ outpath )
        os.system(cmd)

    cmd  = 'rfdir ' + fullpath + ' | awk \' { print $9 } \' '
    files = os.popen(cmd,'r').readlines()

    outfile = open(outfilename,'w')
    
    for ff in files:

        source = fullpath + ff[:-1] #remove the annoying '\n'
        target = afspath + ff
        cmd = cpcmd + source + ' ' + target
        print cmd
        os.system(cmd)
        outfile.write( target )

    outfile.close()
        
print 'Done.'
