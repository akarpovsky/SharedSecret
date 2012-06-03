IDIR=include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR=lib

LIBS=-lm

_DEPS= cmdline.h imageLoader.h messages.h distribution.h gauss.h utils.h
DEPS=$(patsubst %, $(IDIR)/%,$(_DEPS))

_OBJ= main.o cmdline.o imageLoader.o distribution.o gauss.o utils.o
OBJ=$(patsubst %, $(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
			$(CC) -c -o $@ $< $(CFLAGS)

shasec: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) 

%.o: %.c $(DEPS) $(CC) -c -o $@ $< $(LIBS)

.PHONY: clean

clean: 
	rm -f $(ODIR)/*.o *~ core $(INCDIR) /*~