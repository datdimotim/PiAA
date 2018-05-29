all: lab3.o 
	g++ lab3.o -o lab3 
lab3.o: lab3.cpp
	g++ -c lab3.cpp