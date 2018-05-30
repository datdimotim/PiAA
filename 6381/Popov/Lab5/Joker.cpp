#include <iostream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

struct Vrtx {
	vector<int> pattern_num;
	bool flag;
	map<char, int> next_vrtx, auto_move;
	int pat_num = -1, suff_link = -1, parent;
	char prev;
	
	Vrtx(char, int);
};


vector<Vrtx> bohr;
vector<string> split_pattern;
Vrtx::Vrtx(char prev = '0', int parent = 0) : prev(prev), parent(parent){}

void add_pattern_to_bohr(string& pat) {
	int num = 0;
		for(int j = 0; j < pat.length(); j++){
			if(!bohr[num].next_vrtx.count(pat[j])){
				bohr[num].next_vrtx[pat[j]] = bohr.size();
				bohr.emplace_back(pat[j], num);
			}
			num = bohr[num].next_vrtx[pat[j]];
		}
	bohr[num].flag = true;
	split_pattern.push_back(pat);
	bohr[num].pattern_num.push_back(split_pattern.size() - 1);
}

int get_auto_move(int ind, char ch);

int get_suff_link(int ind) {
	if (bohr[ind].suff_link == -1)
		if (!ind || !bohr[ind].parent)
			bohr[ind].suff_link = 0;
		else
			bohr[ind].suff_link = get_auto_move(get_suff_link(bohr[ind].parent), bohr[ind].prev);
	return bohr[ind].suff_link;
}

int get_auto_move(int ind, char ch) {
	if (!bohr[ind].auto_move.count(ch))
		if (bohr[ind].next_vrtx.count(ch))
			bohr[ind].auto_move[ch] = bohr[ind].next_vrtx[ch];
		else
			if (ind == 0)
				bohr[ind].auto_move[ch] = 0;
			else
				bohr[ind].auto_move[ch] = get_auto_move(get_suff_link(ind), ch);
	return bohr[ind].auto_move[ch];
}

void check(int ind, int i, vector<int>& count, const vector<int>& lenght) {
	for (int u = ind; u != 0; u = get_suff_link(u))
		if (bohr[u].flag)
			for (const auto& it : bohr[u].pattern_num)
				if (i - lenght[it]<count.size())
					count[i - lenght[it]]++;
}

void find_all_pos(const string& text, vector<int>& count, const vector<int>& lenght) {
	int u = 0;
	for (size_t i = 0; i < text.length(); i++) {
		u = get_auto_move(u, text[i]);
		check(u, i + 1, count, lenght);
	}
}

vector<int> splitPattern(stringstream& str_pat, char joker) {
	vector<int> lenght;
	int len = 0;
	string tmp;
	while (getline(str_pat, tmp, joker)) {
		if (tmp.size()>0) {
			len += tmp.size();
			lenght.push_back(len);
			add_pattern_to_bohr(tmp);
		}
		len++;
	}
	return lenght;
}

void print(const vector<int>& count, int text_size, int pattern_size) {
	for (int i = 0; i<text_size; i++) {
		if (count[i] == pattern_size)
			cout << i + 1 << "\n";
	}
}

int main(){
	bohr.emplace_back();
	string text, pattern;
	char joker;
	cin >> text >> pattern >> joker;
	stringstream str_pat(pattern);
	vector<int> count(text.size(), 0);
	vector<int> lenght = splitPattern(str_pat, joker);
	find_all_pos(text, count, lenght);
	print(count, text.size(), split_pattern.size());
	return 0;
}