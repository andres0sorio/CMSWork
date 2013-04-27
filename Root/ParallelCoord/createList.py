#!/usr/bin/python

import sys,os

#.

if len(sys.argv) >= 2:
    sourceA  = str(sys.argv[1])
    sourceB  = str(sys.argv[2])
else:
    print 'usage: ' + sys.argv[0] + ' <Data.files> <Emu.files>'
    sys.exit()

#...

runid = sourceA.split('/')[0].split('.')[1]

outfileA  = 'list_of_files.' + runid + '.txt'
fout      = open(outfileA,'w')

outfileB  = 'dataset.'+ runid + '.txt'
ffout     = open(outfileB,'w')

infileA   = open(sourceA,'r')
infileB   = open(sourceB,'r')

filesA = []
filesB = []

while 1:

    line = infileA.readline().split()
    if not line:
        break
    pass
    print line[0]
    filesA.append( line[0] )

while 1:

    line = infileB.readline().split()
    if not line:
        break
    pass
    print line[0]
    filesB.append( line[0] )

maxfiles = len(filesA)

for i in range(0,maxfiles):
    fout.writelines( filesA[i] + '\t' + filesB[i] + '\n')
    ffout.writelines( filesA[i] + '\n')
    
fout.close()
ffout.close()
