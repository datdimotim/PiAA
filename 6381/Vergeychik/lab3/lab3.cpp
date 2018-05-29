
#include <iostream>
#include <vector>
#include <stack>

class Edge
{

	char start;
	char end;
	double length;

public:
	Edge(char start, char end, double length) : start(start), end(end), length(length) {};
	char getStart()
	{
		return start;
	}
	char getEnd()
	{
		return end;
	}
	double getLength()
	{
		return length;
	}
	void setLength(double length)
	{
		this->length = length;
	}
};

bool isTopInList(const std::vector<char> &tops, char top)
{
	for (int i = 0; i < tops.size(); i++)
	{
		if (tops[i] == top)
		{
			return true;
		}
	}
	return false;
}

bool isTopInList(std::vector<Edge> &e, char g)
{
	for (int i = 0; i < e.size(); i++)
	{
		if (e[i].getEnd() == g)
		{
			return true;
		}
	}
	return false;
}

int getPositionOfTop(const std::vector<char> &tops, char top)
{
	for (int i = 0; i < tops.size(); i++)
	{
		if (tops[i] == top)
		{
			return i;
		}
	}
}
int getPositionOfTopInVector(std::vector<Edge> &edges, char top)
{
	for (int i = 0; i < edges.size(); i++)
	{
		if (edges[i].getEnd() == top)
		{
			return i;
		}
	}
}
std::vector<char> tops;
std::vector<std::vector<Edge>> givenGraph;
std::vector<std::vector<Edge>> edges;
bool flow = false;
std::vector <double> stack;
std::vector <char> toops;
int maxFlow = 0;
int flowSize = 0;


bool consistElement(char element)
{
	for (int i = 0; i < toops.size(); i++)
	{
		if (toops[i] == element)
		{
			return true;
		}
	}
	toops.push_back(element);
	return false;
}
void getMaxFlow()
{
	maxFlow = stack.back();
	stack.pop_back();
	toops.pop_back();
	while (!stack.empty())
	{
		if (maxFlow > stack.back())
		{
			maxFlow = stack.back();
		}
		stack.pop_back();
		toops.pop_back();
	}
}

int getPositionToInsert(std::vector<char> e, char element)
{
	for (int i = 0; i < e.size(); i++)
	{
		if ((int)e[i] >(int)element)
			return i;
	}
	return -1;
}
int getPositionToInsert(std::vector<Edge> e, char element)
{
	for (int i = 0; i < e.size(); i++)
	{
		if ((int)e[i].getEnd() >(int)element)
			return i;
	}
	return -1;
}
void insertVector(char startEdge, char endEdge)
{
	if (!isTopInList(tops, startEdge))//check presence of start top in list
	{
		std::vector<Edge> a;//create new vector
		int positionToInsert = getPositionToInsert(tops, startEdge);
		//std::cout << positionToInsert << std::endl;
		if (positionToInsert != -1)
		{
			tops.insert(tops.begin() + positionToInsert, startEdge);//put new top in list
			edges.insert(edges.begin() + positionToInsert, a);
			givenGraph.insert(givenGraph.begin() + positionToInsert, a);
		}
		else
		{
			tops.push_back(startEdge);
			edges.push_back(a);//and put it in the list
			givenGraph.push_back(a);
		}

	}
	if (!isTopInList(tops, endEdge))//check presence of end top in list
	{
		std::vector<Edge> a;//create new vector
		int positionToInsert = getPositionToInsert(tops, endEdge);
		//std::cout << positionToInsert << std::endl;
		if (positionToInsert != -1)
		{
			tops.insert(tops.begin() + positionToInsert, endEdge);//put new top in list
			edges.insert(edges.begin() + positionToInsert, a);
			givenGraph.insert(givenGraph.begin() + positionToInsert, a);
		}
		else
		{
			tops.push_back(endEdge);
			edges.push_back(a);//and put it in the list
			givenGraph.push_back(a);
		}
	}

}
std::vector<std::vector<Edge>> insertElement(std::vector<std::vector<Edge>> e, char startEdge, char endEdge, double length)
{
	Edge edge(startEdge, endEdge, length);
	int vectorNumber = getPositionOfTop(tops, startEdge);
	int positionInVector = getPositionToInsert(e[vectorNumber], endEdge);
	if (positionInVector != -1)
	{
		e[vectorNumber].insert(e[vectorNumber].begin() + positionInVector, edge);
	}
	else
	{
		e[vectorNumber].push_back(edge);
	}
	return e;
}
bool consistEdge(std::vector<std::vector<Edge>> e, char startEdge, char endEdge)
{
	int vectorNumber = getPositionOfTop(tops, startEdge);
	for (int i = 0; i < e[vectorNumber].size(); i++)
	{
		if (e[vectorNumber][i].getEnd() == endEdge)
			return true;
	}
	return false;
}
bool findFlow(const std::vector<char> &tops, char start, char end)
{
	int position = getPositionOfTop(tops, start);
	for (int i = 0; i < edges[position].size(); i++)
	{
		//std::cout << edges[position][i].getStart() << " "<< edges[position][i].getEnd()<<" ";
		if (!consistElement(edges[position][i].getEnd()))
		{
			//std::cout << "!consist" << std::endl;
			stack.push_back(edges[position][i].getLength());
			if (edges[position][i].getLength() != 0)
			{
				if (edges[position][i].getEnd() != end)
				{
					flow = findFlow(tops, edges[position][i].getEnd(), end);
				}
				else
				{
					flow = true;
					getMaxFlow();
					flowSize += maxFlow;
					//std::cout << maxFlow << std::endl;

				}
			}
			if (flow == true)
			{
				edges[position][i].setLength(edges[position][i].getLength() - maxFlow);
				int position2 = getPositionOfTop(tops, edges[position][i].getEnd());
				int position3 = getPositionOfTopInVector(edges[position2], edges[position][i].getStart());
				edges[position2][position3].setLength(edges[position2][position3].getLength() + maxFlow);
				break;
			}
			else
			{
				stack.pop_back();
				toops.pop_back();
			}
		}
	}
	return flow;
}

int main()
{
	int number = 0;
	char start;
	char end;

	std::cin >> number;
	std::cin >> start;
	std::cin >> end;

	char startEdge;
	char endEdge;
	double length;


	for (int i = 0; i < number; i++)
	{
		std::cin >> startEdge;
		std::cin >> endEdge;
		std::cin >> length;

		insertVector(startEdge, endEdge);

		givenGraph = insertElement(givenGraph, startEdge, endEdge, length);
		edges = insertElement(edges, startEdge, endEdge, length);
	}

	for (int i = 0; i < edges.size(); i++)
	{
		for (int j = 0; j <edges[i].size(); j++)
		{
			if (!consistEdge(edges, edges[i][j].getEnd(), edges[i][j].getStart()))
			{
				edges = insertElement(edges, edges[i][j].getEnd(), edges[i][j].getStart(), 0);
			}
		}
	}

	/*for (int i = 0; i < edges.size(); i++)
	{
	for (int j = 0; j < edges[i].size(); j++)
	{
	std::cout << edges[i][j].getStart() << " " << edges[i][j].getEnd() << " " << edges[i][j].getLength()<< std::endl;
	}
	}*/

	while (findFlow(tops, start, end))
	{
		flow = false;
	}

	std::cout << flowSize << std::endl;

	for (int i = 0; i < givenGraph.size(); i++)
	{
		for (int j = 0; j < givenGraph[i].size(); j++)
		{
			//std::cout << edges[i][j].getStart() << " " << edges[i][j].getEnd()<< " " << copy[i][j].getLength() - edges[i][j].getLength() << std::endl;
			int position = getPositionOfTop(tops, givenGraph[i][j].getStart());
			int position2 = getPositionOfTopInVector(edges[position], givenGraph[i][j].getEnd());
			if ((givenGraph[i][j].getLength() - edges[position][position2].getLength())>0)
				std::cout << givenGraph[i][j].getStart() << " " << givenGraph[i][j].getEnd() << " " << givenGraph[i][j].getLength() - edges[position][position2].getLength() << std::endl;
			else
				std::cout << givenGraph[i][j].getStart() << " " << givenGraph[i][j].getEnd() << " " << 0 << std::endl;
			//std::cout << givenGraph[i][j].getStart() << " " << givenGraph[i][j].getEnd() << " " << givenGraph[i][j].getLength()<< std::endl;
		}
	}

	return 0;
}

