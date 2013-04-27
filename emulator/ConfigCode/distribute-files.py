import os,sys

# ...
# Andres Osorio - aosorio@uniandes.edu.co
# .

print 'Distributing the source code across the different paths'

infile= 'files-location.txt'
fh    = open(infile)

cmssw_base=os.environ.get("CMSSW_BASE")

nfiles=0

while 1:
    line = fh.readline()
    if not line:
        break
    pass
    info = line.split()
    file = info[0]
    target = info[1]
    command = 'cp -iv ' + file + ' ' + cmssw_base + '/src/' + target 
    os.system(command)
    nfiles+=1

print 'Done. total files distributed: ', nfiles    

