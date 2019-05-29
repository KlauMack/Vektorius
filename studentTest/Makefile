CXX = g++
CC = gcc

all:	vector.o student.o
	g++ vector.o student.o -o vector

vector.o: vector.cpp vector.h
	g++ -c vector.cpp

student.o: student.cpp student.h
	g++ -c student.cpp

test:	all
	./vector

clean:
	rm -f *.o vector