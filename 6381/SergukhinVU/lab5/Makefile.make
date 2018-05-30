all: lab5_1 lab5_2

lab5_1: lab5_1.o
	g++ lab5_1.o -o lab5_1 -std=c++11
lab5_2: lab5_2.o
	g++ lab5_2.o -o lab5_2 -std=c++11
lab5_1.o: lab5_1.cpp
	g++ -c lab5_1.cpp -std=c++11
lab5_2.o: lab5_2.cpp
	g++ -c lab5_2.cpp -std=c++11