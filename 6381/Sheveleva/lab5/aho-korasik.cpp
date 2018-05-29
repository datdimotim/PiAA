#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

struct Vertex
{
    int next[5],
		nomber,//номер шаблона
	    suffix = -1,
	    suffix_next[5], 
	    parent;//отец вершины
    bool end_pat = false;//окончание шаблона
    int symb;//следующая вершина
};

int search_alfa (char a)
{
    char alfabet[] = {'A','C','G','T','N'};
	for(int i=0; i<5; i++)
		if(alfabet[i]==a) return i;
}

Vertex make_vertex(int p,int c)
{
   Vertex v;
   memset(v.next, -1, sizeof(v.next));
   memset(v.suffix_next, -1, sizeof(v.suffix_next));
   v.parent=p;
   v.symb=c;
   return v;
}

void add_string(const string &pattern, int nomber, vector<int> &pos, vector<Vertex> &bor){
   int index = 0;
   for (unsigned int i=0, symb; i < pattern.size(); i++)
   {
      symb = search_alfa(pattern[i]);
      if (bor[index].next[symb] == -1)
      {
         bor.push_back(make_vertex(index,symb));
         bor[index].next[symb] = bor.size() - 1;
      }
      index = bor[index].next[symb];
   }
   bor[index].end_pat = true;
   bor[index].nomber = nomber;
   pos.push_back(pattern.size());
}

int search_suffix(int v, int ch, vector<Vertex> &bor);

int search_suffix (int v, vector<Vertex> &bor){
   if (bor[v].suffix == -1)
   {
      if (v==0 || bor[v].parent==0)
         bor[v].suffix = 0;
      else
         bor[v].suffix = search_suffix(search_suffix(bor[v].parent, bor), bor[v].symb, bor);
	}
   return bor[v].suffix;
}

int search_suffix (int v, int ch, vector<Vertex> &bor){
   if (bor[v].suffix_next[ch]==-1)
   {
      if (bor[v].next[ch]!=-1)
         bor[v].suffix_next[ch]=bor[v].next[ch];
      else
         if (v==0)
            bor[v].suffix_next[ch]=0;
         else
            bor[v].suffix_next[ch]=search_suffix(search_suffix(v, bor), ch, bor);
    }
   return bor[v].suffix_next[ch];
}

void search (const string& s, vector<int> &pos, vector<Vertex> &bor)
{
	int u=0;
    for(unsigned int i=0, t=0; i<s.size(); i++){
		if(bor[u].end_pat)
		{
			cout<<i - pos[bor[u].nomber-1] + 1<<' '<<bor[u].nomber<<endl;
			
			t = search_suffix(u, bor);
			if(bor[t].end_pat) cout<<i - pos[bor[t].nomber-1] + 1<<' '<<bor[t].nomber<<endl;
			
			u = search_suffix(u, search_alfa(s[i]), bor);
		}
        else if(bor[u].next[search_alfa(s[i])] != -1) u = bor[u].next[search_alfa(s[i])];
			 else u = search_suffix(u, search_alfa(s[i]), bor);
    }
    if(bor[u].end_pat) cout<<s.size() - pos[bor[u].nomber-1] + 1<<' '<<bor[u].nomber<<endl;
}

int main()
{
	vector<Vertex> bor;
	vector<int>pos;
    bor.push_back(make_vertex(0,' '));
    string text, pattern;
    int ind;
    
    cin >> text >> ind;
    for (int i=0; i<ind; i++)
    {
		cin >> pattern;
		add_string(pattern, i + 1, pos, bor);
	}
	
    search (text, pos, bor); 
	return 0;
}
