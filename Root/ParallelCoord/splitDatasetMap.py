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

splitcmd    = 'split '
splitopt    = '-l 10000 -a 3 -d '

listofevts  = 'event.dataset.map.txt'
outpath     = runid
afspath     = os.getcwd() + '/' + outpath + '/'
prefix      = ' i.'+ outpath + '.'

seqcmds     = ['cp ' + listofevts + ' ./' + outpath,
               'cd ' + outpath,
               splitcmd + splitopt + listofevts + prefix ]

fullseq     = ' ; '.join( seqcmds )

print fullseq
exitcode = os.system( fullseq )

print 'Done.'
