#include <iostream>
#include <algorithm>
#include <vector>

#define s 150
#define outWay -1
using  namespace std;

class Search
{
public:
	Search() :start(0), finish(0), c(s, vector<int>(s, 0)), previous(s, 0), found(s, 0),
		flow(s, vector<int>(s, 0)) {}
	vector<vector<int>> c;
	vector<int> previous;
	vector<bool> found;
	vector<vector<int>> flow;
	int start, finish;

	void initprevious() {
		for (int i = 0; i<s; i++)
			previous[i] = outWay;
	}

	void top(int v) {
		found[v] = true;
		for (int i = 0; i<s; i++)
			if (!found[i] && (c[v][i] - flow[v][i] > 0 && c[v][i] != 0 || flow[v][i] < 0 && c[i][v] != 0)) {
				previous[i] = v;
				top(i);
			}
	}

	bool path(int v) {
		top(v);
		for (int i = 0; i<s; i++)
			found[i] = false;
		return (previous[finish] != outWay);
	}

	int FFLow () {
		int maxFlow = 0;
		while (path(start)) {
			int start = 9999999;
			for (int v = finish; 0 <= previous[v]; v = previous[v])
				start = min(start, c[previous[v]][v] - flow[previous[v]][v]);
			for (int v = finish; 0 <= previous[v]; v = previous[v]) {
				flow[previous[v]][v] += start;
				flow[v][previous[v]] -= start;
			}
			maxFlow += start;
			initprevious();
		}
		return maxFlow;
	}
};

int main() {
	Search f;
	f.initprevious();
	int numb_tops = 0, cost = 0;
	char  ist, st;
	cin >> numb_tops;
	cin >> ist >> st;
	f.start = ist - '0';
	f.finish = st - '0';
	for (int k = 0; k < numb_tops; k++) {
		cin >> ist >> st >> cost;
		int i = ist - '0';
		int j = st - '0';
		f.c[i][j] = cost;
	}
	cout << f.FFLow () << endl;
	for (int i = 0; i < s; i++)
		for (int j = 0; j < s; j++) {
			if (f.flow[i][j] != 0 && f.flow[i][j] < 0)
				f.flow[i][j] = 0;
			if (f.c[i][j] > 0)
				cout << (char)(i + '0') << " " << (char)(j + '0') << " " << f.flow[i][j] << endl;
		}
	system ("pause");
	return 0;
}