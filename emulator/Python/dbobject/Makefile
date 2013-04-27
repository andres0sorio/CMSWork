SHELL = /bin/sh
UNAME = $(shell uname)

BOOSTDIR     = $(BOOSTPATH)
BOOSTVERSION = $(BOOSTVER)

#.................................................................

CXX          = g++
RM           = rm -f 
AR	     = ar cru

CXXFLAGS     = -O0 -g -Wall -fPIC

INCDIR       = .
SRCDIR       = .
LIBDIR       = ../libs
EXEDIR       = .
GARBAGE      = *.o *.so

# Special dependencies - Scientific Linux

ifeq "$(ISSL4)" "yes"
CXXFLAGS    += -I$(INCDIR) -I$(SWPATH)/python/2.4.2-cms2/include/python2.4 -I../include/boost-$(BOOSTVERSION)
LIBS        += -L../libs -lboost_python-gcc34-mt-$(BOOSTVERSION)
else
CXXFLAGS    += -I$(INCDIR) -I/usr/include/python2.5 -I$(BOOSTDIR)/include/boost-$(BOOSTVERSION)
LIBS        += -L$(BOOSTDIR)/lib -lboost_python-gcc42-mt-$(BOOSTVERSION)
endif

OBJSA   = RBCBoardConfig.o TTUBoardConfig.o DBObject_wrapper.o

all : test

%.o : %.cc
	$(CXX) $(CXXFLAGS) -c $< 	

test: $(OBJSA)
	$(CXX) -shared -o DBObject_wrapper.so $(OBJSA) $(LINKFLAGS) $(LIBS)
	cp DBObject_wrapper.so $(LIBDIR)/DBObject_wrapper.so

clean		:
	$(RM) $(GARBAGE)

