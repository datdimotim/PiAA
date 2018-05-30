#include <iostream>
#include <string>
#include <vector>

using namespace std;
const char alph[] = { 'A','C','G','T','N' };

struct Bor {
	int next[5];
	int	suff_link = -1;
	int suff_next[5];
	int	parent;
	bool flag = false;
	int vrtx;
	int number = 0;
	vector <int> number_P;
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

void search(const string& s, vector<int> &pos, vector<Bor> &bor, int k) {
	int res[100000];
	memset(res, 0, sizeof(res));
	for (int i = 0, u = 0; i<s.size(); i++) {
		u = search_suffix(u, alphabet(s[i]), bor);
		for (int v = u; v != 0; v = search_suffix(v, bor))
			for (int j = 0; j<bor[v].number_P.size(); j++)
				if ((i + 1 - pos[bor[v].number - 1] - bor[v].number_P[j] + pos[bor[v].number - 1]) >= 0)
					res[i + 1 - pos[bor[v].number - 1] - bor[v].number_P[j] + pos[bor[v].number - 1]]++;
	}
	for (int i = 0; i<100000; i++)
		if (res[i] == k) cout << i + 1 << endl;
}

void add(const string &patt, int number, vector<int> &pos, vector<Bor> &bor, int j) {
	int index = 0;
	for (unsigned int i = 0, symb; i < patt.size(); i++) {
		symb = alphabet(patt[i]);
		if (bor[index].next[symb] == -1) {
			bor.push_back(make_Bor(index, symb));
			bor[index].next[symb] = bor.size() - 1;
		}
		index = bor[index].next[symb];
	}
	bor[index].flag = true;
	bor[index].number_P.push_back(number);
	bor[index].number = j;
	pos.push_back(patt.size());
}

int main() {
	vector<Bor> bor;
	vector<int> pos;
	string text, pattern, patt;
	char joker;
	bor.push_back(make_Bor(0, ' '));
	cin >> text >> pattern >> joker;
	int a = 0;
	for (int i = 0; i<pattern.size(); i++) {
		if (pattern[i] == joker) {
			if (patt != "")
			{
				add(patt, i, pos, bor, a + 1);
				a++;
				patt = "";
			}
		}
		else patt = patt + pattern[i];
	}
	if (patt != "") { 
		add(patt, pattern.size(), pos, bor, a + 1); 
		a++; 
	}
	search(text, pos, bor, a);
	return 0;
}