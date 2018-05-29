#include <iostream>
#include <vector>

using namespace std;

vector<size_t> compute_prefix_function(string s) 
{
	size_t len = s.length();
	vector<size_t> p(len); // значения префикс-функции
	                    // индекс вектора соответствует номеру последнего символа аргумента
	p[0] = 0; // для префикса из нуля и одного символа функция равна нулю

    int k = 0;	
	for (size_t i = 1; i < len; ++i) {	
		while ((k > 0) && (s[k] != s[i])) 
			k = p[k - 1]; 
		if (s[k] == s[i])
			++k;
		p[i] = k;
	}
	return p;
}

int main()
{
	string P, T, res;
	cin >> P;
	cin >> T;

	size_t P_len = P.length();
	P += '~' + T;

	vector<size_t> pref = compute_prefix_function(P);

    for (auto i: P)
    {
        cout << i << " ";
    }
	cout << endl;
    for (auto i: pref)
    {
        cout << i << " ";
    }
    cout << endl;

	for(size_t i = 0; i < pref.size(); i++)
	{
		if(pref[i] == P_len)
		{
			res += to_string(i - 2*P_len) + ',';
		}
	}

	if(res.size() != 0)
	{
		res.pop_back();
		cout << res;
	}
	else
	{
		cout << "-1" << endl;
	}

	return 0;
}

