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

GARBAGE      = *.o $(EXEDIR)/test

SOGARBAGE    = *.so

CXXFLAGS    += -I$(INCDIR) $(ROOTCFLAGS) $(GSLINC) $(BOOSTINC)
LINKFLAGS    =

##Libraries
LIBS       += $(ROOTLIBS) -lMinuit -lMathCore -lMathMore -lXMLParser $(GSLLIB) 

OBJS    = LHCOParser.o WeightsAnalyzer.o PGSAnalyzer.o main.o

OBJSWGT = WeightsAnalyzer.o weights.o


all : test reader

%.o : %.cc
	$(CXX) $(CXXFLAGS) -c $< 	

test: $(OBJS)
	 $(CXX) -o $(EXEDIR)/$@ $(OBJS) $(LINKFLAGS) $(LIBS)

reader: $(OBJSWGT)
	 $(CXX) -o $(EXEDIR)/$@ $(OBJSWGT) $(LINKFLAGS) $(LIBS)

clean	:
	$(RM) $(GARBAGE)

cleanall:
	$(RM) $(GARBAGE) $(SOGARBAGE)
