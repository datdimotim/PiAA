#include "Methods.h"

int ProcessingData(char Joker, std::string& CurrentLine, Node& Start, std::vector<Node*>& MyGraph) {
	Node* currentNode = &Start;
	Rib* currentRib = NULL;
	std::string currentString;
	int SubstringNumber = 0;
	
	for (int i = 0; i < CurrentLine.size(); i++) {//проходим по всем символам и строим дерево
		if (CurrentLine[i] != Joker) {
			currentString = currentString + CurrentLine[i];
			currentRib = currentNode->findWay(CurrentLine[i]);//ищем ребро
			if (currentRib != NULL) {//идём по уже существующему пути
				currentNode = currentRib->getEnd();
			}
			else {
				Node* newNode = new Node(currentNode);//создаём новую вершину
				MyGraph.push_back(newNode);//добавляем в граф
				currentRib = new Rib(CurrentLine[i], currentNode, newNode);//создаём новое ребро
				currentNode->addToGo(currentRib);//добавляем ребро
				currentNode = newNode;//переходим на следующую вершину
				currentNode->setLine(currentString);//записываем
			}
		}
		else {//если наткнулись на джокер
			if (!currentString.empty()) {//если нашли новую подстроку
				SubstringNumber++;
				currentNode->setFinal(i-currentString.size());//в последнем обозначаем конец текущего слова
				currentString.clear();//очищаем строку
				currentNode = &Start;//переходим в начало
			}
		}
	}

	if (!currentString.empty()) {//если нашли новую подстроку
		SubstringNumber++;
		currentNode->setFinal(CurrentLine.size()-currentString.size());//в последнем обозначаем конец текущего слова
		currentString.clear();//очищаем строку
		currentNode = &Start;//переходим в начало
	}
	return SubstringNumber;
}

void setSuffixLinks(std::vector<Node*>& MyGraph, Node& Start) {
	Node* Parent = &Start;
	char Name;

	Start.setToReturn(&Start);

	std::sort(MyGraph.begin(), MyGraph.end(), [](Node* a, Node* b) {//сортируем по возрастанию длин строк
		return a->getLine().size() < b->getLine().size();
	});

	for (int i = 0; i < MyGraph.size(); i++) { //ищем суффиксные ссылки для каждого
		Parent = MyGraph[i]->getCameFrom()->getToReturn();//получили родителя, переходим на максимальную суффиксную ссылку родителя
		Name = MyGraph[i]->lastSymbol();

		while ((Parent != &Start) && (Parent->findWay(Name) == NULL)) {
			Parent = Parent->getToReturn();
		}

		if (Parent == &Start) {//выход по первому условию
			if (Parent->findWay(Name) == NULL) 
				MyGraph[i]->setToReturn(&Start);//ссылка - корень
			else {
				if (Parent->findWay(Name)->getEnd() == MyGraph[i]) 
					MyGraph[i]->setToReturn(&Start);//ссылка - корень
				else 
					MyGraph[i]->setToReturn(Parent->findWay(Name)->getEnd());
			}
		}

		else{//выход по второму условию
			MyGraph[i]->setToReturn(Parent->findWay(Name)->getEnd());
		}
	}
}

void algorithmAhoCorasick(Node& Start, std::string& Text, int SubstringNumber, std::vector<int>& Answer) {
	Node* currentNode = &Start;
	std::vector<int> Mass(Text.size(), 0);

	for (int i = 0; i < Text.size(); i++) {

		while ((currentNode != &Start) && (currentNode->findWay(Text[i]) == NULL)) {//пока не найдём куда перейти или не вернёмся в вершину
			currentNode = currentNode->getToReturn();//переходим по суффиксной ссылке
		}

		if (currentNode == &Start) {//вышли по первому условию
			if (currentNode->findWay(Text[i]) != NULL) {//если существует путь из вершины
				currentNode=currentNode->findWay(Text[i])->getEnd();//переходим по этому пути
				if (currentNode->FinalSize() > 0) {//если конечная вершина
					int size = i - currentNode->getLine().size() + 1;
					for (int k = 0; k < currentNode->FinalSize(); k++) {
						if ((size- currentNode->getFinal(k)>=0)&&(size-currentNode->getFinal(k)<Text.size()))
							Mass[size - currentNode->getFinal(k)]++;//увеличиваем количество подстрок на 1
					}
				}
			}
		}
		else {//вышли по второму условию
			currentNode = currentNode->findWay(Text[i])->getEnd();//переходим на следующую вершину
			Node* temporaryNode = currentNode;//заводим временную переменную

			while (temporaryNode != &Start) {//пока не дойдём до вершины
				if (temporaryNode->FinalSize() > 0) {//если конечная вершина
					int size = i - temporaryNode->getLine().size() + 1;
					for (int k = 0; k < temporaryNode->FinalSize(); k++) {
						if ((size - temporaryNode->getFinal(k) >= 0) && (size - temporaryNode->getFinal(k)<Text.size()))
							Mass[size - temporaryNode->getFinal(k)]++;//увеличиваем количество подстрок на 1
					}
				}
	 		temporaryNode = temporaryNode->getToReturn();//переходим по следующей суффиксной ссылке
	 		}
		}
	}

	for (int i = 0; i < Mass.size(); i++) {
		if (Mass[i] >= SubstringNumber)
			Answer.push_back(i);
	}
}