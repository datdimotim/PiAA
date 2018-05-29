#include <iostream>
#include <algorithm>

#define SIZE 300
#define noPath -1

using  namespace std;

int  costs[SIZE][SIZE] = {0};
int  prevs[SIZE] = {0};
bool visited[SIZE] = {0};
int  flow[SIZE][SIZE] = {0};

void deepSearch(int num)
{
	visited[num] = true;
	for (int i = 0; i < SIZE; i++)
	{
		if (!visited[i] && (costs[num][i] - flow[num][i] > 0 && costs[num][i] != 0 || flow[num][i] < 0 && costs[i][num] != 0))
		{
			prevs[i] = num;
			deepSearch(i);
		}
	}
}

bool getPath(int istock, int stock)
{
	deepSearch(istock);
	for (int i = 0; i < SIZE; i++) visited[i] = false;
	return (prevs[stock] != noPath);
}

int calcFlow(int stock, int istock)
{
	int maxFlow = 0;
	while (getPath(istock, stock))
	{
		int tmp = 9999;
		for (int num = stock; 0 <= prevs[num]; num = prevs[num]) tmp = min(tmp, costs[prevs[num]][num] - flow[prevs[num]][num]);
		for (int num = stock; 0 <= prevs[num]; num = prevs[num])
		{
			flow[prevs[num]][num] += tmp;
			flow[num][prevs[num]] -= tmp;
		}
		maxFlow += tmp;
		for (int i = 0; i < SIZE; i++) prevs[i] = noPath;
	}
	return maxFlow;
}

void printResult()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (flow[i][j] != 0 && flow[i][j] < 0) flow[i][j] = 0;
			if (costs[i][j] > 0) cout << (char)(i + '0') << " " << (char)(j + '0') << " " << flow[i][j] << endl;
		}
	}
}

int main()
{
	
	for (int i = 0; i < SIZE; i++) prevs[i] = noPath;
		
	int numPaths = 0; 
	int cost = 0;
	int istock;
	int stock;
		
	char left;
	char right;

	cin >> numPaths;
	cin >> left >> right;
		
	istock = left - '0';
	stock = right - '0';

	for (int k = 0; k < numPaths; k++)
	{
		cin >> left >> right >> cost;
		int i = left - '0';
		int j = right - '0';
		costs[i][j] = cost;
	}
	cout << calcFlow(stock, istock) << endl;
	printResult();
	return 0;
}