#include <iostream>
#include <algorithm>
#include <vector>

#define sz 150
#define noPath -1

using  namespace std;

class Helper
{
public:
	Helper():istock(0), stock(0), c(sz, std::vector<int>(sz, 0)), prevs(sz, 0), visited(sz, 0),
	flow(sz, std::vector<int>(sz, 0)){}
		
	std::vector<std::vector<int>> c;
	std::vector<int> prevs;
	std::vector<bool> visited;
	std::vector<std::vector<int>> flow;
	int istock, stock;

void initPrevs() {
	for (int i = 0; i<sz; i++)
	prevs[i] = noPath;
}

void isVertex(int v) {
	visited[v] = true;
	for (int i = 0; i<sz; i++)
		if (!visited[i] && (c[v][i] - flow[v][i] > 0 && c[v][i] != 0 || flow[v][i] < 0 && c[i][v] != 0)) {
			prevs[i] = v;
			isVertex(i);
		}
	}

bool isPath(int v) {
	isVertex(v);
	for (int i = 0; i<sz; i++)
		visited[i] = false;
	return (prevs[stock] != noPath);
	}

int fullFlow() {
	int maxFlow = 0;
	while (isPath(istock)) {
		int tmp = 9999999;
		for (int v = stock; 0 <= prevs[v]; v = prevs[v]) 
			 tmp = min(tmp, c[prevs[v]][v] - flow[prevs[v]][v]);
		for (int v = stock; 0 <= prevs[v]; v = prevs[v]) {
			flow[prevs[v]][v] += tmp; 
			flow[v][prevs[v]] -= tmp; 
		}
		maxFlow += tmp;
		initPrevs();
	}
	return maxFlow;
	}


};

int main() {
	Helper h;

	h.initPrevs();
	int numb_edges = 0, cost = 0;
	char  ist, st;
	cin >> numb_edges;
	cin >> ist >> st;
	h.istock = ist - '0';
	h.stock = st - '0';

	for (int k = 0; k < numb_edges; k++) {
		cin >> ist >> st >> cost;
		int i = ist - '0';
		int j = st - '0';
		h.c[i][j] = cost;
	}
	cout << h.fullFlow() << endl;
	for (int i = 0; i < sz; i++)
		for (int j = 0; j < sz; j++) {
			if (h.flow[i][j] != 0 && h.flow[i][j] < 0)
				h.flow[i][j] = 0;
			if (h.c[i][j] > 0)
				cout << (char)(i + '0') << " " << (char)(j + '0') << " " << h.flow[i][j] << endl;
		}
	return 0;
}