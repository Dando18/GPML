CC = g++
HEADERS = ../include
FLAGS = -std=c++11 -O3 -I $(HEADERS)/
TARGETS = matrix_test

all: matrix_test

matrix_test: matrix_test.cpp $(HEADERS)/Matrix.hpp
	$(CC) $(FLAGS) -o $@ $<

clean:
	rm -rf *.o $(TARGETS)
