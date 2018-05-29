#include <iostream> 
#include <vector> 
#include <algorithm> 

using namespace std; 

class way{ 
public: 
char from; 
char to; 
double weight; 
bool correct; 
way(): from('\0'), to('\0'), weight(0), correct(true){}; 
way(char from, char to, double weight): from(from), to(to), weight(weight), correct(true){} 
}; 

int min(vector<way> &graph, char start, int k, vector<char> corrway){ 
way min; 
for (int i = 0; i < graph.size(); i++) 
if ((graph[i].from == start) && (graph[i].correct)) {min = graph[i]; k = i; break;} 

if (min.weight == -1) {graph[k].correct = false; return -1;} 

for (int i = 0; i < graph.size(); i++) 
if ((graph[i].weight < min.weight) && (graph[i].from == start) && (graph[i].correct)) {min = graph[i]; k = i;} 
if (find(corrway.begin(), corrway.end(), graph[k].to) != corrway.end()) {graph[k].correct = false; return -1;} 
return k; 
} 

int main(){ 
char start, end; 
cin >> start >> end; 
vector<way> graph; 
vector<char> corrway; 
way currway; 
char temp = start; 
char temp1; 
double weight; 
while (temp1 != end){ 
cin >> temp >> temp1 >> weight; 
way currway(temp, temp1, weight); 
graph.push_back(currway); 
} 
char start1 = start; 
int i = 0; 
for(;;){ 
corrway.push_back(start1); 
i = min(graph, start1, i, corrway); 
if (i == -1) {i = 0; start1 = start; corrway.clear();} 
else start1 = graph[i].to; 
if (graph[i].to == end) break; 
} 
corrway.push_back(end); 

for (int i = 0; i<corrway.size(); i++) 
cout << corrway[i]; 
}
