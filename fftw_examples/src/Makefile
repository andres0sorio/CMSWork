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

INCDIR       = .
SRCDIR       = .
LIBDIR       = .
EXEDIR       = ../exe

GARBAGE      = *.o $(EXEDIR)/ex1 $(EXEDIR)/rpcanalysis \
	$(EXEDIR)/extract $(EXEDIR)/simulate $(EXEDIR)/simulate-sw \
	$(EXEDIR)/ex2

SOGARBAGE    = *.o *.so

RANLIB       = ranlib
CXXFLAGS    += -I$(INCDIR) $(ROOTCFLAGS) -I/HEPsw/fftw/include

LINKFLAGS    =

LIBS        += $(ROOTLIBS) -lMathCore -L/HEPsw/fftw/lib -lfftw3


all : ex1 ex2 rpcanalysis simulate extract simulate-sw

%.o : %.c
	$(CXX) $(CXXFLAGS) -c $< 	

ex1:    Data.o example1.o
	$(CXX) -o $(EXEDIR)/$@ Data.o example1.o $(LINKFLAGS) $(LIBS)

ex2:    Data.o example2.o
	$(CXX) -o $(EXEDIR)/$@ Data.o example2.o $(LINKFLAGS) $(LIBS)

extract: extract.o
	$(CXX) -o $(EXEDIR)/$@ extract.o $(LINKFLAGS) $(LIBS)

simulate: simulate.o
	$(CXX) -o $(EXEDIR)/$@ simulate.o $(LINKFLAGS) $(LIBS)

simulate-sw: simulate-sinewave.o
	$(CXX) -o $(EXEDIR)/$@ simulate-sinewave.o $(LINKFLAGS) $(LIBS)

rpcanalysis: Data.o rpcanalysis.o
	$(CXX) -o $(EXEDIR)/$@ Data.o rpcanalysis.o $(LINKFLAGS) $(LIBS)

clean	:
	$(RM) $(GARBAGE)

cleanall:
	$(RM) $(GARBAGE) $(SOGARBAGE)
