IDIR = include
ODIR = src
BDIR = bin
LDIR = lib
DDIR = doc
CC = gcc
CFLAGS = -ansi -pedantic -Wall -I$(IDIR)
LDLIBS = -lwiringPi
SRC = $(wildcard $(ODIR)/**/.c)
OBJS = $(SRC:.c=.o)

$(ODIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

all: ledanzeige

ledanzeige: $(OBJS)
	@mkdir -p $(ODIR)/build
	@echo "Compiling Files: $^"
	$(CC) $(CFLAGS) $(LDLIBS) $^ -o $(ODIR)/build/$@

install: all
	@echo "Kopiere ausführbare Dateien nach ./bin"
	cp $(ODIR)/build/* $(BDIR)/

test:
	@echo "Not implemented"

run: install

doc: 
	@echo "Not implemented"

.PHONY: clean

clean:
	@echo Entferne alle temp-Files
	@rm -r -f -v $(ODIR)/*.o
	@rm -r -f -v $(ODIR)/build

distclean:
	@echo Entferne alle generierten Ordner: /bin /lib & /doc
	@rm -r -f -v $(BDIR)
	@rm -r -f -v $(LDIR)
	@rm -r -f -v $(DDIR)
