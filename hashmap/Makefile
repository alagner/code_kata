CC=gcc
CXX=g++

CDEFS=
CXXDEFS=-DADD_EXTRA_TEST_GETTERS
DEPS = THashtable.hpp
OBJ = hashtable_test.o
CFLAGS=
CXXFLAGS= -ggdb3 -std=c++14 $(CXXDEFS)
LIBS = -lboost_unit_test_framework

%.o :  %.cc $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS) $(CXXFLAGS)

test: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

all: clean test

.PHONY: clean

clean:
	rm -rf *.o test



