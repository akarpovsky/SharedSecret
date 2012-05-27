IDIR=include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR=lib

LIBS=-lm

_DEPS= cmdline.h imageLoader.h messages.h
DEPS=$(patsubst %, $(IDIR)/%,$(_DEPS))

_OBJ= main.o cmdline.o imageLoader.o
OBJ=$(patsubst %, $(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
			$(CC) -c -o $@ $< $(CFLAGS)

shasec: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(CFLAGS) 

%.o: %.c $(DEPS) $(CC) -c -o $@ $< $(LIBS)

.PHONY: clean

clean: 
	rm -f $(ODIR)/*.o *~ core $(INCDIR) /*~