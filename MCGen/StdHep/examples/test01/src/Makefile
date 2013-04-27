SHELL = /bin/sh
UNAME = $(shell uname)

STDHEPLOCATION = /opt/hepsw/stdhep/pro

# Root variables
ROOTCFLAGS    = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --libs) 
ROOTGLIBS     = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --glibs)
LHAPDFCFLAGS  = -L$(LHAPDFLOCATION)/lib $(shell $(LHAPDFLOCATION)/bin/lhapdf-config --cppflags)
LHAPDFLDFLAGS = -L$(LHAPDFLOCATION)/lib $(shell $(LHAPDFLOCATION)/bin/lhapdf-config --ldflags)

STDHEPCFLAGS  = -I$(STDHEPLOCATION)

PYTHIACFLAGS  = -I$(PYTHIA8)/include 

STDHEPLDFLAGS  = -L$(STDHEPLOCATION)/lib -lstdhepC -lstdhep -lFmcfio -lgfortran

PYTHIALDFLAGS  = -L$(PYTHIA8)/lib -lpythia8 -llhapdfdummy 

################
##linux
CXX          = g++
RM           = rm -f 
AR	     = ar cru
--with-momentum=
##Flags
CXXFLAGS     = -O0 -g -Wall -fPIC
#CXXFLAGS     += -D_DEBUG

INCDIR       = .
SRCDIR       = .
LIBDIR       = .
EXEDIR       = ../bin

GARBAGE      = *.o $(EXEDIR)/test.exe 

SOGARBAGE    = *.so

CXXFLAGS    += -I$(INCDIR) $(ROOTCFLAGS) $(STDHEPCFLAGS) $(PYTHIACFLAGS) $(LHAPDFCFLAGS)

##Libraries

LIBS       += $(ROOTLIBS) -lMinuit -lMathCore -lMathMore -lXMLParser $(LHAPDFLDFLAGS)
LIBS       += $(STDHEPLDFLAGS) $(PYTHIALDFLAGS)

OBJS   = main.o

all : test.exe

%.o : %.C
	$(CXX) $(CXXFLAGS)  -c $< 	

test.exe: $(OBJS)
	 $(CXX) -o $(EXEDIR)/$@ $(OBJS) $(LINKFLAGS) $(LIBS)

clean	:
	$(RM) $(GARBAGE)

cleanall:
	$(RM) $(GARBAGE) $(SOGARBAGE)
