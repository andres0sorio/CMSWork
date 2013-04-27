SHELL = /bin/sh
UNAME = $(shell uname)

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

GARBAGE      = *.o $(EXEDIR)/run_higssZZ $(EXEDIR)/run_susy

SOGARBAGE    = *.so

#################
RANLIB       = ranlib
CXXFLAGS    += -I$(INCDIR) -I$(PYTHIA8)/include -I$(LHAPDFLOCATION)/include
LINKFLAGS    =

##Libraries
LIBS       +=  -L$(PYTHIA8)/lib/archive -l pythia8 -L$(LHAPDFLOCATION)/lib -lLHAPDF

all : run_higssZZ run_susy

%.o : %.cc 
	$(CXX) $(CXXFLAGS) -c $< 	

run_higssZZ: run_higssZZ.o
	 $(CXX) -o $(EXEDIR)/$@  run_higssZZ.o $(LINKFLAGS) $(LIBS)

run_susy: run_susy.o 
	 $(CXX) -o $(EXEDIR)/$@ run_susy.o $(LINKFLAGS) $(LIBS)

clean	:
	$(RM) $(GARBAGE)

cleanall:
	$(RM) $(GARBAGE) $(SOGARBAGE)

