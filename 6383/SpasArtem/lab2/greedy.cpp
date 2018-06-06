#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;

 
class Path{
public:
    char from;
    char to;
    double weight;
    bool correct;
    Path(): from('\0'), to('\0'), weight(-1), correct(true){};
    Path(char from, char to, double weight): from(from), to(to), weight(weight), correct(true){}
};
 
int min(vector<Path> &graph, char start, int k, vector<char> corr_path){//
    Path min;
    for (int i = 0; i < graph.size(); i++)
        if ((graph[i].from == start) && (graph[i].correct)) {
            min = graph[i]; 
            k = i; 
            break;
        }// if there is a path from this vertex
    if (min.weight == -1) {graph[k].correct = false; return -1;}// if no - mark this edge as incorrect
 
    for (int i = 0; i < graph.size(); i++)
        if ((graph[i].weight < min.weight) && (graph[i].from == start) && (graph[i].correct)) {
            min = graph[i]; 
            k = i;
        }// choose the the path by a min edge 
    if (find(corr_path.begin(), corr_path.end(), graph[k].to) != corr_path.end()) {
        graph[k].correct = false;
        return -1;
    }// if the vertex we are going to have already added
    return k;// return index of edge with min weight
}
 
int main(){
    char start, end;
    cin >> start >> end;
    vector<Path> graph;
    vector<char> corr_path;
    Path cur_path;
    char v; // first vertex (from)
    char v1;// end vertex (to)
    double weight;// weight of edge
    
    while (cin >> v){
        cin >> v1 >> weight;
        Path cur_path(v, v1, weight);
        graph.push_back(cur_path);
	}

    char current = start;
    int i = 0;
    while(true){
        corr_path.push_back(current);
		i = min(graph, current, i, corr_path);
		if (i == -1) {i = 0; current = start; corr_path.clear();}
        else current = graph[i].to;
        if (graph[i].to == end) break;
    }
    corr_path.push_back(end);
   
    for (int i = 0; i<corr_path.size(); i++)
        cout << corr_path[i];

    return 0;
}