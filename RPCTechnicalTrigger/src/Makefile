SHELL = /bin/sh
UNAME = $(shell uname)

# Root variables
ROOTCFLAGS   = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS     = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --libs) 
ROOTGLIBS    = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --glibs)

GSLPATH      =/usr/local

GSLINC       =$(GSLPATH)/include
GSLLIB       =$(GSLPATH)/lib

#.................................................................

CXX          = g++
RM           = rm -f 
AR	     = ar cru

CXXFLAGS     = -O0 -g -Wall -fPIC

INCDIR       = /home/aosorio/Work/emulator
SRCDIR       = .
LIBDIR       = .
EXEDIR       = ../exe

GARBAGE      = *.o $(EXEDIR)/emulate

SOGARBAGE    = *.o *.so

RANLIB       = ranlib
CXXFLAGS    += -I$(INCDIR) $(ROOTCFLAGS)
#CXXFLAGS    += -I$(INCDIR)

LINKFLAGS    =

LIBS       += $(ROOTLIBS) -lMathCore

#AccessConfigMySQL.o

COMMON      = RBCInput.o TTUInput.o RBCProcessTestSignal.o RBCTestLogic.o \
	RBCChamberORLogic.o RBCPatternLogic.o LogicImp.o Dimension.o ToyDB.o \
	AccessConfigMySQL.o RBCId.o PaC.o RBCPaC.o RBCEmulator.o RPCWheel.o TTUTrackingAlg.o \
	RBCBasicConfig.o TTUPaC.o RPCTTU.o RPCData.o RPCProcessTestSignal.o \
	TTUBasicConfig.o RPCTechnicalTrigger.o main.o

all : emulate

%.o : %.cc 
	$(CXX) $(CXXFLAGS) -c $< 	

emulate: $(COMMON)
	 $(CXX) -o $(EXEDIR)/$@ $(COMMON) $(LINKFLAGS) $(LIBS)

clean	:
	$(RM) $(GARBAGE)

cleanall:
	$(RM) $(GARBAGE) $(SOGARBAGE)
