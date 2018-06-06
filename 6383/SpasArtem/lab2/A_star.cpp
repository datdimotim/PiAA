#include <string>
#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <map>
using namespace std;

class Pair {
public:
    Pair(char name, double weight): name(name), weight(weight) {};
    char name = 0;
    double weight = 0;
};

class Vertex {
public:
    Vertex(char name) : name(name){};

    list<Pair> list_edge; // все возможные пути, в которые ведет вершина

    char get_name() const {
        return name;
    }
private:
    char name;
};

class Graph {
public:
    Graph() {
        for (char i = 'a'; i <= 'z'; i++)
            list_vertex.push_back(Vertex(i));
    }
    vector<Vertex> list_vertex; 
    map <char, char> came_from; 
    map <char, double> cost_to_top; 
    Vertex& at(char a){
        return list_vertex[a-'a'];
    }
    void search_path (Vertex first, Vertex last);
    double heuristic(Pair temp, Vertex last) {
        return abs(last.get_name()-temp.name);
    }
};

class Pair_prior {
public:
    Pair_prior(Vertex vert, double prior): vert(vert), prior(prior){};
    Vertex vert;
    double prior;
    bool operator<(const Pair_prior b) const {
        return prior > b.prior;
    }
};

void Graph::search_path (Vertex first, Vertex last) { // основная функция
    priority_queue<Pair_prior> next_step;
    next_step.emplace(first, 0);

    came_from[first.get_name()] = first.get_name();
    cost_to_top[first.get_name()] = 0;

    while(!next_step.empty()) {
        const Vertex temp = next_step.top().vert;
        next_step.pop();

        if(temp.get_name() == last.get_name()) {
            break;
        }

        for(const Pair& next : at(temp.get_name()).list_edge) {
            double new_cost = cost_to_top[temp.get_name()] + next.weight;
            if(cost_to_top.find(next.name) == cost_to_top.end() || new_cost < cost_to_top[next.name]) {
                cost_to_top[next.name] = new_cost;
                double priority = new_cost + heuristic(next, last);
                came_from[next.name] = temp.get_name();
                next_step.emplace(at(next.name), priority);  
            }
        }
    }
        // собираем путь и выводим его
       vector<char> path;
       char elem = last.get_name();
       path.push_back(elem);
       while(elem!= first.get_name()) {
           elem = came_from[elem];
           path.push_back(elem);
       }
       reverse(path.begin(), path.end());
       for(int i = 0; i < path.size(); i++)
           cout << path[i];
    }

int main() {
    char first, last;
    char edge_l,edge_r;
    double weight;

    Graph graph;
    cin >> first >> last;
    Vertex first_vert (first);
    Vertex last_vert (last);

    while (cin >> edge_l){
        cin>> edge_r ;
        cin >> weight;
        graph.at(edge_l).list_edge.push_back({edge_r, weight});
        graph.at(edge_r).list_edge.push_back({edge_l, weight});
    }

    graph.search_path(first_vert, last_vert);
    return 0;
}