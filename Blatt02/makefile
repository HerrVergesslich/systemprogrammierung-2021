IDIR = include
ODIR = src/ledanzeige
BDIR = bin
LDIR = lib
DDIR = doc
CC = gcc
CFLAGS = -ansi -pedantic -Wall -I$(IDIR)
LDLIBS = -lwiringPi
OBJS = $(ODIR:.c=.o)

all: build

$(ODIR)/%.o: %.c
	echo "Creating Object-File: $@"
	$(CC) -c $(CFLAGS) $^ -o $@

build: $(OBJS)
	mkdir $(ODIR)/build
	$(CC) $(CFLAGS) $(LDLIBS) -o $(ODIR)/build/$@

install: all
	echo "Kopiere ausführbare Dateien nach ./bin"
	cp $(ODIR)/build/* $(BDIR)/

test:
	echo "Keine Tests."

run: install

doc: 

.PHONY: clean

clean:
	echo Entferne alle temp-Files
	rm -rf $(ODIR)/*.o
	rm -rf $(ODIR)/build

distclean:
	echo Entferne alle generierten Ordner: /bin /lib & /doc
	rm -r -f $(BDIR)
	rm -r -f $(LDIR)
	rm -r -f $(DDIR)
