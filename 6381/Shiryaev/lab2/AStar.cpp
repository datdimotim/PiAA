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
	int heuristic;

	Vertex(char n, char goal): name(n), came_from(nullptr), visited(false), costbefore(0){
		heuristic = goal - name;
	}

	void AddNeigh(Vertex *vertex, double weight){
		neighbors.push_back(vertex);
		weights.push_back(weight);
	}

	char getName(){
		return name;
	}

	double getCost(){
		return costbefore;
	}

	bool getVis(){
		return visited;
	}

	double getWeight(int j){
		return weights[j];
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

	int getH(){
		return heuristic;
	}
};

void printGraph(vector<Vertex*> graph);
int SearchByName(vector<Vertex*> graph, char name);
void AStar (Vertex* start, Vertex* goal, vector<char>& path);
void printVector(vector<char> vector);
void fillPath(Vertex* goal, vector<char>& path);

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
		j = SearchByName(graph, tmp);
		if (i < 0){
			Vertex *A = new Vertex(name, goal);
			graph.push_back(A);
			i = graph.size() - 1;
		}
		if (j < 0){
			Vertex *B = new Vertex(tmp, goal);
			graph.push_back(B);
			j = graph.size() - 1;
		}
		graph[i]->AddNeigh(graph[j],weight);
	}
	//printGraph(graph);
	AStar(graph[SearchByName(graph,start)], graph[SearchByName(graph,goal)], path);
	fillPath(graph[SearchByName(graph,goal)], path);
	//cout << "path: ";
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

void AStar (Vertex *start, Vertex *goal, vector<char>& path){
	//path.push_back(start.getName());
	//double new_cost = costbefore;
	//cout << "ya v vershine" << endl;
	//cout << start->getName() << start->getH() << endl;
	if(start->getName() == goal->getName()){
		//cout << "nashel goal" << endl;
		return;
	}
	for (size_t i = 0; i < start->neighbors.size(); i++){
		if(start->neighbors[i] == start->getCame()){
			return;
		}
		if(start->neighbors[i]->getName() == start->getName()){
			continue;
		}
		double new_cost = start->getCost() + start->getWeight(i) + start->neighbors[i]->getH();
		//cout << "stoimost' do soseda " << start->neighbors[i]->getName() << " vershiny " << start->getName() << " ravna: " << start->getCost() << "+" << start->getWeight(i) << "+" << start->neighbors[i]->getH() << "=" << new_cost << endl;
		if(start->neighbors[i]->costbefore == 0 || new_cost < start->neighbors[i]->costbefore)
		{
			//cout << "kladu znacheniya" << endl;
			start->neighbors[i]->setCame(start);
			start->neighbors[i]->setCost(new_cost);
			//cout << "perehozhu v soseda" << endl;
			AStar(start->neighbors[i], goal, path);
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

/*
a g
a b 5.0
a c 3.0
b d 2.0
c d 1.0
c e 2.0
d e 2.0
d g 5.0
d f 2.0
b f 1.0
f g 2.0
e g 6.0

a e
a b 3.0
b c 1.0
c d 1.0
a d 5.0
d e 1.0

a e
a e 15.0
a b 1.0
c e 12.0
b d 5.0
b d 7.0
d e 1.0
b c 8.0

a f
a b 1.0
c b 5.0
d e 4.0
a e 7.0
a c 10.0
c d 11.0
e f 3.0
b f 16.0

a z
a b 4
b z 2
a x 5
x z 1
x y 1

a e
a b 0.4
a c 2.4
a d 1.5
c e 1.7
d e 3.2
b e 0.9

a e
a b 1.7
b e 1.2
a d 0.3
d c 0.2
c e 0.7
d e 0.5
*/