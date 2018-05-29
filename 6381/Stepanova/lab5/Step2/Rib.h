#pragma once
#include"Node.h"

class Node;

class Rib
{
private:
	char Name;//буква
	Node* Begin;//начальная вершина
	Node* End;//конечная вершина
public:
	Rib(char name, Node* begin, Node* end);
	~Rib();
	Node* getEnd();
	char getName();
};