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
LIBDIR       = .
EXEDIR       = .

GARBAGE      = *.o $(EXEDIR)/checkdata

#.............................................................................
# Special dependencies
# Linux
ifeq "$(UNAME)" "Linux"
RANLIB       = ranlib
CXXFLAGS    += -I$(INCDIR) $(ROOTCFLAGS)
LINKFLAGS    =
endif

#Libraries
LIBS       += $(ROOTLIBS)

COMMON    = checkdata.o

all : checkdata

%.o : %.C 
	$(CXX) $(CXXFLAGS) -c $< 	

checkdata: $(COMMON)
	 $(CXX) -o $(EXEDIR)/$@ $(COMMON) $(LINKFLAGS) $(LIBS)
	 $(RM) $(COMMON)

clean	:
	$(RM) $(GARBAGE)

cleanall:
	$(RM) $(GARBAGE) $(SOGARBAGE)
