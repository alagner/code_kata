CC=gcc
CPP=g++

DEPS = THashtable.hpp
OBJ = hashtable_test.o
CFLAGS=
CPPFLAGS= -ggdb3 -std=c++14
LIBS = -lboost_unit_test_framework

%.o :  %.cc $(DEPS)
	$(CPP) -c -o $@ $< $(CFLAGS) $(CPPFLAGS)

test: $(OBJ)
	g++ -o $@ $^ $(CPPFLAGS) $(LIBS)

all: test

.PHONY: clean

clean:
	rm -rf *.o test



