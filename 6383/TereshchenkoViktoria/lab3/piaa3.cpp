// piaa3
/*Найти максимальный поток в сети, а также фактическую величину потока, протекающего через каждое ребро, используя алгоритм Форда-Фалкерсона.*/
// ожидается выведение в том числе и ребер с нулевым потоком


#include <iostream>
#include <vector>
#include <fstream>
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

    double getLength()
    {
        return length;
    }
    
    Edge(char startOfEdge, char endOfEdge, double length) : startOfEdge(startOfEdge), endOfEdge(endOfEdge), length(length) {}

    void setLength(double length)
    {
        this->length = length;
    }
}; 

bool isTopInList(const vector<char> &tops, char startOfEdge)
{
    for (int i = 0; i < tops.size(); i++)
    {
        if (tops[i] == startOfEdge) return true;
    }
    return false;
}

bool isTopInList(vector<Edge> &c, char d)
{
    for (int i = 0; i < c.size(); i++)
    {
        if (c[i].getEndOfEdge() == d) return true;
    }
    return false;
}

int getIndex(const vector<char> &tops, char startOfEdge)
{
    for (int i = 0; i < tops.size(); i++)
    {
        if (tops[i] == startOfEdge) return i;
    }
}

int getIndexOfTopInList(vector<Edge> &edges, char top) 
{ 
    for (int i = 0; i < edges.size(); i++) 
    { 
        if (edges[i].getEndOfEdge() == top) return i; 
    } 
} 
vector<char> tops; 
vector<vector<Edge>> graph; 
vector<vector<Edge>> edges; 
bool flow = false; 
vector <double> storage; 
vector <char> toops;
int maxFlow = 0; 
int flowSize = 0; 

bool consistElement(char elem) 
{ 
    for (int i = 0; i < toops.size(); i++) 
    { 
        if (toops[i] == elem) return true; 
    } 
    toops.push_back(elem); 
    return false; 
} 

void getMaxFlow() 
{ 
    maxFlow = storage.back(); 
    storage.pop_back(); 
    toops.pop_back();
    while (!storage.empty()) 
    { 
        if (maxFlow > storage.back()) 
        { 
            maxFlow = storage.back(); 
        } 
        storage.pop_back(); 
        toops.pop_back();
    } 
} 

int getPosToInsert(vector<char> b, char elem)
{
	for (int i = 0; i < b.size(); i++)
	{
		if ((int)b[i] > (int)elem)
			return i;
	}
	return -1;
}

int getPosToInsert(vector<Edge> b, char elem)
{
	for (int i = 0; i < b.size(); i++)
	{
		if ((int)b[i].getEndOfEdge() > (int)elem)
			return i;
	}
	return -1;
}

void insertVector(char startOfEdge, char endOfEdge)
{
	if (!isTopInList(tops, startOfEdge))
	{
		vector<Edge> a;
		int posToInsert = getPosToInsert(tops, startOfEdge);
		if (posToInsert != -1)
		{
			tops.insert(tops.begin() + posToInsert, startOfEdge);
			edges.insert(edges.begin() + posToInsert, a);
			graph.insert(graph.begin() + posToInsert, a);
		}
		else
		{
			tops.push_back(startOfEdge);
			edges.push_back(a);
			graph.push_back(a);
		}

	}
	if (!isTopInList(tops, endOfEdge))
	{
		vector<Edge> a;
		int posToInsert = getPosToInsert(tops, endOfEdge);
		if (posToInsert != -1)
		{
			tops.insert(tops.begin() + posToInsert, endOfEdge);
			edges.insert(edges.begin() + posToInsert, a);
			graph.insert(graph.begin() + posToInsert, a);
		}
		else
		{
			tops.push_back(endOfEdge);
			edges.push_back(a);
			graph.push_back(a);
		}
	}

}

vector<vector<Edge>> insertElement(vector<vector<Edge>> e, char startOfEdge, char endOfEdge, double length)
{
	Edge edge(startOfEdge, endOfEdge, length);
	int vectorNumber = getIndex(tops, startOfEdge);
	int posInVector = getPosToInsert(e[vectorNumber], endOfEdge);
	if (posInVector != -1)
	{
		e[vectorNumber].insert(e[vectorNumber].begin() + posInVector, edge);
	}
	else
	{
		e[vectorNumber].push_back(edge);
	}
	return e;
}

bool consistEdge(vector<vector<Edge>> e, char startOfEdge, char endOfEdge) 
{
	int vectorNumber = getIndex(tops, startOfEdge);
	for (int i = 0; i < e[vectorNumber].size(); i++)
	{
		if (e[vectorNumber][i].getEndOfEdge() == endOfEdge)
			return true;
	}
	return false;
}

bool findFlow(const vector<char> &tops, char start, char end) 
{ 
    int pos = getIndex(tops, start); 
    for (int i = 0; i < edges[pos].size(); i++) 
    { 
        if (!consistElement(edges[pos][i].getEndOfEdge())) 
        { 
            storage.push_back(edges[pos][i].getLength()); 
            if (edges[pos][i].getLength() != 0) 
            { 
                if (edges[pos][i].getEndOfEdge() != end) 
                { 
                    flow = findFlow(tops, edges[pos][i].getEndOfEdge(), end); 
                } 
                else 
                { 
                    flow = true; 
                    getMaxFlow(); 
                    flowSize += maxFlow; 
                } 
            } 
            if (flow == true) 
            { 
                edges[pos][i].setLength(edges[pos][i].getLength() - maxFlow); 
                int pos2 = getIndex(tops, edges[pos][i].getEndOfEdge()); 
                int pos3 = getIndexOfTopInList(edges[pos2], edges[pos][i].getStartOfEdge()); 
                edges[pos2][pos3].setLength(edges[pos2][pos3].getLength() + maxFlow); 
                break; 
            } 
            else 
            { 
                storage.pop_back(); 
                toops.pop_back(); 
            } 
        } 
    } 
    return flow; 
} 

int main()
{
    ifstream fin("piaa3.txt");

    int number = 0; 
    char start; 
    char end; 

    fin >> number; 
    fin >> start; 
    fin >> end; 

    char startOfEdge; 
    char endOfEdge; 
    double length; 

    for(int i = 0; i < number; i++) 
    { 
        fin >> startOfEdge; 
        fin >> endOfEdge; 
        fin >> length; 

        insertVector(startOfEdge, endOfEdge);

        graph = insertElement(graph, startOfEdge, endOfEdge, length);
        edges = insertElement(edges, startOfEdge, endOfEdge, length);
    }

    for (int i = 0; i < edges.size(); i++)
	{
		for (int j = 0; j < edges[i].size(); j++)
		{
			if (!consistEdge(edges, edges[i][j].getEndOfEdge(), edges[i][j].getStartOfEdge()))
			{
				edges = insertElement(edges, edges[i][j].getEndOfEdge(), edges[i][j].getStartOfEdge(), 0);
			}
		}
	}

	while (findFlow(tops, start, end))
	{
		flow = false;
	}

	cout << flowSize << endl;

	for (int i = 0; i < graph.size(); i++)
	{
		for (int j = 0; j < graph[i].size(); j++)
		{
			int pos1 = getIndex(tops, graph[i][j].getStartOfEdge());
			int pos2 = getIndexOfTopInList(edges[pos1], graph[i][j].getEndOfEdge());
			if ((graph[i][j].getLength() - edges[pos1][pos2].getLength())>0)
				cout << graph[i][j].getStartOfEdge() << " " << graph[i][j].getEndOfEdge() << " " << graph[i][j].getLength() - edges[pos1][pos2].getLength() << endl;
			else
				cout << graph[i][j].getStartOfEdge() << " " << graph[i][j].getEndOfEdge() << " " << 0 << endl;
		}
	}
    
    fin.close();
    return 0;  
}