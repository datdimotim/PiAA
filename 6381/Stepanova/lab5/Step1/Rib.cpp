#include "Rib.h"

Rib::Rib(char name, Node* begin, Node* end){
	Name = name;
	Begin = begin;
	End = end;
}

Rib::~Rib(){
}

Node* Rib::getEnd() {
	return End;
}

char Rib::getName() {
	return Name;
}