all: Main.o Methods.o Node.o Rib.o 
	g++ Main.o Methods.o Node.o Rib.o -o out -std=c++11
Main.o: Main.cpp Methods.h Node.h Rib.h
	g++ -c Main.cpp -std=c++11
Methods.o: Methods.cpp Methods.h Node.h Rib.h
	g++ -c Methods.cpp -std=c++11	
Node.o: Node.cpp Node.h Rib.h
	g++ -c Node.cpp -std=c++11
Rib.o: Rib.cpp Rib.h Node.h
	g++ -c Rib.cpp -std=c++11