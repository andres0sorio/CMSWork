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
EXEDIR       = ../exe

GARBAGE      = *.o $(EXEDIR)/analyze $(EXEDIR)/getRates $(EXEDIR)/simulate $(EXEDIR)/testRates

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

OBJ1   = HistoRates.o TtuRates.o main.o

OBJ2   = simulate.o

OBJ3   = TrigRates.o test.o

OBJ4   = TrigRates.C HistoRates.C GuiHistoRates.C TtuRates.C getRates.C

all : analyze simulate testRates getRates

%.o : %.C
	$(CXX) $(CXXFLAGS) -c $< 	

analyze: $(OBJ1)
	 $(CXX) -o $(EXEDIR)/$@ $(OBJ1) $(LINKFLAGS) $(LIBS)

simulate: $(OBJ2)
	 $(CXX) -o $(EXEDIR)/$@ $(OBJ2) $(LINKFLAGS) $(LIBS)

testRates: $(OBJ3)
	 $(CXX) -o $(EXEDIR)/$@ $(OBJ3) $(LINKFLAGS) $(LIBS)

getRates: $(OBJ4)
	rootcint -f guiDict.C -c GuiHistoRates.h guiLinkDef.h
	g++ `root-config --cflags --glibs` -o $(EXEDIR)/$@ guiDict.C $(OBJ4)


clean	:
	$(RM) $(GARBAGE)

cleanall:
	$(RM) $(GARBAGE) $(SOGARBAGE)
