all: lab4_1 lab4_2

lab4_1: lab4_1.o
	g++ lab4_1.o -o lab4_1 -std=c++11
lab4_2: lab4_2.o
	g++ lab4_2.o -o lab4_2 -std=c++11
lab4_1.o: lab4_1.cpp
	g++ -c lab4_1.cpp -std=c++11
lab4_2.o: lab4_2.cpp
	g++ -c lab4_2.cpp -std=c++11