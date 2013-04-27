SHELL = /bin/sh
UNAME = $(shell uname)

# Root variables
ROOTCFLAGS   = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS     = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --libs) 
ROOTGLIBS    = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --glibs)

##GSLPATH      =$(LCG_release_area)/GSL/1.8/$(CMTCONFIG)
##GSLINC       =$(GSLPATH)/include
##GSLLIB       =$(GSLPATH)/lib
##CLHEPINC     =/opt/cern/clhep/pro/include

################
##linux
CXX          = g++
RM           = rm -f 
AR	     = ar cru

##Flags
CXXFLAGS     = -O0 -g -Wall -fPIC
#CXXFLAGS     += -D_DEBUG


INCDIR       = .
SRCDIR       = .
LIBDIR       = .
EXEDIR       = ../exe

GARBAGE      = *.o $(EXEDIR)/l1Analyse

SOGARBAGE    = *.so

#################
##Dependencies
# Linux
ifeq "$(UNAME)" "Linux"
RANLIB       = ranlib
CXXFLAGS    += -I$(INCDIR) $(ROOTCFLAGS) -I$(GSLINC) -I$(CLHEPINC)
LINKFLAGS    =
endif

# MAC OSX
ifeq "$(UNAME)" "Darwin"
RANLIB       = ranlib -s
CXXFLAGS    += -I$(INCDIR) $(ROOTCFLAGS)
LINKFLAGS    = -Xlinker -flat_namespace -bind_at_load
endif

##Libraries
LIBS       += $(ROOTLIBS) -lMinuit -lMathCore -lMathMore -L$(GSLLIB) -lgslcblas

OBJECTS   = Utilities.o \
	L1Tree.o L1ExtraTree.o MuonRecoTree.o RunAnalysis.o \
	L1TTUTree.o BasicOutput.o main.o

OBJSINGLE = BasicOutput.o L1Tree.o L1TTUTree.o mainLooper.o

OBJCONSCK = BasicOutput.o L1Tree.o L1TTUTree.o consistCheck.o

all : l1Analyse singleAnal consistCheck

%.o : %.C
	$(CXX) $(CXXFLAGS) -c $< 	

l1Analyse: $(OBJECTS)
	 $(CXX) -o $(EXEDIR)/$@ $(OBJECTS) $(LINKFLAGS) $(LIBS)

singleAnal: $(OBJSINGLE)
	 $(CXX) -o $(EXEDIR)/$@ $(OBJSINGLE) $(LINKFLAGS) $(LIBS)

consistCheck: $(OBJCONSCK)
	 $(CXX) -o $(EXEDIR)/$@ $(OBJCONSCK) $(LINKFLAGS) $(LIBS)

clean	:
	$(RM) $(GARBAGE)

cleanall:
	$(RM) $(GARBAGE) $(SOGARBAGE)
