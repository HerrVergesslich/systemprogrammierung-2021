CXX=g++
CXXFLAGS=--std=c++14
CXXFLAGS+=-Wall
CXXFLAGS += $(INCLUDES)

INCLUDES=-I./include
SRCDIR=./src/smartpointer

TESTDIR = ./tests/smartpointer

all:
	@echo "###################################################################"
	@echo
	@echo "Nichts zu tun, da in Programm keine main()-Funktion present ist."
	@echo
	@echo "###################################################################"
#	$(CXX) $(CXXFLAGS) $(SRCDIR)/**/*.cpp -o $(srcdir)/bin/ringbuffer

install: all
#	mkdir -p ./bin
#	cp $(SRCDIR)/bin/smartpointer ./bin/smartpointer

test:
	make -C $(TESTDIR) abgabe

run: install
#	$(SRCDIR)/bin/smartpointer

doc:
	doxygen doxygen.config

.PHONY: clean

clean:
	make -C $(TESTDIR) clean
	rm -fr $(SRCDIR)/bin

distclean: clean
	rm -fr ./doc