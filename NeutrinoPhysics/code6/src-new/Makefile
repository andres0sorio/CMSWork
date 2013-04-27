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

GSLPATH      =$(GSLLOCATION)
GSLINC       =$(shell $(GSLPATH)/bin/gsl-config --cflags)
GSLLIB       =$(shell $(GSLPATH)/bin/gsl-config --libs)

INCDIR       = .
SRCDIR       = .
LIBDIR       = .
EXEDIR       = ../bin

GARBAGE      = *.o $(EXEDIR)/evalxsec.exe

SOGARBAGE    = *.so

CXXFLAGS    += -I$(INCDIR) $(ROOTCFLAGS) $(GSLINC)
LINKFLAGS    =

##Libraries
LIBS       += $(ROOTLIBS) -lMinuit -lMathCore -lMathMore -lXMLParser $(GSLLIB)

OBJS   = Graphics.o Derivatives.o nuN_interpxsec.o main.o

all : evalxsec.exe

%.o : %.C
	$(CXX) $(CXXFLAGS) -c $< 	

evalxsec.exe: $(OBJS)
	 $(CXX) -o $(EXEDIR)/$@ $(OBJS) $(LINKFLAGS) $(LIBS)

clean	:
	$(RM) $(GARBAGE)

cleanall:
	$(RM) $(GARBAGE) $(SOGARBAGE)
