CXX=g++
CXXFLAGS=--std=c++14
CXXFLAGS+=-Wall
CXXFLAGS+=-fPIC
CXXFLAGS+=-g
CXXFLAGS+=-DNDEBUG
CXXFLAGS+=-DDEFRAG20
CXXFLAGS += -I$(includes)

includes=./include
src=./src/ringbuffer/ringbuffer.c

testsrc=./tests/ringbuffer.cpp $(src)
TESTLIBS=-lgtest -lgtest_main -pthread

all:

test:
	$(CXX) $(CXXFLAGS) $(testsrc) -o ringbuffer_test $(TESTLIBS)
