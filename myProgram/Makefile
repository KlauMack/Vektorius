CXX = g++
CC = gcc

all:	main.o student.o
	g++ main.o student.o -o tipas

main.o: main.cpp functions.h Vector.h
	g++ -c main.cpp

student.o: student.cpp  student.h
	g++ -c student.cpp

test:	all
	./tipas

clean:
	rm -f *.o tipas