CXX = g++
CC = gcc

all:	vector.o
	g++ vector.o -o vector

vector.o: vector.cpp vector.h
	g++ -c vector.cpp

test:	all
	./vector

clean:
	rm -f *.o vector