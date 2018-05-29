all: lr5_1 lr5_2
lr5_1 : lr5_1 .o
	g++ -std=c++11 lr5_1 .o -o lr5_1  
lr5_2: lr5_2.o
	g++ -std=c++11 lr5_2.o -o lr5_2 
lr5_1 .o: lr5_1 .cpp
	g++ -std=c++11 -c lr5_1 .cpp 
lr5_2.o: lr5_2.cpp
	g++ -std=c++11 -c lr5_2.cpp 
