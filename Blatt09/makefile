CXX=g++
CXXFLAGS=--std=c++14
CXXFLAGS+=-Wall
CXXFLAGS += $(INCLUDES)
INCLUDES = -I./include
SRCDIR=./src/
SRC = ./src/*.cpp

all: build	

build:
	mkdir -p $(SRCDIR)/bin
	$(CXX) $(CXXFLAGS) -o $(SRCDIR)/bin/binary $(SRC)

install: all
	mkdir -p ./bin
	cp $(SRCDIR)/bin/binary ./bin/server

run: install
	./bin/server www-path 8080 daemon

doc:
	doxygen doxygen.config

.PHONY: clean distclean

clean:
	rm ./bin $(SRCDIR)/bin -rf

distclean: clean
	rm -fr ./bin ./lib ./doc