#!/bin/csh
if( ! $?LD_LIBRARY_PATH ) then
  setenv LD_LIBRARY_PATH /opt/hepsw/hepmc/pro/lib
else
  setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:/opt/hepsw/hepmc/pro/lib
endif
setenv PYTHIA8DATA ${PYTHIA8_HOME}/xmldoc
