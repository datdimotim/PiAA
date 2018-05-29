//lab3. Bykov I.V. 6383

#include <iostream>
#include <queue>
#include <vector>
#define sz 75
#define MAXFLOW 9999

class Helper
{
public:
    char sink;
    char source;
    std::vector<std::vector<int>> currentFlow;
    std::vector<std::vector<int>> adjacencyMatrix;
    Helper() :  sink(0), source(0), currentFlow(sz, std::vector<int>(sz, 0)), adjacencyMatrix(sz, std::vector<int>(sz, 0)) {}

void fill_adj_matrix(int i, int j, int w)
{
    adjacencyMatrix[i][j] = w;
}

int to_int(char a) 
{
    return (int)(a - '1');
}
    
char to_char(int a)
{
    return (char)(a + '1');
}
    
int max_flow ()
{
    int new_flow = Ford_Falkerson();
    int sum = new_flow;
    while (new_flow > 0)
    {
        new_flow = Ford_Falkerson();
        sum += new_flow;
    }
    return sum;
}
    
int Ford_Falkerson()
{
    std::vector<int> flowOfVertex(sz, 0);
    std::vector<int> prevs(sz, 0);
    std::queue <char> queue;
    char curVertex;
    flowOfVertex [to_int(source)] = MAXFLOW;
    prevs[to_int(sink)] = 0;
    queue.push(source);
    while (prevs[to_int(sink)] == 0 && !queue.empty()) 
    {
        curVertex = queue.front();
         for (int j = 0; j < sz; j++){
                if ((adjacencyMatrix[to_int(curVertex)][j] - currentFlow[to_int(curVertex)][j])>0 && flowOfVertex[j] == 0) 
                {
                        queue.push(to_char(j));
                        prevs[j] = curVertex;
                        flowOfVertex[j] = std::min(flowOfVertex[to_int(curVertex)], adjacencyMatrix[to_int(curVertex)][j]
                        - currentFlow[to_int(curVertex)][j]);
                }
         }
        queue.pop();
    }
    if (prevs[to_int(sink)] == 0)
        return 0;
    curVertex = sink;
    while ( curVertex != source ) 
    {
         currentFlow [to_int(prevs[to_int(curVertex)])][to_int(curVertex)] += flowOfVertex [to_int(sink)];
         currentFlow [to_int(curVertex)][to_int(prevs[to_int(curVertex)])] -= flowOfVertex [to_int(sink)];
         curVertex = prevs [to_int(curVertex)];
    }
    return flowOfVertex [to_int(sink)];
}
    
void out()
{
    for (int i = 0; i < sz; i++)
    {
        for (int j = 0; j < sz; j++)
        {
            if (currentFlow[i][j] != -1 && currentFlow[i][j] < 0 )
                currentFlow[i][j] = 0;
            if ((currentFlow[i][j]!=-1) && adjacencyMatrix[i][j] != 0)
                std::cout << to_char(i) << ' ' << to_char(j)
                << ' ' << currentFlow[i][j] << std::endl;
        }
    }
}

};

int main()
{
    int n = 0, weight;
    Helper h;
    char a, b;
    std::cin >> n >> h.source >> h.sink;
    for (int m = 0; m < n; m++)
    {
        std::cin >> a >> b >> weight;
        h.fill_adj_matrix((int)(a - '1'), (int)(b - '1'), weight);
    }
    std::cout << h.max_flow() << std::endl;
    h.out();
    return 0;
}
