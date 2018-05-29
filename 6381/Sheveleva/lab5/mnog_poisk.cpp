#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

struct Vertex
{
    int next[5],
	    suffix = -1,
	    suffix_next[5], 
	    parent;//отец вершины
	vector <int> nomber;//номер шаблона 
    bool end_pat = false;//окончание шаблона
    int symb;//следующая вершина
    int nom = 0;
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

void add_string(const string &pattern, int nomber, vector<int> &pos, vector<Vertex> &bor, int j){
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
   bor[index].nomber.push_back(nomber);
   bor[index].nom=j;
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

void search(const string& s, vector<int> &pos, vector<Vertex> &bor, int kol)
{
    int res[100000];
	memset(res, 0, sizeof(res));
    for(int i=0, u=0; i<s.size(); i++)
    {
        u = search_suffix(u,search_alfa(s[i]), bor);
        for(int v=u;v!=0;v=search_suffix(v, bor))
			for(int j=0; j<bor[v].nomber.size();j++)
				if((i + 1 - pos[bor[v].nom-1] - bor[v].nomber[j] + pos[bor[v].nom-1]) >= 0) 
					res[i + 1 - pos[bor[v].nom-1] - bor[v].nomber[j] + pos[bor[v].nom-1]]++;
    }
     for(int i=0; i<100000; i++)
		if(res[i]==kol) cout<<i+1<<endl;
}

int main()
{
	vector<Vertex> bor;
	vector<int>pos;
    bor.push_back(make_vertex(0,' '));
    string text, pattern, patt="";
    char joker;
    
    cin >> text >> pattern >> joker;
    int j=0;
    
    for(int i=0; i<pattern.size(); i++)
    {
		if(pattern[i]==joker)
		{
			if(patt != "")
			{
				add_string(patt, i, pos, bor, j+1);
				j++;
				patt="";
			}
		}
		else patt=patt+pattern[i];
	}
	if(patt != "") {add_string(patt, pattern.size(), pos, bor,j+1); j++;}
	
    search (text, pos, bor, j);
	return 0;
}
