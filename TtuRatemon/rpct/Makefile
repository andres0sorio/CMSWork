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

GARBAGE      = *.o $(EXEDIR)/analyze

SOGARBAGE    = *.so

#################
##Dependencies
# Linux
ifeq "$(UNAME)" "Linux"
RANLIB       = ranlib
CXXFLAGS    += -I$(INCDIR) $(ROOTCFLAGS) -I$(GSLINC) -I$(CLHEPINC)
LINKFLAGS    =
endif

##Libraries
LIBS       += $(ROOTLIBS) -lMinuit -lMathCore -lMathMore

OBJ1   = TTUStatisticDiagManager.o main.o

all : analyze

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< 	

analyze: $(OBJ1)
	 $(CXX) -o $(EXEDIR)/$@ $(OBJ1) $(LINKFLAGS) $(LIBS)

clean	:
	$(RM) $(GARBAGE)

cleanall:
	$(RM) $(GARBAGE) $(SOGARBAGE)
