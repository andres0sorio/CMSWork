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

EXROOT       = $(EXROOTMG)
EXROOTINC    = -I$(EXROOT)
EXROOTLIB    = -L$(EXROOT)/lib -lExRootAnalysis

INCDIR       = .
SRCDIR       = .
LIBDIR       = .
EXEDIR       = ../bin

GARBAGE      = *.o $(EXEDIR)/lhe2lhco

SOGARBAGE    = *.so

CXXFLAGS    += -I$(INCDIR) $(ROOTCFLAGS) $(GSLINC) $(BOOSTINC) $(EXROOTINC)
LINKFLAGS    =

##Libraries
LIBS       += $(EXROOTLIB) $(ROOTLIBS) -lMinuit -lMathCore -lMathMore -lXMLParser -lEG $(GSLLIB) 

OBJS    = Histograms.o LHCOParser.o LHEAnalyzer.o main.o


all : lhe2lhco

%.o : %.cc
	$(CXX) $(CXXFLAGS) -c $< 	

lhe2lhco: $(OBJS)
	 $(CXX) -o $(EXEDIR)/$@ $(OBJS) $(LINKFLAGS) $(LIBS)

clean	:
	$(RM) $(GARBAGE)

cleanall:
	$(RM) $(GARBAGE) $(SOGARBAGE)
