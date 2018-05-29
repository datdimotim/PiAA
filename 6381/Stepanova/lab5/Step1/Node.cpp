#include "Node.h"

Node::Node(Node* cf){
	Final = -1;
	ToReturn = NULL;
	CameFrom = cf;
}

Node::~Node(){
}

int Node::getFinal() {
	return Final;
}

void Node::setFinal(int end) {
	Final = end;
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