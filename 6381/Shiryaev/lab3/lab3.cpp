#include <iostream>
#include <vector>
#include <algorithm>
#include <cstddef>
#define MAXDOUBLE  9223372036854775807.0

using namespace std;

class Vertex{
public:
	char name;
	Vertex* came_from;
	vector<Vertex*> neighbors;
	vector<double> capacity;
	vector<double> flow;
	vector<bool> EdgeVis;
	bool visited = false;

	Vertex(char n, char goal): name(n), came_from(nullptr) {}

	void AddNeigh(Vertex *vertex, double cap){
		neighbors.push_back(vertex);
		capacity.push_back(cap);
		flow.push_back(0);
		EdgeVis.push_back(false);
	}

	char getName(){
		return name;
	}

	Vertex* getNei(int i){
		return neighbors[i];
	}

	double getCap(int j){
		return capacity[j];
	}

	double setCap(int j, double w){
		capacity[j] = w;
	}

	void setCame(Vertex *a){
		came_from = a;
	}

	Vertex* getCame(){
		return came_from;
	}

	bool MayGo(){
		bool a = false;
		for(int i = 0; i < neighbors.size(); i++){
			if(capacity[i] != 0){
				a = true;
			}
		}
		cout << "may go: "<< a << endl;
		return a;
	}

	bool getVis(){
		return visited;
	}

	void setVis(bool a){
		visited = a;
	}

	void setFlow(int i, double val){
		flow[i] = val;
	}

};

void printGraph(vector<Vertex*> graph);
int SearchByName(vector<Vertex*> graph, char name);
void FordFalk(Vertex* start, Vertex* goal, vector<Vertex*> graph, double &maxflow, double localMax);
int findMaxNum(Vertex * vertex);
int findMaxNum2(Vertex* vertex){
	int maxNum = -1;
	double maxW = -1;
	for (size_t i = 0; i < vertex->neighbors.size(); ++i){
		if (vertex->getCap(i) > maxW){
			maxW = vertex->getCap(i);
			maxNum = i;		
		}
	}
	//cout << maxNum;
	return maxNum;
}
int SearchNeiByName(Vertex * vertex, char a);

// int checkgraph(Vertex * vertex){
// 	int ok = -1;
// 	for(int i = 0; i < vertex->neighbors.size(); ++i){
// 		if()
// 	}
// }

int main() {
	char start, goal;
	char name, tmp;
	double capacity;
	double maxcap = 0;
	int i, j;
	int NumEdges = 0;
	double maxflow = 0;
	vector<char> path;
	vector<Vertex*> graph;
	cin >> NumEdges >> start >> goal;
	while(cin >> name >> tmp >> capacity){
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
		graph[i]->AddNeigh(graph[j],capacity);
		if(maxcap < capacity){
			maxcap = capacity;
		}
	}
	printGraph(graph);
	FordFalk(graph[SearchByName(graph, start)], graph[SearchByName(graph, goal)], graph, maxflow, maxcap);
	//printGraph(graph);
	cout << maxflow << endl;
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

int SearchNeiByName(Vertex * vertex, char a){
	for(size_t i = 0; i < vertex->neighbors.size(); ++i){
		if(vertex->getNei(i)->getName() == a){
			return i;
		}
	}
}

void printGraph(vector<Vertex*> graph){
	for(size_t i = 0; i < graph.size(); i++)
	{
		cout << "current ver: " << graph[i]->getName() << endl;
		cout << "neighbors: ";
		for(size_t j = 0; j < graph[i]->neighbors.size(); j++)
		{
        	cout << '(' << (graph[i]->neighbors[j])->getName() << ' ';
        	cout << graph[i]->capacity[j] << ')' << ' ';
		}
		cout << endl;
	}
}

void FordFalk(Vertex* start, Vertex* goal, vector<Vertex*> graph, double &maxflow, double localMax){
	int maxNum = 0;
	double tmp;
	double lm = localMax;
	int i = 0;
	Vertex * next = nullptr;
	while(start->MayGo()){
		//cout << "nachalo" <<endl;
		Vertex* currVertex = start;
		currVertex->setVis(true);
		cout << start->getName() << endl;
		while(findMaxNum(currVertex) != -1 || currVertex == goal ){
			cout << currVertex->getName() << endl;
			if(currVertex == goal){
				cout << "!" << endl;
				while(currVertex != start){
					cout << currVertex->getName() << " " << currVertex->getCame()->getName() << endl;
					next = currVertex;
					currVertex = currVertex->getCame();
					i = SearchNeiByName(currVertex, next->getName());
					currVertex->getNei(i)->setCame(nullptr);
					currVertex->getNei(i)->setVis(false);
					currVertex->setFlow(i, lm);
					tmp = currVertex->getCap(i) - lm;
					currVertex->setCap(i, tmp);
				}
				maxflow = maxflow+lm;
				cout << lm << " " << maxflow << endl;
				printGraph(graph);
				lm = localMax;
				//currVertex = start;
			}
			//cout << currVertex->MayGo() << endl;
			if (currVertex->MayGo()){
				//cout << "tut" << endl;
				maxNum = findMaxNum(currVertex);
				if(lm > currVertex->getCap(maxNum)){
					lm = currVertex->getCap(maxNum);
				}
				currVertex->getNei(maxNum)->setVis(true);
				currVertex->getNei(maxNum)->setCame(currVertex);
				currVertex = currVertex->getNei(maxNum);
			}
			else {
				if(currVertex == start || currVertex->getCame() == start){
					break;
				}
				currVertex->setVis(true);
				currVertex = currVertex->getCame();
				//cout << "schavzorvus' " << currVertex->getName() << endl;
				//cout << "mne pizda" << endl;
			}
			//break;
		}
		break;
	}
	//cout << "tut" << endl;
	return;
}

int findMaxNum(Vertex * vertex){
	int maxNum = -1;
	double maxW = -1;
	//cout << "findmax1" << endl;
	for (int i = 0; i < vertex->neighbors.size(); ++i){
		//cout << "findmax2" << endl;
		if (vertex->getCap(i) > maxW && vertex->getNei(i)->getVis() == false){
			maxW = vertex->getCap(i);
			maxNum = i;		
		}
	}
	return maxNum;
}




/*

7
a
f
a b 7
a c 6
b d 6
c f 9
d e 3
d f 4
e c 2

16
a
e
a b 20
b a 20
a d 10
d a 10
a c 30
c a 30
b c 40
c b 40
c d 10
d c 10
c e 20
e c 20
b e 30
e b 30
d e 20
e d 20





			cout << "!!" << endl;
			maxNum = findMaxNum(currVertex);
			
			if(currVertex->MayGo()){ // возможно надо вставить проверку на висячую вершину
				cout << "!!!!" << endl;
				(currVertex->getNei(maxNum))->setCame(currVertex);
				currVertex->getNei(maxNum)->setVis(true);
				int fal = maxNum;
				maxNum = findMaxNum(currVertex);
				if(maxNum == -1){
					break;
				}
				currVertex->getNei(fal)->setVis(false);
				currVertex = currVertex->getNei(maxNum);
			}
			else {
				cout << "!!!!!" << endl;
				currVertex->setVis(true);
				currVertex = currVertex->getCame();
			}
			//(currVertex->getNei(maxNum))->setVis(true);
			//currVertex = currVertex->getNei(maxNum);
			cout << currVertex->getName() <<endl;



*/