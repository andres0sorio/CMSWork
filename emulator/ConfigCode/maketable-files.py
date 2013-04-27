import os,sys

# ...
# Andres Osorio - aosorio@uniandes.edu.co
# .

infile= 'files-location.txt'
fh    = open(infile)
cmssw_base=os.environ.get("CMSSW_BASE")

listoffiles=[]

while 1:
    line = fh.readline()
    if not line:
        break
    pass
    info = line.split()
    file = info[0]
    target = info[1]
    listoffiles.append( [ file, target ] )

for files in listoffiles:
    print '| ', files[0], ' | ', files[1], ' |'

