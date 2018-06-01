#include <vector>
#include <iostream>
#include <limits.h>
using namespace std;
class para{
public:
  char from;
  char to;
  float weight;
  bool dead;
  para(char from=0, char to=0, float weight=0, bool dead=false) : from(from), to(to), weight(weight), dead(dead){}
};
int min(std::vector<para> &graph, char from){
  float min = INT_MAX;
  int k=-1;
  for(int i=0; i<graph.size(); i++){
    if(!graph[i].dead && (graph[i].from==from) && (graph[i].weight < min)){
      min = graph[i].weight;
      k=i;
    }
  }
  return k;
}
bool way(std::vector<para> &graph, std::vector<char> &qwert, char from, char to){
  qwert.push_back(from);
  if(from==to) return true;
  while(min(graph, from)!=-1){
    if(way(graph, qwert, graph[min(graph, from)].to, to))return true;
    else{
      qwert.pop_back();
      graph[min(graph, from)].dead = true;
    }
  }
  return false;
}
int main(){
  char begin, end;
  cin >> begin >> end;
  std::vector<para> graph;
  std::vector<char> qwert;
  char from, to;
  float weight;
  while(to!=end){
    cin >> from >> to >> weight;
    para tmp(from, to, weight, false);
    graph.push_back(tmp);
  }
  way(graph, qwert, begin, end);
  for(int i=0; i<qwert.size(); i++) cout<<qwert[i];
  return 0;
}
