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

GARBAGE      = *.o $(EXEDIR)/test.exe 

SOGARBAGE    = *.so AutoDict_* *.d

CXXFLAGS    += -I$(INCDIR) $(ROOTCFLAGS) $(GSLINC) $(BOOSTINC)
LINKFLAGS    =

##Libraries
LIBS       += $(ROOTLIBS) -lMinuit -lMathCore -lMathMore -lXMLParser $(GSLLIB) \
	-L$(BOOSTPATH)/lib -lboost_program_options

OBJS   = DensityModels.o main.o 

all : test.exe

%.o : %.cc
	$(CXX) $(CXXFLAGS) -c $< 	

test.exe: $(OBJS)
	 $(CXX) -o $(EXEDIR)/$@ $(OBJS) $(LINKFLAGS) $(LIBS)

clean	:
	$(RM) $(GARBAGE)

cleanall:
	$(RM) $(GARBAGE) $(SOGARBAGE)
