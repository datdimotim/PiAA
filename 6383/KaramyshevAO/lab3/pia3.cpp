#include <vector>
#include <iostream>
#include <algorithm>
#include <limits.h>
#include <queue>
#define N 100
using namespace std;

class graph{
public:
  char from;
  char to;
  vector<vector<int>> cap;
  vector<vector<int>> flow;
  graph() : from(0), to(0), cap(N, vector<int>(N, 0)), flow(N, vector<int>(N,0)){}
  int max_flow (){
      int new_flow = ff_alg();
      int sum = new_flow;
      while (new_flow > 0)
      {
          new_flow = ff_alg();
          sum += new_flow;
      }
      return sum;
  }
  int ff_alg(){
    vector<int> fov(N, 0);
    vector<int> prevs(N, 0);
    queue <char> queue;
    char cur;
    fov [from-'1'] = INT_MAX;
    prevs[to-'1'] = 0;
    queue.push(from);
    while (prevs[to-'1'] == 0 && !queue.empty())
    {
        cur = queue.front();
         for (int j = 0; j < N; j++){
                if ((cap[cur-'1'][j] - flow[cur-'1'][j])>0 && fov[j] == 0)
                {
                        queue.push( j+'1');
                        prevs[j] = cur;
                        fov[j] = min(fov[cur-'1'], cap[cur-'1'][j] - flow[cur-'1'][j]);
                }
         }
        queue.pop();
    }
    if (prevs[to-'1'] == 0)
        return 0;
    cur = to;
    while ( cur != from )
    {
         flow [prevs[cur-'1']-'1'][cur-'1'] += fov [to-'1'];
         flow [cur-'1'][prevs[cur-'1']-'1'] -= fov [to-'1'];
         cur = prevs [cur-'1'];
    }
    return fov[to-'1'];
  }
};
int main(){
  int M, wei;
  graph X;
  cin >> M;
  cin >> X.from >> X.to;
  char a, b;
  for(int i=0; i<M; i++){
    cin >> a >> b >> wei;
    X.cap[a-'1'][b-'1']=wei;
  }
  cout << X.max_flow() << endl;
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      if(X.flow[i][j]!=-1 && X.flow[i][j]<0){
         X.flow[i][j]=0;
      }
      if(X.cap[i][j]!=0 && X.flow[i][j]!=-1){
        cout << (char)(i+'1') << ' ' << (char)(j+'1') << ' ' << X.flow[i][j] << endl;
      }
    }
  }
  return 0;
}
