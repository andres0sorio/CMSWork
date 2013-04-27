include $(FECSOFTWARE_ROOT)/FecHeader.linux
include $(FECSOFTWARE_ROOT)/config/FecRules.linux

XDAQ_ROOT_DIR:=$(XDAQ_ROOT)

include $(XDAQ_ROOT)/config/mfAutoconf.rules
include $(XDAQ_ROOT)/config/mfDefs.linux

Project=rpct
Package=xdaqRpcConfigTest

XDAQ_BACK_TO_ROOT:=$(XDAQ_ROOT)

Sources = \
	XdaqRpcConfigTest.cpp


IncludeDirs = \
	$(BUILD_HOME)/rpct/xdaqLBoxAccess/include \
	$(XERCESROOT)/include \
	$(XERCESROOT)/include/xercesc \
	$(FECSOFTWARE_ROOT)/$(Project)/$(Package)/include \
	$(FECSOFTWARE_ROOT)/generic/include \
	$(FECSOFTWARE_ROOT)/FecSupervisor/include \
	$(FECUSBSOFT_INCLUDE) \
	${FECSOFT_INCLUDE} \
	$(SBSINCLUDEDIR) $(CAENINCLUDEDIR) \
	$(HALINCLUDEDIR) \
	$(ROOTSYS)/include 



LibraryDirs = \
	$(DEVICEDRIVERPATH) \
	$(FECSOFTWARE_ROOT)/ThirdParty/APIConsoleDebugger/lib/linux/x86 

UserCFlags = -g -O2
UserCCFlags = ${FECSOFT_C++FLAGS} -g -O2
UserDynamicLinkFlags = 
UserStaticLinkFlags = 
UserExecutableLinkFlags = -g -O2

ExternalObjects = \
	$(InstallLibDir)/libxdaqlboxaccess.so  \
	$(InstallLibDir)/librpctxdaqutils.so  \
	$(InstallLibDir)/libdevices.so  \
	$(InstallLibDir)/libbs.so  \
	$(InstallLibDir)/libdiag.so  \
	$(InstallLibDir)/librpcti2c.so  \
	$(InstallLibDir)/libii.so  \
	$(InstallLibDir)/liblboxaccess.so  \
	$(InstallLibDir)/libxdaqiiaccess.so  \
	$(InstallLibDir)/libtbstd.so  \
    $(InstallLibDir/librpctxdata.so  \
    $(XDAQ_ROOT)/lib/libCAENLinuxBusAdapter.so \
    $(XDAQ_ROOT)/lib/libGenericHAL.so \
    ${CAEN_DIR}/lib/libCAENVME.so 

# Libraries = lboxaccess tbstd $(FECSOFT_LIB) readline ncurses \
#	devices ii xerces-c xdaq xoap xdata xgi peer toolbox xcept log4cplus udpappender cgicc	

DynamicLibrary= xdaqrpcconfigtest

RpctNeedXdaq = true
include $(BUILD_HOME)/rpct/config/mfDefs
include $(BUILD_HOME)/rpct/config/Makefile.rules
