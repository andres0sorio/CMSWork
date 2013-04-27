#!/bin/csh
#................................................
#.. Andres Osorio - aosorio@uniandes.edu.co        
#................................................

set cmsswroot = "/opt/exp_soft/CMS"
set scramarch = "slc5_ia32_gcc434"
set version   = "CMSSW_3_11_3"
set higgsmass = ${1}

setenv VO_CMS_SW_DIR ${cmsswroot}
setenv SCRAM_ARCH ${scramarch}
source ${VO_CMS_SW_DIR}/cmsset_default.csh 
scram project CMSSW ${version}
cd ${version}
eval `scram runtime -csh`  #cmsenv

#................................................
# ...... untar users module .....................
#------------------------------------------------

echo ./calculateAvgXSec_Higgs.py -m 1 -o ${higgmass}

