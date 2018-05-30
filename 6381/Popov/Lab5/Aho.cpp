#include<iostream>
#include<string>
#include<vector>
#include<map>

using namespace std;

class Vrtx{
public:
	map<char, int> next_vrtx, auto_move;
	int pat_num = -1, suff_link = -1, good_suff_link = -1, parent;
	char prev;
	
	Vrtx(char, int);
};

vector<Vrtx> bohr;
vector<string> pattern;

Vrtx::Vrtx(char prev = '0', int parent = 0) : prev(prev), parent(parent){}

void readTextAndPatt(string &text){
	int count;
	cin >> text >> count;
	pattern.resize(count);
	for(int i = 0; i < count; i++)
		cin >> pattern[i];
}

void addStrToBohr(){
	int num;
	for(int i = 0; i < pattern.size(); i++){
		num = 0;
		for(int j = 0; j < pattern[i].length(); j++){
			if(!bohr[num].next_vrtx.count(pattern[i][j])){
				bohr[num].next_vrtx[pattern[i][j]] = bohr.size();
				bohr.emplace_back(pattern[i][j], num);
			}
			num = bohr[num].next_vrtx[pattern[i][j]];
		}
		bohr[num].pat_num = i;
	}
}

int getAutoMove(int, char);
 
int getSuffLink(int ind){
	if(bohr[ind].suff_link == -1){
		if(ind == 0 || bohr[ind].parent == 0)
			bohr[ind].suff_link = 0;
		else{
			bohr[ind].suff_link = getAutoMove(getSuffLink(bohr[ind].parent), bohr[ind].prev);
		}
	}
	return bohr[ind].suff_link;
}

int getAutoMove(int ind, char ch){
	if(!bohr[ind].auto_move.count(ch))
		if(bohr[ind].next_vrtx.count(ch))
			bohr[ind].auto_move[ch] = bohr[ind].next_vrtx[ch];
		else{
			if(!ind)
				bohr[ind].auto_move[ch] = 0;
			else
				bohr[ind].auto_move[ch] = getAutoMove(getSuffLink(ind), ch);
		}
	return bohr[ind].auto_move[ch];
}

int getGoodSuffLink(int ind){
	if(bohr[ind].good_suff_link == -1){
		int i = getSuffLink(ind);
		if(!i)
			bohr[ind].good_suff_link = 0;
		else
			bohr[ind].good_suff_link = bohr[i].pat_num != -1 ? i : getGoodSuffLink(i);
	}
	return bohr[ind].good_suff_link;
}

void check(int curr, int end_symb){
	for(int i = curr; i != 0; i = getGoodSuffLink(i))
		if(bohr[i].pat_num != -1)
			cout << end_symb - pattern[bohr[i].pat_num].length() + 1 << ' ' << bohr[i].pat_num + 1 << endl;
}

void findAllPos(string text){
	int u = 0;
	for(int i = 0; i < text.length(); i++){
		u = getAutoMove(u, text[i]);
		check(u, i + 1);
	}
}

int main() {
	bohr.emplace_back();
	string text;
	readTextAndPatt(text);
	addStrToBohr();
	findAllPos(text);
    return 0;
}