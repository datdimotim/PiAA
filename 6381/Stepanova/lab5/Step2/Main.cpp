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
	string CurrentLine;//текущая строка
	char Joker;
	Node* Start = new Node(NULL);//начальная вершина
	vector<Node*> MyGraph;//содержатся все вершны графа, кроме начальной
	vector<int> Answer;//для сохранения ответа
	int SubstringNumber = 0;

	fin >> Text>>CurrentLine>>Joker;
	cout << Text << endl << CurrentLine << endl<<Joker<<endl;
	
	if ((Text.size() >= CurrentLine.size())&&(!Text.empty())&&(!CurrentLine.empty())){
		SubstringNumber=ProcessingData(Joker, CurrentLine, *Start, MyGraph);//вызываем функцию построения дерева

		if (MyGraph.size() == 0) {
			for (int i = 0; i <= Text.size() - CurrentLine.size(); i++)
				cout << i +1<< endl;
		}
		else {
			setSuffixLinks(MyGraph, *Start);//устанавливаем суффиксные ссылки
			algorithmAhoCorasick(*Start, Text, SubstringNumber, Answer);

			sort(Answer.begin(), Answer.end(), [](int a, int b) {//сортируем по возрастанию длин строк
				return a < b;
			});

			for (int i = 0; i < Answer.size(); i++)
				cout << Answer[i] + 1 << endl;
		}
	}
    return 0;
}