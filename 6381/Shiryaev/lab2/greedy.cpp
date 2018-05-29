#include <iostream>
#include <vector>
#include <algorithm>
#include <cstddef>

using namespace std;

class Vertex{
public:
	char name;
	Vertex* came_from;
	vector<Vertex*> neighbors;
	vector<double> weights;
	bool visited;
	double costbefore;

	Vertex(char n): name(n), came_from(nullptr), visited(false), costbefore(0){}

	void AddNeigh(Vertex *vertex, double weight){
		neighbors.push_back(vertex);
		weights.push_back(weight);
	}

	char getName(){
		return name;
	}

	bool getVis(){
		return visited;
	}

	double getWeight(int j){
		return weights[j];
	}

	void setWeight(int j, double a){
		weights[j] = a;
	}

	void setVis(bool a){
		visited = a;
	}

	void setCame(Vertex *a){
		came_from = a;
	}

	Vertex* getCame(){
		return came_from;
	}

	void setCost(double a){
		costbefore = a;
	}
};

void printGraph(vector<Vertex*> graph);
int SearchByName(vector<Vertex*> graph, char name);
void Greedy (Vertex* start, Vertex* goal, vector<char>& path);
void printVector(vector<char> vector);
void fillPath(Vertex* goal, vector<char>& path);
int findMinNum(Vertex * vertex);

int main() {
	char start, goal;
	char name, tmp;
	double weight;
	int i, j;
	vector<char> path;
	vector<Vertex*> graph;
	cin >> start >> goal;
	while(cin >> name >> tmp >> weight){
		cin.clear();
		i = SearchByName(graph, name);
		if (i < 0){
			Vertex *A = new Vertex(name);
			graph.push_back(A);
			i = graph.size() - 1;
		}
		j = SearchByName(graph, tmp);
		if (j < 0){
			Vertex *B = new Vertex(tmp);
			graph.push_back(B);
			j = graph.size() - 1;
		}
		graph[i]->AddNeigh(graph[j],weight);
	}
	Greedy(graph[SearchByName(graph,start)], graph[SearchByName(graph,goal)], path);
	fillPath(graph[SearchByName(graph,goal)], path);
	printVector(path);
	return 0;
}

int SearchByName(vector<Vertex*> graph, char a){
	int j = -1;
	for(size_t i = 0; i < graph.size(); ++i){
		if(graph[i]->getName() == a){
			return i;
		}
	}
	return j;
}

void printGraph(vector<Vertex*> graph){
	for(size_t i = 0; i < graph.size(); i++)
	{
		cout << "current ver: " << graph[i]->getName() << endl;
		cout << "neighbors: ";
		for(size_t j = 0; j < graph[i]->neighbors.size(); j++)
		{
        	cout << '(' << (graph[i]->neighbors[j])->getName() << ' ';
        	cout << graph[i]->weights[j] << ')' << ' ';
		}
		cout << endl;
	}
}

void printVector(vector<char> vector){
	for(size_t i = 0; i < vector.size(); i++){
		cout << vector[i];
	}
}

void Greedy (Vertex *start, Vertex *goal, vector<char>& path){
	start->setVis(true);
	if(start->getName() == goal->getName()){
		return;
	}
	for (size_t i = 0; i < start->neighbors.size(); i++){
		if(start->neighbors[i] == start->getCame()){
			continue;
		}
		if(start->neighbors[i]->getName() == start->getName()){
			continue;
		}
		if(findMinNum(start) != -1){
			int minNum = findMinNum(start);
			start->neighbors[minNum]->setVis(true);
			start->neighbors[minNum]->setCame(start);
			Greedy(start->neighbors[minNum], goal, path);
		}
		else
			return;
	}
	return;
}

void fillPath(Vertex* goal, vector<char>& path){
	vector<char> tmp;  
	while(goal->getCame() != nullptr){
		tmp.push_back(goal->getName());
		goal = goal->getCame();
	}
	tmp.push_back(goal->getName());
	for(int i = tmp.size()-1; i >= 0; i--){
		path.push_back(tmp[i]);
	}
	return;
}

int findMinNum(Vertex * vertex){
	int minNum = -1;
	double minW = 9223372036854775807;
	for (size_t i = 0; i < vertex->neighbors.size(); ++i){
		if (vertex->getWeight(i) < minW && vertex->neighbors[i]->getVis() == false){
			minW = vertex->getWeight(i);
			minNum = i;		}
	}
	return minNum;
}