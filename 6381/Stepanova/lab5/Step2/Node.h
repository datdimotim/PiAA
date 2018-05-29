#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "Rib.h"

class Rib;

class Node
{
private:
	std::vector<int> Final;//номер строки, для которой этот узел последний
	std::vector<Rib*> ToGo;//ребра, которые выходят из данной вершины
	Node* ToReturn;//cуффиксные ссылки
	Node* CameFrom;//откуда пришли
	std::string Line;//строка, которая может получится
public:
	Node(Node* cf);
	~Node();
	void setFinal(int end);
	Rib* findWay(char symbol);
	std::string& getLine();
	void setLine(std::string ToAdd);
	void setToReturn(Node* ret);
	Node* getToReturn();
	Node* getCameFrom();
	char lastSymbol();
	void addToGo(Rib* New);
	int FinalSize();
	int getFinal(int index);
};