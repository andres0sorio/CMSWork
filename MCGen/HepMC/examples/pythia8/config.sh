#!/bin/sh
if [ ! $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=/opt/hepsw/hepmc/pro/lib
fi
if [ $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/opt/hepsw/hepmc/pro/lib
fi
export PYTHIA8DATA=${PYTHIA8_HOME}/xmldoc
