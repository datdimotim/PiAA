all: lab1 lab2 clean

lab1: aho-korasik.o 
	g++ aho-korasik.o -o lab

aho-korasik.o: aho-korasik.cpp
	g++ -std=c++11 -c aho-korasik.cpp

lab2: mnog_poisk.o 
	g++ mnog_poisk.o -o lab1

mnog_poisk.o: mnog_poisk.cpp
	g++ -std=c++11 -c mnog_poisk.cpp
		
clean:
	rm -rf *.o lab1
	rm -rf *.o lab2

