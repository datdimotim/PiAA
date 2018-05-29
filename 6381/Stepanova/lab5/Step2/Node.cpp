#include "Node.h"

Node::Node(Node* cf){
	ToReturn = NULL;
	CameFrom = cf;
}

Node::~Node(){
}

void Node::setFinal(int end) {
	Final.push_back(end);
}

Rib* Node::findWay(char symbol) {
	
	if (!ToGo.empty()) {
		for (int i = 0; i < ToGo.size(); i++) {
			if (ToGo[i]->getName() == symbol)
				return ToGo[i];
		}
	}

	return NULL;
}

std::string& Node::getLine() {
	return Line;
}

void Node::setLine(std::string ToAdd) {
	Line = ToAdd;
}

void Node::setToReturn(Node* ret) {
	ToReturn = ret;
}

Node* Node::getToReturn() {
	return ToReturn;
}

Node* Node::getCameFrom() {
	return CameFrom;
}

char Node::lastSymbol() {
	if (!Line.empty())
		return Line[Line.size() - 1];
	else
		return '\0';
}

void Node::addToGo(Rib* New) {
	ToGo.push_back(New);
}

int Node::getFinal(int index) {
	if (index<Final.size()&&index>=0) {
		return Final[index];
	}
	else
		return -1;
}

int Node::FinalSize() {
	return Final.size();
}