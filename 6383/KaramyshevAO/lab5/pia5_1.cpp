#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#define N 50

using namespace std;

class Bohr {
public:
	int next_vrtx[N]; // массив где номер вершины в которую мы переходим по индексу
	int pattern_num; // номер строки образца, обозначающего вершиной next_vrtx
	bool mark; // флаг указывающий исходную строку (конец)
	int suff_link; //суффиксная ссылка
	int auto_move[N]; //переход автомата
	int parent; // отец
	char symb;  // символ к этой вершине
  Bohr(int p, char c) : parent(p), symb(c) {
  	memset(next_vrtx, 255, sizeof(next_vrtx));
  	mark = false;
  	suff_link = -1;
  	memset(auto_move, 255, sizeof(auto_move));
  }
};

vector<Bohr> bohr;
vector<string> pattern;


void init() {
  Bohr v(0,0);
	bohr.push_back(v);
}


void add_pattern_to_bohr(const string& s) {
	int num = 0;
	for (int i = 0; i< s.length(); i++) {
		char ch = s[i] - 'A';
		if (bohr[num].next_vrtx[ch] == -1) { //нет ребра
      Bohr v(num, ch);
			bohr.push_back(v);
			bohr[num].next_vrtx[ch] = bohr.size() - 1;
		}
		num = bohr[num].next_vrtx[ch];
	}
	bohr[num].mark = true;
	pattern.push_back(s);
	bohr[num].pattern_num = pattern.size() - 1;
}

int get_auto_move(int v, char ch);

//получить суффиксную ссылку
int get_suff_link(int v) {
	if (bohr[v].suff_link == -1)
		if (v == 0 || bohr[v].parent == 0)
			bohr[v].suff_link = 0;
		else
			bohr[v].suff_link = get_auto_move(get_suff_link(bohr[v].parent), bohr[v].symb);
	return bohr[v].suff_link;
}

int get_auto_move(int v, char ch) {
	if (bohr[v].auto_move[ch] == -1)
		if (bohr[v].next_vrtx[ch] != -1)
			bohr[v].auto_move[ch] = bohr[v].next_vrtx[ch];
		else
			if (v == 0)
				bohr[v].auto_move[ch] = 0;
			else
				bohr[v].auto_move[ch] = get_auto_move(get_suff_link(v), ch);
	return bohr[v].auto_move[ch];
}


void check(int v, int i) {
	for (int u = v; u != 0; u = get_suff_link(u)) {
		if (bohr[u].mark) cout << i - pattern[bohr[u].pattern_num].length() + 1 << " " << bohr[u].pattern_num + 1 << endl;
	}
}

void find_all_pos(const string& s) {
	int u = 0;
	for (int i = 0; i<s.length(); i++) {
		u = get_auto_move(u, s[i] - 'A');
		check(u, i + 1);
	}
}

int main()
{
	init();
	string text;
	string pattern;
	int n;
	cin >> text >> n;

	for (int i = 0; i<n; i++) {
		cin >> pattern;
		add_pattern_to_bohr(pattern);
	}
	find_all_pos(text);
	return 0;
}
