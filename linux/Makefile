CC=gcc
CPP=g++

CDEFS=
CPPDEFS=
DEPS = 
OBJ = mbr_reader.o
CFLAGS= -ggdb3 -std=gnu11 $(CDEFS) -Wextra -pedantic -I.
CPPFLAGS= -ggdb3 -std=c++14 $(CPPDEFS)
LIBS = 

%.o :  %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

mbr_reader: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

all: clean test

.PHONY: clean

clean:
	rm -rf *.o mbr_reader



