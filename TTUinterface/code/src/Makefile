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
LIBDIR       = ../pyspecs
EXEDIR       = .
GARBAGE      = *.o $(LIBDIR)/*.so $(LIBDIR)/TTUspecs/*.so $(LIBDIR)/RBCspecs/*.so \
	  $(LIBDIR)/*.pyc $(LIBDIR)/TTUspecs/*.pyc $(LIBDIR)/RBCspecs/*.pyc \
	  $(LIBDIR)/GUIstatus/*.pyc

# Special dependencies - Scientific Linux

ifeq "$(ISSL4)" "yes"
CXXFLAGS    += -I$(INCDIR) -I$(SWPATH)/python/2.4.2-cms2/include/python2.4 -I../include/boost-$(BOOSTVERSION)
LIBS        += -L../libs -lboost_python-gcc34-mt-$(BOOSTVERSION)
else
CXXFLAGS    += -I$(INCDIR) -I/usr/include/python2.5 -I$(BOOSTDIR)/include/boost-$(BOOSTVERSION)
LIBS        += -L$(BOOSTDIR)/lib -lboost_python-gcc42-mt-$(BOOSTVERSION)
endif

CMOBJS   = RBCBoardSpecs.o TTUBoardSpecs.o

all : stlsupp ttuspecs rbcspecs

%.o : %.cc
	$(CXX) $(CXXFLAGS) -c $< 	

stlsupp: STLVector_wrapper.o
	$(CXX) -shared -o ../pyspecs/STLvector.so STLVector_wrapper.o $(LINKFLAGS) $(LIBS)

ttuspecs: $(CMOBJS) TTUspecs.o
	$(CXX) -shared -o ../pyspecs/TTUspecs/_TTUspecs.so $(CMOBJS) TTUspecs.o $(LINKFLAGS) $(LIBS)

rbcspecs: $(CMOBJS) RBCspecs.o
	$(CXX) -shared -o ../pyspecs/RBCspecs/_RBCspecs.so $(CMOBJS) RBCspecs.o $(LINKFLAGS) $(LIBS)

clean		:
	$(RM) $(GARBAGE)

