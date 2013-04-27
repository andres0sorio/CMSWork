#!/usr/bin/python

import os,sys
import string

# ...
# Andres Osorio - aosorio@uniandes.edu.co
# .

if len(sys.argv) >= 2:
    infile= str(sys.argv[1])
    
print 'Copying files: '

fh    = open(infile)
nfiles=0

cpmethod = 'srmcp'
cpopts   = ' -srm_protocol_version=2 -use_urlcopy_script=true -urlcopy= ${SRM_PATH}/sbin/url-copy.sh'

option   = 'ZMUMU'

#............... TO

#tprefix  = ' srm://srm-cms.cern.ch:8443/srm/managerv2\?SFN=/castor/cern.ch'
#tprefix  = ' srm://moboro.uniandes.edu.co:8446/srm/managerv2\?SFN=/dpm/uniandes.edu.co/home/cms'
tprefix  = ' file:///'

#tdir     = '/tmp/aosorio/'+option+'/'
tdir     = '/opt/exp_soft/CMS/cmsspace_03_10/data/'+option+'/' 
#tdir     = '/user/a/aosorio/gridfiles/'
#tdir     = '/user/s/sanabria/gridfiles/Summer09/SUSY_LM0_229_SUSYPAT_V5_v1/'
#tdir     = '/user/a/aosorio/gridfiles/SUSY/Summer10/SUSY_LM0/'

#............... FROM

#sprefix  = ' srm://cmssrm.fnal.gov:8443/srm/managerv2\?SFN=/11'
#sprefix  = ' srm://grid-srm.physik.rwth-aachen.de:8443/srm/managerv2\?SFN=/pnfs/physik.rwth-aachen.de/cms'
#sprefix  = ' srm://pccms2.cmsfarm1.ba.infn.it:8443/srm/managerv2\?SFN=/pnfs/cmsfarm1.ba.infn.it/data/cms/phedex'
#sprefix  = ' srm://hephyse.oeaw.ac.at:8446/srm/managerv2\?SFN=/dpm/oeaw.ac.at/home/cms'
#sprefix = ' srm://storm-se-01.ba.infn.it:8444/srm/managerv2\?SFN=//cms'
#sprefix = ' srm://ingrid-se02.cism.ucl.ac.be:8444/srm/managerv2\?SFN=/storage/data/cms'

sprefix = ' srm://srm-cms.cern.ch:8443/srm/managerv2\?SFN=/castor/cern.ch/cms'

 
while 1:
    line     = fh.readline()
    if not line:
        break
    pass
    info     = line.split('/')
    filename = info[len(info)-1]
    source   = sprefix  + string.replace(line,"\n","")
    target   = tprefix  + tdir   + filename
    command  = cpmethod + cpopts + source + target  
    print command
    os.system(command)
    nfiles+=1

print 'Done. Total files: ', (nfiles-1)

