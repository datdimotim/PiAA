﻿#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#define alph 52

using namespace std;

struct Bohr {
	int next_vrtx[alph];
	int pattern_num;
	bool flag;
	int suff_link;
	int auto_move[alph];
	int par; 
	char symb; 
};

vector<Bohr> bohr;
vector<string> pattern;


Bohr make_bohr(int p, char c) {
	Bohr v;
	memset(v.next_vrtx, 255, sizeof(v.next_vrtx));
	v.flag = false;
	v.suff_link = -1;
	memset(v.auto_move, 255, sizeof(v.auto_move));
	v.par = p;
	v.symb = c;
	return v;
}

void init_bohr() {
	bohr.push_back(make_bohr(0, 255));
}


void add_pattern_to_bohr(const string& s) {
	int num = 0; 
	for (int i = 0; i<s.length(); i++) {
		char ch = s[i] - 'A'; 
		if (bohr[num].next_vrtx[ch] == -1) {
			bohr.push_back(make_bohr(num, ch));
			bohr[num].next_vrtx[ch] = bohr.size() - 1;
		}
		num = bohr[num].next_vrtx[ch];
	}
	bohr[num].flag = true;
	pattern.push_back(s);
	bohr[num].pattern_num = pattern.size() - 1;
}

int get_auto_move(int v, char ch);

int get_suff_link(int v) {
	if (bohr[v].suff_link == -1)
		if (v == 0 || bohr[v].par == 0) 
			bohr[v].suff_link = 0;
		else
			bohr[v].suff_link = get_auto_move(get_suff_link(bohr[v].par), bohr[v].symb);
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
		if (bohr[u].flag) cout << i - pattern[bohr[u].pattern_num].length() + 1 << " " << bohr[u].pattern_num + 1 << endl;
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
	init_bohr();
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
