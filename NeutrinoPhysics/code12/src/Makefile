SHELL = /bin/sh
UNAME = $(shell uname)

# Root variables
ROOTCFLAGS   = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS     = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --libs) 
ROOTGLIBS    = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --glibs)

################
##linux
CXX          = g++
RM           = rm -f 
AR	     = ar cru

##Flags
CXXFLAGS     = -O0 -g -Wall -fPIC
#CXXFLAGS     += -D_DEBUG

GSLINC       =$(shell $(GSLPATH)/bin/gsl-config --cflags)
GSLLIB       =$(shell $(GSLPATH)/bin/gsl-config --libs)

BOOSTINC     =-I$(BOOSTPATH)/include

INCDIR       = .
SRCDIR       = .
LIBDIR       = .
EXEDIR       = ../bin

GARBAGE      = *.o $(EXEDIR)/evalxsec.exe $(EXEDIR)/validate.exe $(EXEDIR)/evalintegrals.exe

SOGARBAGE    = *.so

CXXFLAGS    += -I$(INCDIR) $(ROOTCFLAGS) $(GSLINC) $(BOOSTINC)
LINKFLAGS    =

##Libraries
LIBS       += $(ROOTLIBS) -lMinuit -lMathCore -lMathMore -lXMLParser $(GSLLIB) \
	-L$(BOOSTPATH)/lib -lboost_program_options

OBJS   = Graphics.o Integrals.o DOMParameters.o nuN_interpxsec.o PShadow.o \
	ShowerEvents.o MuTrackEvents.o IProbabilityMatrix.o \
	MixingParameters.o NeutrinoOscInVacuum.o NeutrinoOscInMatter.o main.o

VALOBJS = Integrals.o DOMParameters.o IntegralsPlots.o nuN_interpxsec.o PShadow.o

all : evalxsec.exe validate.exe evalintegrals.exe

%.o : %.C
	$(CXX) $(CXXFLAGS) -c $< 	

evalxsec.exe: $(OBJS)
	 $(CXX) -o $(EXEDIR)/$@ $(OBJS) $(LINKFLAGS) $(LIBS)

validate.exe: $(VALOBJS) validate.o
	 $(CXX) -o $(EXEDIR)/$@ $(VALOBJS) validate.o $(LINKFLAGS) $(LIBS)

evalintegrals.exe: $(VALOBJS) evalintegrals.o
	 $(CXX) -o $(EXEDIR)/$@ $(VALOBJS) evalintegrals.o $(LINKFLAGS) $(LIBS)

clean	:
	$(RM) $(GARBAGE)

cleanall:
	$(RM) $(GARBAGE) $(SOGARBAGE)
