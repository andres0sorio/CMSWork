#!/bin/bash
cd $XDAQ_ROOT/lib/linux/x86
find ../../../daq/extern -name "lib*.so*" -exec ln -s {} \;
find $XDAQ_ROOT/trigger/ts/extern -name "lib*.so*" -exec ln -s {} \;
