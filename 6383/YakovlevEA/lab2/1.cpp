#include <iostream> 
#include <vector> 
//#include <fstream> 
#include <stack> 

using namespace std;

class Edge
{
	char startOfEdge;
	char endOfEdge;
	double length;

public:

	char getStartOfEdge()
	{
		return startOfEdge;
	}

	char getEndOfEdge()
	{
		return endOfEdge;
	}

	double getlength()
	{
		return length;
	}

	Edge(char startOfEdge, char endOfEdge, double length) : startOfEdge(startOfEdge), endOfEdge(endOfEdge), length(length) {}

};

bool isTopInList(vector<char> tops, char startOfEdge)
{
	for (int i = 0; i < tops.size(); i++)
	{
		if (tops[i] == startOfEdge) return true;
	}
	return false;
}

bool isTopInList_forEnd(vector<char> tops, char endOfEdge)
{
	for (int i = 0; i < tops.size(); i++)
	{
		if (tops[i] == endOfEdge) return true;
	}
	return false;
}

int getIndex(vector<char> tops, char startOfEdge)
{
	for (int i = 0; i < tops.size(); i++)
	{
		if (tops[i] == startOfEdge)
			return i;
	}

}

void printStack(stack <char> stack)
{
	char m = stack.top();
	stack.pop();
	if (!stack.empty())
	{
		printStack(stack);
	}
	cout << m;// « " " ; 
}

bool way = false;
void findWay(vector<char> tops, vector<vector<Edge> > edges, int startIndex, char end, stack <char> stack)
{
	if (!edges[startIndex].empty())
	{
		char endLocal = edges[startIndex][0].getEndOfEdge();
		stack.push(endLocal);
		if (endLocal != end)
		{
			edges[startIndex].erase(edges[startIndex].begin());
			findWay(tops, edges, getIndex(tops, endLocal), end, stack);
			stack.pop();
			if (way == false)
			{
				findWay(tops, edges, startIndex, end, stack);
			}
		}
		else
		{
			printStack(stack);
			cout << endl;
			way = true;
		}
	}
}

int main()
{
	//ifstream fin("piaa2.txt"); 

	char start;
	char end;

	cin >> start;
	cin >> end;

	char startOfEdge;
	char endOfEdge;
	double length;

	vector<char> tops;
	vector<vector<Edge> > edges;

	while (cin >> startOfEdge && cin >> endOfEdge && cin >> length)
	{

		if (!isTopInList(tops, startOfEdge))
		{
			tops.push_back(startOfEdge);
			vector<Edge> a;
			edges.push_back(a);

		}

		if (!isTopInList_forEnd(tops, endOfEdge))
		{
			tops.push_back(endOfEdge);
			vector<Edge> a;
			edges.push_back(a);
		}

		edges[getIndex(tops, startOfEdge)].push_back(Edge(startOfEdge, endOfEdge, length));
	}

	stack <char> stack;
	stack.push(start);

	if (edges.size() > 1)
		for (int i = 0; i < edges.size(); i++)
		{
			if (edges[i].size() > 1)
				for (int j = 0; j < edges[i].size() - 1; j++)
				{
					for (int k = 0; k < edges[i].size(); k++)
					{
						if (edges[i][j].getlength() > edges[i][j + 1].getlength())
						{
							Edge e = edges[i][j];
							edges[i][j] = edges[i][j + 1];
							edges[i][j + 1] = e;
						}
					}
				}
		}

	/*for (int i = 0; i < edges.size(); i++)
	{
	for (int j = 0; j < edges[i].size(); j++)
	{
	cout « edges[i][j].getStartOfEdge() « " " « edges[i][j].getEndOfEdge() « " " « edges[i][j].getlength() « endl;
	}
	}*/

	findWay(tops, edges, getIndex(tops, start), end, stack);
	//fin.close(); 

	return 0;
}