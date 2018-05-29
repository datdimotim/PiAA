#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <utility>
#include <vector>
#include "Node.h"
#include "Rib.h"
#include "Methods.h"

using namespace std;

int main()
{
	ifstream fin("Test.txt");
	string Text;//текст
	int Number;//количество строк
	string CurrentLine;//текущая строка
	Node* Start = new Node(NULL);//начальная вершина
	vector<Node*> MyGraph;//содержатся все вершны графа, кроме начальной
	vector<pair<int, int>*> Answer;//для сохранения ответа

	fin >> Text >> Number;
	cout << Text << endl << Number << endl;
	for (int i = 0; i < Number; i++) {
		fin >> CurrentLine;
		cout << CurrentLine << endl;
		ProcessingData(i, CurrentLine, *Start, MyGraph);//вызываем функцию построения дерева
	}

	if((!MyGraph.empty())&&(!Text.empty())){
		setSuffixLinks(MyGraph, *Start);//устанавливаем суффиксные ссылки

		algorithmAhoCorasick(*Start, Text, Answer);

		sort(Answer.begin(), Answer.end(), [](pair<int, int>* a, pair<int, int>* b) {//сортируем по возрастанию длин строк
			if (a->first == b->first)
				return a->second < b->second;
			return a->first < b->first;
		});

		for (int i = 0; i < Answer.size(); i++)
			cout << Answer[i]->first << " " << Answer[i]->second << endl;
	}
    return 0;
}