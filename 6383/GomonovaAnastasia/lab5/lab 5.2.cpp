#include <iostream>
#include <fstream>
#include <vector>
#include <string>
 using namespace std;
// A =0; C = 1; G = 2; T = 3; N =4;
int lapsum(char c);

// Структура вершин автомата-бора
struct Pic
{
int out[6]; 					// номер вершины, в которую мы придем по символу с номером i в алфавите
int move[6]; 					// Запоминание перехода автомата
int par; 						// "отцовая вершина"
std::vector<int> num_str; 		// номера строки-образца, обозначаемого этой вершиной
bool f; 						// true - вершина - исходная строка, false - нет
int suff;					    // Ссылка на суффикс
int suff_g;					    // Ссылка на "хороший" суффикс
char c; 						// символ на ребре от par сюда 

Pic(int par, char ch);
};

Pic::Pic(int par, char c) : par(par), f(false), suff(-1), suff_g(-1), c(c)
{
for (int i = 0; i < 6; i++) 
out[i] = move[i] = -1;
}


class Bor
{
private:
std::vector<Pic> bor;           // Бор
std::vector< std::string > str; // Шаблоны

int get_suff(int v); 			// Получение суффикса
int get_move(int v, char ch);   // Куда пройти из v по c
int get_suff_g(int v); 			// Получение хорошего суффикса

std::vector<int> it; 			// "Массив" начал подшаблонов
int kol; 						// Количество подшаблонов
int lenght;

void way_M(int v, int i, int *C, int p);  

void in_bor(std::string &, int); // Добавление шаблона в бор

public:
Bor(std::string &P, char mask);

void AKG_M(const std::string &s);

};

// Конструктор для шаблона с маской
Bor::Bor(std::string &P, char mask)
{
kol = 0;
lenght = P.length();
P += mask;
int from = 0;
bor.push_back(*(new Pic(-1, (char)0)));

// Поиск подшаблонов с добавлением в бор
for (int i = 0; i < P.length(); i++)
{
// Если символ не джокер - игнорим и идём дальше
if (P[i] != mask)
continue;

// Если джокер "подряд" - игнорим
if (i - from == 0)
{
from = i + 1;
continue;
}

str.push_back(P.substr(from, i - from)); // "Создаём" подшаблон
it.push_back(from);                      // Место, откуда в шаблоне начинается подшаблон

in_bor(str[kol], kol);                   // Добавляем в бор

kol++;
from = i + 1;
}
}

void Bor::way_M(int v, int i, int *C, int p)
{

for (int u = v; u != 0; u = get_suff_g(u))
{
if (bor[u].f)
{
std::vector<int> a = bor[u].num_str;
for (int j = 0; j < a.size(); j++)
{
int pq = i - str[a[j]].length() - it[a[j]];


if ( (pq + lenght <= p) && pq>=0)
C[pq]++;
}
}
}
}

void Bor::AKG_M(const string &s)
{

int u = 0;
int *C = new int[s.length()]();
for (int i = 0; i < s.length(); i++)
{
u = get_move(u, s[i]);
way_M(u, i + 1, C, s.length());
}

for (int i = 0; i < s.length(); i++)
{
if (C[i] == kol)
std::cout << i + 1 << std::endl;
}
}

int main()
{
string T, P;
char mask;
cin >> T >> P >> mask;
Bor qw(P, mask);
qw.AKG_M(T);

}
int lapsum(char c)
{
switch (c)
{
case 'A': return 0;
case 'C': return 1;
case 'G': return 2;
case 'T': return 3;
case 'N': return 4;
default: return 5;
}
}

int Bor::get_suff(int v)
{
if (bor[v].suff == -1)
{
if (v == 0 || bor[v].par == 0)
bor[v].suff = 0;
else
bor[v].suff = get_move(get_suff(bor[v].par), bor[v].c);
}
return bor[v].suff;
}

int Bor::get_move(int v, char ch)
{
int CH = lapsum(ch);
if (bor[v].move[CH] == -1)
{
if (bor[v].out[CH] != -1)
bor[v].move[CH] = bor[v].out[CH];
else
{
if (!v)
bor[v].move[CH] = 0;
else
bor[v].move[CH] = get_move(get_suff(v), ch);
}
}
return bor[v].move[CH];
}

int Bor::get_suff_g(int v)
{
if (bor[v].suff_g == -1);
{
int u = get_suff(v);
if (!u)
bor[v].suff_g = 0;
else
bor[v].suff_g = (bor[u].f) ? u : get_suff_g(u);
}
return bor[v].suff_g;
}


void Bor::in_bor(string &dop, int i)
{
int num = 0;
for (int j = 0; j < dop.length(); j++)
{
int ch = lapsum(dop[j]);
if (bor[num].out[ch] == -1)
{
bor.push_back(*(new Pic(num, dop[j])));
bor[num].out[ch] = bor.size() - 1;
}
num = bor[num].out[ch];
}
bor[num].f = true;
bor[num].num_str.push_back(i);
}
