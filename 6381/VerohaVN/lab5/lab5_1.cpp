#include <iostream>
#include <string>
#include <vector>

using namespace std;
const char alph[] = { 'A','C','G','T','N' };

struct Bor {
	int next[5];
	int	suff_link = -1;
	int suff_next[5];
	int parent;
	bool flag = false;
	int vrtx;
	int number_P;
};

int alphabet(char a) {
	for (int i = 0; i<5; ++i)
		if (alph[i] == a)
			return i;
}

Bor make_Bor(int p, int c) {
	Bor v;
	memset(v.next, -1, sizeof(v.next));
	memset(v.suff_next, -1, sizeof(v.suff_next));
	v.parent = p;
	v.vrtx = c;
	return v;
}

int search_suffix(int v, int ch, vector<Bor> &bor);

int search_suffix(int v, vector<Bor> &bor) {
	if (bor[v].suff_link == -1) {
		if (v == 0 || bor[v].parent == 0)
			bor[v].suff_link = 0;
		else
			bor[v].suff_link = search_suffix(search_suffix(bor[v].parent, bor), bor[v].vrtx, bor);
	}
	return bor[v].suff_link;
}

int search_suffix(int v, int ch, vector<Bor> &bor) {
	if (bor[v].suff_next[ch] == -1) {
		if (bor[v].next[ch] != -1)
			bor[v].suff_next[ch] = bor[v].next[ch];
		else
			if (v == 0)
				bor[v].suff_next[ch] = 0;
			else
				bor[v].suff_next[ch] = search_suffix(search_suffix(v, bor), ch, bor);
	}
	return bor[v].suff_next[ch];
}

void search(const string& s, vector<int> &pos, vector<Bor> &bor) {
	int u = 0;
	for (unsigned int i = 0, t = 0; i < s.size(); i++) {
		if (bor[u].flag) {
			cout << i - pos[bor[u].number_P - 1] + 1 << ' ' << bor[u].number_P << endl;

			t = search_suffix(u, bor);
			if (bor[t].flag) cout << i - pos[bor[t].number_P - 1] + 1 << ' ' << bor[t].number_P << endl;

			u = search_suffix(u, alphabet(s[i]), bor);
		}
		else 
			if (bor[u].next[alphabet(s[i])] != -1) 
				u = bor[u].next[alphabet(s[i])];
		else 
			u = search_suffix(u, alphabet(s[i]), bor);
	}
	if (bor[u].flag) 
		cout << s.size() - pos[bor[u].number_P - 1] + 1 << ' ' << bor[u].number_P << endl;
}

int main() {
	vector<Bor> bor;
	vector<int> pos;
	string text, pattern;
	int n;
	bor.push_back(make_Bor(0, ' '));
	cin >> text >> n;
	for (int i = 0; i<n; i++) {
		cin >> pattern;
		int index = 0;
		for (unsigned int i = 0, symb; i < pattern.size(); i++) {
			symb = alphabet(pattern[i]);
			if (bor[index].next[symb] == -1) {
				bor.push_back(make_Bor(index, symb));
				bor[index].next[symb] = bor.size() - 1;
			}
			index = bor[index].next[symb];
		}
		bor[index].flag = true;
		bor[index].number_P = i + 1;
		pos.push_back(pattern.size());
	}
	search(text, pos, bor);
	return 0;
}