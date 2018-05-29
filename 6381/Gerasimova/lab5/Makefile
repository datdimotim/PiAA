all: aho joker

aho: lr5_1.o
	g++ lr5_1.o -o aho -std=c++11
joker: lr5_2.o
	g++ lr5_2.o -o joker -std=c++11
lr5_1.o: lr5_1.cpp
	g++ -c lr5_1.cpp -std=c++11
lr5_2.o: lr5_2.cpp
	g++ -c lr5_2.cpp -std=c++11
