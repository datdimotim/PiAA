// lab42
// Заданы две строки A (|A|≤5000000) и B (|B|≤5000000). Определить, является ли А циклическим сдвигом В (это значит, что А и В имеют одинаковую длину и А состоит из суффикса В, склеенного с префиксом В).

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int* prefix(const string &p) {
	int *res = new int[p.length()];
	res[0] = 0;
	int suf = 0;
	for (int i = 1; i < p.length(); i++)
	{
		while (suf > 0 && p[suf] != p[i])   suf = res[suf - 1];
		if (p[suf] == p[i]) suf++;
		res[i] = suf;
	}
	return res;
}

int findOccurrences(string t, string p) {
	int* pref = prefix(p);
	int pLength = p.length();
	int numberOfEquals = 0;

	for (int i = 0; i < t.length(); ++i) {
		while ((p[numberOfEquals] != t[i]) && numberOfEquals > 0)
			numberOfEquals = pref[numberOfEquals - 1];
		if (p[numberOfEquals] == t[i])
		{
			numberOfEquals = numberOfEquals + 1;
			if (numberOfEquals == pLength)
				return i + 1 - numberOfEquals;
		}
	}
	return -1;
}

int main() {
    ifstream fin("piaa42.txt");
    string p; // pattern
	string t; // text
    fin >> t;
	fin >> p;

	cout << findOccurrences(t + t, p) << endl;

    fin.close();
	return 0;
}