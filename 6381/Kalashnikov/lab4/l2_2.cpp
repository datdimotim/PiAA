#include <iostream>
#include <vector>

using namespace std;

void compute_prefix_function(const string& s1, const string& s2, vector<size_t>& p) 
{
	size_t len1 = s1.length();
	size_t len2 = s2.length();
	 // значения префикс-функции
	                    // индекс вектора соответствует номеру последнего символа аргумента
	p[0] = 0; // для префикса из нуля и одного символа функция равна нулю

    int k = 0;	
	for (size_t i = 1; i < len1; ++i)
	{	
		while ( k > 0 && s1[k] != s1[i] ) 
			k = p[k - 1]; 
		if ( s1[k] == s1[i] )
			++k;
		p[i] = k;
	}
	
	p[len1] = 0;

	for(size_t i = 0; i < len2*2; ++i)
	{
		size_t k = p[i + len1];
		while( k > 0 && s1[k] != s2[i%len2] )
			k = p[k - 1];
		if ( s1[k] == s2[i%len2] )
			++k;
		p[len1 + 1 + i]=k;
	}
}

int main()
{
	string P, T;
    getline(cin, P);
    getline(cin, T);

	if(P.size() != T.size())
	{

		cout << -1;
		return 0;
	}

	P.shrink_to_fit();
	T.shrink_to_fit();

	vector<size_t> pref(T.size() + 2 * P.size(), 0);
	compute_prefix_function(T, P, pref);

		/* for(auto i: T)
		{
			cout << i << " ";
		}
		for(auto i: P)
		{
			cout << i << " ";
		}
		for(auto i: P)
		{
			cout << i << " ";
		}
		cout << endl;

		for(auto i: pref)
		{
			cout << i << " ";
		}
		cout << endl; */

	int offset = -1;
	for (unsigned sizeP = P.size(), sizePref = pref.size(), i = sizeP; i < sizePref; ++i)
	{
		if (pref.at(i) == sizeP)
		{
			offset = i - sizeP - T.size();
			break;
		}
	}
	cout <<  offset;

	return 0;
}

