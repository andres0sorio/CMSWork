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


INCDIR       = .
SRCDIR       = .
LIBDIR       = .
EXEDIR       = .

GARBAGE      = *.o $(EXEDIR)/evalxsec.exe

SOGARBAGE    = *.so

CXXFLAGS    += -I$(INCDIR) -I$(LHAPDFLOCATION)/include $(ROOTCFLAGS) 
LINKFLAGS    =

##Libraries
LIBS       += $(ROOTLIBS) -lMinuit -lMathCore -lMathMore -L$(LHAPDFLOCATION)/lib -lLHAPDF

OBJS   = nuN_xsec.o main.o

all : evalxsec.exe

%.o : %.C
	$(CXX) $(CXXFLAGS) -c $< 	

evalxsec.exe: $(OBJS)
	 $(CXX) -o $(EXEDIR)/$@ $(OBJS) $(LINKFLAGS) $(LIBS)

clean	:
	$(RM) $(GARBAGE)

cleanall:
	$(RM) $(GARBAGE) $(SOGARBAGE)
