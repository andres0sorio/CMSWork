SHELL = /bin/sh
UNAME = $(shell uname)

# Root variables
ROOTCFLAGS   = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS     = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --libs) 
ROOTGLIBS    = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --glibs)

#.................................................................

CXX          = g++
RM           = rm -f 
AR	     = ar cru

CXXFLAGS     = -O0 -g -Wall -fPIC

INCDIR       = .
SRCDIR       = .
LIBDIR       = ../lib
EXEDIR       = ../exe

GARBAGE      = *.o *.so $(EXEDIR)/analyse $(LIBDIR)/*.so

CXXFLAGS    += -I$(INCDIR) $(ROOTCFLAGS)

LIBS        += $(ROOTLIBS) -lMathCore

COMMON      = loader.o BasicOutput.o eventB.o eventV.o UCSBTuplesAnalyzer.o

all : analyse

%.o : %.cc
	$(CXX) $(CXXFLAGS) -c $< 	

analyse: $(COMMON) analyse.o
	 $(CXX) -o $(EXEDIR)/$@ $(COMMON) analyse.o $(LIBS)

clean	:
	$(RM) $(GARBAGE)

