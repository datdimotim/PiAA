// lab41
// Реализуйте алгоритм КМП и с его помощью для заданных шаблона P (|P|≤15000) и текста T (|T|≤5000000) найдите все вхождения P в T.

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
		while (suf > 0 && p[suf] != p[i])
			suf = res[suf - 1];
		if (p[suf] == p[i])
			suf++;
		res[i] = suf;
	}
	return res;
}

vector<int> findOccurrences(const string &t, const string &p) {
	vector<int> res;
	int pLength = p.length();
	int* pref = prefix(p);
	int numberOfEquals = 0;

	for (int i = 0; i < t.length(); ++i)
	{
		while ((p[numberOfEquals] != t[i]) && numberOfEquals > 0)
			numberOfEquals = pref[numberOfEquals - 1]; 
		if (p[numberOfEquals] == t[i])
		{
			numberOfEquals = numberOfEquals + 1; 
			if (numberOfEquals == pLength)
			{
				res.push_back(i + 1 - numberOfEquals);
				numberOfEquals = pref[numberOfEquals - 1];
			}
		}
	}
	return res;
}

int main()
{
    ifstream fin("piaa41.txt");
	string p;
	string t;
	fin >> p;
	fin >> t;
	vector<int> occurrences = findOccurrences(t, p);

	if (occurrences.size() > 0)
	{
		cout << occurrences[0];
		for (int i = 1; i < occurrences.size(); i++)
		{
			cout << "," << occurrences[i];
		}
	}
	else cout << - 1 << endl;

    fin.close();
	return 0;
}