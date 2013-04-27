#!/usr/bin/python
import os,sys
#...

name=sys.argv[1]
fh = open(name)

for line in fh.readlines():
    text=line.split('\n')
    print 'print \'' + text[0] +'\''

