CXX=g++
CXXFLAGS=--std=c++14
CXXFLAGS+=-Wall
CXXFLAGS += $(INCLUDES)
INCLUDES = -I./include
SRCDIR=./src/$(wildcard *.c)
MAIN = ./src/main

all:
	mkdir -p $(srcdir)/bin
	$(CXX) $(CXXFLAGS) $(src) -o $(MAIN)$(SRCDIR)

install: all
	mkdir -p ./bin
	cp $(MAIN)/bin/main ./bin/main

run: install
	$(MAIN)/bin/main 8080 daemon

doc:
	doxygen doxygen.config

.PHONY: clean distclean

clean:
	rm -f $(MAIN)/bin -r

distclean: clean
	rm -fr ./bin ./lib ./doc