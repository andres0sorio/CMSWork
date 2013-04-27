SHELL = /bin/sh
UNAME = $(shell uname)

# Root variables
ROOTCFLAGS    = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOTLIBS      = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --libs) 
ROOTGLIBS     = -L$(ROOTSYS)/lib $(shell $(ROOTSYS)/bin/root-config --glibs)
LHAPDFCFLAGS  = -L$(LHAPDFLOCATION)/lib $(shell $(LHAPDFLOCATION)/bin/lhapdf-config --cppflags)
LHAPDFLDFLAGS = -L$(LHAPDFLOCATION)/lib $(shell $(LHAPDFLOCATION)/bin/lhapdf-config --ldflags)

HEPMCCFLAGS   = -I$(HEPMCLOCATION)/include
PYTHIACFLAGS  = -I$(PYTHIA8)/include 

HEPMCLDFLAGS   = -L$(HEPMCLOCATION)/lib -lHepMC -lHepMCfio
PYTHIALDFLAGS  = -L$(PYTHIA8)/lib -lpythia8 -llhapdfdummy -lhepmcinterface \
		-L$(PYTHIA6)/lib -lPythia6

##	-L$(PYTHIA6)/lib -lPythia6

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

CXXFLAGS    += -I$(INCDIR) $(ROOTCFLAGS) $(HEPMCCFLAGS) $(PYTHIACFLAGS) $(LHAPDFCFLAGS)
LINKFLAGS   += -lgfortran 

##Libraries

LIBS       += $(ROOTLIBS) -lMinuit -lMathCore -lMathMore -lXMLParser $(LHAPDFLDFLAGS)
LIBS       += $(HEPMCLDFLAGS) $(PYTHIALDFLAGS)

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
