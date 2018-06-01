#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <cmath>

using namespace std;
class para{
public:
  char from;
  char to;
  float weight;
  para(char from=0, char to=0, float weight=0) : from(from), to(to), weight(weight){}
};
class dote{
public:
  char name;
  dote *from;
  int f;
  int g;
  dote(char name=0, dote *from = nullptr, int f=0, int g=0) : name(name), from(from), f(f), g(g) {}
};
int min_f(vector<dote*> &Q){
  int k=0;
  dote *min = Q[k];
  for(int i=1; i<Q.size(); i++){
    if(Q[i]->f == min->f){
        if((min->f-min->g) > ((Q[i]->f)-(Q[i]->g))){
            min = Q[i];
            k=i;
        }
    }
    else if((Q[i]->f) < (min->f)){
      min = Q[i];
      k=i;
    }
  }
  return k;
}
int beQ_U(vector<dote*> &Q, dote *v){
  int k=-1;
  for(int i=0; i<Q.size(); i++){
    if(Q[i]->name == v->name){
      k=i;
      break;
    }
  }
  return k;
}
void prnt(dote *a){
  if((a->from)!=nullptr){
    prnt(a->from);
    cout<<a->name;
    return;
  }
  cout<<(a->name);
}
bool A1(vector<para> &graph, char start, char end){
  vector<dote*> Q;
  vector<dote*> U;
  dote *begn=new dote(start, nullptr, abs(end-start), 0);
  Q.push_back(begn);
  while(Q.size()!=0){

    dote *curr = Q[min_f(Q)];
    if(curr->name == end) {
      prnt(curr);
      delete curr;
      for(int i=0; i<U.size(); i++) delete U[i];
      for(int i=0; i<Q.size(); i++) delete Q[i];
      return true;
    }
    Q.erase(Q.begin()+min_f(Q));
    U.push_back(curr);
    for(int i=0; i<graph.size(); i++){
      if(curr->name ==graph[i].from){
        dote *neig=new dote(graph[i].to, curr, abs(end-graph[i].to)+graph[i].weight+curr->g, graph[i].weight+curr->g);
        if((beQ_U(U, neig)!=-1)){
          delete neig;
          continue;
        }

        if((beQ_U(Q, neig)==-1)) {
          Q.push_back(neig);
        }
        else if(neig->g < Q[beQ_U(Q, neig)]->g){
          Q[beQ_U(Q, neig)]->from = curr;
          Q[beQ_U(Q, neig)]->g = neig->g;
          Q[beQ_U(Q, neig)]->f = neig->f;
        }
      }
    }
  }
  return false;
}
int main(){
  char begin, end;
  cin >> begin >> end;
  std::vector<para> graph;
  char from, to;
  float weight;
  while(cin>>from>>to >> weight){
    para tmp(from, to, weight);
    graph.push_back(tmp);
  }
  A1(graph, begin, end);
  return 0;
}
