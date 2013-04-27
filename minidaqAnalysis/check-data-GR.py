#!/usr/bin/python
# ...
# Andres Osorio - aosorio@uniandes.edu.co
# ...

import os,sys
import string

from optparse import OptionParser
#---------------------------------------------------------------------------
#---------------------------------------------------------------------------
parser = OptionParser()
parser.add_option("-r", type = "string", dest="runid",
                  help="Run Id number", metavar="RUNID" )

parser.add_option("-t", type = "string", dest="tag",
                  help="Global run tag", metavar="GLOBAL RUN TAG" )

parser.add_option("-s", type = "string", dest="stream",
                  help="Stream (A,Express,HLT,...)", metavar="A", default='A')

(options, args) = parser.parse_args()

if options.runid is None:
        parser.error("please give a run number")

if options.tag is None:
        parser.error("please give a global run tag (ex. MWGR_25, CRUZET_II)")

#---------------------------------------------------------------------------
#---------------------------------------------------------------------------

runid = options.runid
mwgrid = options.tag
subprefix=options.stream

lsmethod = 'rfdir'
tmp1 = str(runid)

tmp2 = tmp1[0:len(tmp1)-3]

if len(tmp2) < 3:
    pathA = '0'+tmp2
else:
    pathA = tmp2

pathB = tmp1[len(tmp1)-3:len(tmp1)]

runpath = pathA + '/' + pathB

option = 'streamer'

prefix='/castor/cern.ch/cms/store/'+ option +'/' + mwgrid + '/' + subprefix + '/000/'
fullpath = prefix + runpath
cmd = lsmethod + ' ' + fullpath
excode = os.system(cmd)

tprefix = os.environ['CASTOR_CCMUON']
target = tprefix + '/RPC/GlobalRuns/' + mwgrid + '/' + tmp1

cmd = 'rfmkdir ' + tprefix + '/RPC/GlobalRuns/' + mwgrid
os.system(cmd)

outfilename = tmp1 + '/list_of_files.txt'

if excode == 0:
    cmd = 'rfdir ' + target
    excode = os.system(cmd)
    if excode != 0:
        cmd = 'rfmkdir ' + target
        excode = os.system(cmd)
        print 'created new storage directory'
        print 'setting permissions'
        cmd = 'rfchmod +777 ' + target
        excode = os.system(cmd)
        if excode == 0:
            print 'success'
        else:
            print 'could not set permissions to directory'
    
    excode = os.path.isdir(tmp1)
    if excode != True:
        cmd = ('mkdir '+ tmp1 )
        os.system(cmd)

    cmd  = 'rfdir ' + fullpath + ' | awk \' { print $9 } \' '
    files = os.popen(cmd,'r').readlines()

    outfile = open(outfilename,'w')
    for ff in files:
        outfile.write(ff)
    outfile.close()
        
print 'Done.'
