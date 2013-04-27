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

GARBAGE      = *.o $(EXEDIR)/mapbinaryWheels

SOGARBAGE    = *.so

#################
##Dependencies
# Linux
ifeq "$(UNAME)" "Linux"
RANLIB       = ranlib
CXXFLAGS    += -I$(INCDIR) $(ROOTCFLAGS)
LINKFLAGS    =
endif

# MAC OSX
ifeq "$(UNAME)" "Darwin"
RANLIB       = ranlib -s
#CXXFLAGS   += -Wunreachable-code
CXXFLAGS    += -I$(INCDIR) $(ROOTCFLAGS)
LINKFLAGS    = -Xlinker -flat_namespace -bind_at_load
endif

##Libraries
LIBS       += $(ROOTLIBS)

OBJSONE    = mapbinaryWheels.o

all : mapbinaryWheels

%.o : %.C 
	$(CXX) $(CXXFLAGS) -c $< 	

mapbinaryWheels: $(OBJSONE)
	 $(CXX) -o $(EXEDIR)/$@ $(OBJSONE) $(LINKFLAGS) $(LIBS)

clean	:
	$(RM) $(GARBAGE)

cleanall:
	$(RM) $(GARBAGE) $(SOGARBAGE)
