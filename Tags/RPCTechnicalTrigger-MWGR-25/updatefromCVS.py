#!/usr/bin/python
import os,sys

# ...
# Andres Osorio - aosorio@uniandes.edu.co
# .

print 'Development of RPCTechnicalTrigger code Update from CMSSW-CVS'

option  =' -v '
location='/src/L1Trigger/RPCTechnicalTrigger'
cmssw_base=os.environ.get("CMSSW_BASE")

sources=[]
sources.append('/interface/*.h')
sources.append('/src/*.h')
sources.append('/src/*.cc')
sources.append('/test/*.py')
sources.append('/test/*.txt')
sources.append('/test/*.db')
sources.append('/python/*.py')
sources.append('/BuildFile')

targets=[]
targets.append(' ./interface/')
targets.append(' ./src/')
targets.append(' ./src/')
targets.append(' ./test/')
targets.append(' ./test/')
targets.append(' ./test/')
targets.append(' ./python/')
targets.append(' .')

indx=0

for files in sources:
    source = cmssw_base + location + files 
    command = 'cp' + option + source + targets[indx]
    print command
    os.system(command)
    indx=indx+1
    
print 'Done'  

