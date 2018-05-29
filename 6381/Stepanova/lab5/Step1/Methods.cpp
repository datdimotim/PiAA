#include "Methods.h"

void ProcessingData(int Number, std::string& CurrentLine, Node& Start, std::vector<Node*>& MyGraph) {
	Node* currentNode = &Start;
	Rib* currentRib = NULL;
	std::string currentString;
	
	for (int i = 0; i < CurrentLine.size(); i++) {//проходим по всем символам и строим дерево
		currentString = currentString + CurrentLine[i];
		currentRib = currentNode->findWay(CurrentLine[i]);//ищем ребро
		if (currentRib!=NULL) {//идём по уже существующему пути
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

	currentNode->setFinal(Number+1);//в последнем обозначаем конец текущего слова
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

void algorithmAhoCorasick(Node& Start, std::string& Text,std::vector<std::pair<int, int>*>& Answer) {
	Node* currentNode = &Start;

	for (int i = 0; i < Text.size(); i++) {

		while ((currentNode != &Start) && (currentNode->findWay(Text[i]) == NULL)) {//пока не найдём куда перейти или не вернёмся в вершину
			currentNode = currentNode->getToReturn();//переходим по суффиксной ссылке
		}

		if (currentNode == &Start) {//вышли по первому условию
			if (currentNode->findWay(Text[i]) != NULL) {//если существует путь из вершины
				currentNode=currentNode->findWay(Text[i])->getEnd();//переходим по этому пути
				if (currentNode->getFinal() > 0) {//если конечная вершина
					std::pair<int, int>* newAnswer = new std::pair<int, int>(i +1, currentNode->getFinal());//то записываем ответ
					Answer.push_back(newAnswer);//раз уже пришли сюда
				}
			}
		}
		else {//вышли по второму условию
			currentNode = currentNode->findWay(Text[i])->getEnd();//переходим на следующую вершину
			Node* temporaryNode = currentNode;//заводим временную переменную

			while (temporaryNode != &Start) {//пока не дойдём до вершины
				if (temporaryNode->getFinal() > 0) {//если это конечная вершина
					std::pair<int, int>* newAnswer = new std::pair<int, int>(i - temporaryNode->getLine().size() + 2, temporaryNode->getFinal());//то записываем ответ
					Answer.push_back(newAnswer);//раз уже пришли сюда
				}
	 			temporaryNode = temporaryNode->getToReturn();//переходим по следующей суффиксной ссылке
	 		}
		}
	}
}