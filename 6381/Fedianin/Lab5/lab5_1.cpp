#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>

using namespace std;

const vector<char> alphabet = {'A', 'C', 'G', 'T', 'N'};

int GetIndInAlphabet(char ch) {
   for(int i = 0; i < alphabet.size(); ++i) {
      if(alphabet[i] == ch)
         return i;
   }
   throw out_of_range(string("There is no symbol '") + ch + "' in alphabet");
}

struct TrieVrtx{
   //номер вершины в которую мы придем по символу номер i в алфавите
   vector<int> next_vrtx;

   //номера шаблонов в данной вершине
   vector<int> pat_nums;

   //суффиксные ссылки
   int suff_link = -1;
   int suff_flink = -1; //"хорошая"

   //запоминание перехода автомата
   vector<int> auto_move;

   //вершина-родитель в дереве
   int parent;

   //является ли вершина строкой
   bool flag = false;

   //символ на ребре от parent к этой вершине
   char symb;
};

struct Trie {
	Trie() { trie.push_back(MakeTrieVrtx(0,'$')); }; //инициализация бора
	
	TrieVrtx MakeTrieVrtx(int p, char c) { //создание новой вершины

	  TrieVrtx v;

	  //заполнение элементов вектора значениями -1
	  v.next_vrtx = vector<int>(alphabet.size(), -1);
	  v.auto_move = vector<int>(alphabet.size(), -1);

	  v.parent = p;
	  v.symb = c;

	  return v;
	}

	int GetSuffLink(int v) {
	  if (trie[v].suff_link == -1) //если еще не считали
		 //если v - корень или предок v - корень
		 if (v == 0 || trie[v].parent == 0)
			trie[v].suff_link = 0;
		 else 
			trie[v].suff_link = GetAutoMove
			(GetSuffLink(trie[v].parent), GetIndInAlphabet(trie[v].symb));
	  return trie[v].suff_link;
	}

	int GetAutoMove(int v, int ch) {
	  if (trie[v].auto_move[ch] == -1){
		 if (trie[v].next_vrtx[ch] != -1)	trie[v].auto_move[ch] = trie[v].next_vrtx[ch];
		 else{
			if (v == 0)		trie[v].auto_move[ch] = 0;
			else			trie[v].auto_move[ch] = GetAutoMove(GetSuffLink(v), ch);
		 }
	  }
	  return trie[v].auto_move[ch];
	}

	int GetSuffFLink(int v) {
	  if (trie[v].suff_flink == -1) {
		 int u = GetSuffLink(v);
		 if (u == 0)	trie[v].suff_flink = 0;
		 else			trie[v].suff_flink = (trie[u].flag) ? u : GetSuffFLink(u);
	  }
	  return trie[v].suff_flink;
	}

	void Check(int v, int i) {
	   for(int u = v; u != 0; u = GetSuffFLink(u)) {
		   if (trie[u].flag) {// если true
			   for(const auto& num : trie[u].pat_nums) {
				  int pos_in_text = i - pattern[num].length();
				  all_poss.push_back(pos_in_text);
				  nums_of_pattern.push_back(num);
			   }
		   }
	   }
	}

	void FindAllPos(const string& s) {
	   int u = 0;
	   for(size_t i = 0; i < s.length(); i++) {
		   u = GetAutoMove(u, GetIndInAlphabet(s[i]));
		   Check(u, i+1);
	   }
	}

	//добавление строки в бор
	void AddStringToTrie(const string& s) {
	  int num = 0;
	  for (size_t i = 0; i < s.length(); ++i) {
		 size_t ind = GetIndInAlphabet(s[i]);
		 if (trie[num].next_vrtx[ind] == -1) { //если ребро отсутствует
			trie.push_back(MakeTrieVrtx(num, s[i]));
			trie[num].next_vrtx[ind] = trie.size() - 1;
		 }
		 num = trie[num].next_vrtx[ind];
	  }

	  trie[num].flag = true;
	  pattern.push_back(s);
	  trie[num].pat_nums.push_back(pattern.size() - 1);
	}

	vector<TrieVrtx> trie; //вершины бора
	vector<string> pattern; //хранит набор максимальных подстрок без джокеров;

	//все позиции вхождения шаблонов в текст
	vector<int> all_poss;

	//номера шаблонов, которые содержатся в тексте
	vector<int> nums_of_pattern;
};

int main(){
   Trie tr;
   string text, patt;
   int n;
   cin >> text >> n;
   for(size_t i = 0; i < n; ++i) {
      cin >> patt;
      tr.AddStringToTrie(patt);
   }
   tr.FindAllPos(text);
   for(size_t i = 0; i < tr.all_poss.size(); ++i) 
       cout << tr.all_poss[i] + 1 << " " << tr.nums_of_pattern[i] + 1 <<endl;
}