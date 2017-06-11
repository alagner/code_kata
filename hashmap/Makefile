CC=gcc
CPP=g++

CDEFS=
CPPDEFS=-DADD_EXTRA_TEST_GETTERS
DEPS = THashtable.hpp
OBJ = hashtable_test.o
CFLAGS=
CPPFLAGS= -ggdb3 -std=c++14 $(CPPDEFS)
LIBS = -lboost_unit_test_framework

%.o :  %.cc $(DEPS)
	$(CPP) -c -o $@ $< $(CFLAGS) $(CPPFLAGS)

test: $(OBJ)
	g++ -o $@ $^ $(CPPFLAGS) $(LIBS)

all: clean test

.PHONY: clean

clean:
	rm -rf *.o test



