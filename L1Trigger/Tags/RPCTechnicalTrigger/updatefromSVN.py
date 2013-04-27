#!/usr/bin/python
import os,sys

# ...
# Andres Osorio - aosorio@uniandes.edu.co
# .

print 'Development of RPCTechnicalTrigger code Update from CMSSW-CVS'

option  =' -vi '
location='/src/L1Trigger/RPCTechnicalTrigger'
cmssw_base=os.environ.get("CMSSW_BASE")

sources=[]
sources.append(' interface/*.h ')
sources.append(' src/*.h ')
sources.append(' src/*.cc ')
sources.append(' test/*.py ')
sources.append(' test/*.txt ')
sources.append(' test/*.db ')
sources.append(' BuildFile ')

targets=[]
targets.append('/interface/')
targets.append('/src/')
targets.append('/src/')
targets.append('/test/')
targets.append('/test/')
targets.append('/test/')
targets.append('/.')

indx=0

for files in sources:
    target = cmssw_base + location + targets[indx]
    command = 'cp' + option + files + target
    print command
    os.system(command)
    indx=indx+1
    
print 'Done'  

