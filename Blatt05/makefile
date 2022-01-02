CXX=g++
CXXFLAGS=--std=c++14
CXXFLAGS+=-Wall
CXXFLAGS+=-fPIC
CXXFLAGS+=-g
CXXFLAGS+=-DNDEBUG
CXXFLAGS+=-DDEFRAG20
CXXFLAGS += $(includes)

includes=-I./include
srcdir=./src/ringbuffer

testsrc=./tests/ringbuffer.cpp $(srcdir)/*.c
TESTLIBS=-lgtest -lgtest_main -pthread

all:
	mkdir -p $(srcdir)/bin
	$(CXX) $(CXXFLAGS) $(src) -o $(srcdir)/bin/ringbuffer

install: all
	mkdir -p ./bin
	cp $(srcdir)/bin/ringbuffer ./bin/ringbuffer

test:
	$(CXX) $(CXXFLAGS) $(testsrc) -o ringbuffer_test $(TESTLIBS)

run: install
	$(srcdir)/bin/ringbuffer

doc:
	doxygen doxygen.config

.PHONY: clean

clean:
	rm -f $(srcdir)/bin -r
	rm -f ringbuffer_test

distclean: clean
	rm -fr ./bin ./lib ./doc

