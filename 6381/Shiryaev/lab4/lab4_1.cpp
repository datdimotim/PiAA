#include <iostream>
#include <vector>
#include <string>
#include <cstddef>

using namespace std;

vector<size_t> prefix_function (string s);

int main(){
	string text;
	string tmplt;
	const char *c = "@"; 
	int n = 0;
	vector<size_t> kmp;
	vector<size_t> res;
	cin >> tmplt;
	cin >> text;
	n = tmplt.size();
	text = tmplt + c + text;
	kmp = prefix_function(text);
	for (int i = 0; i < kmp.size(); ++i){
		if (n == kmp[i]){
			res.push_back(i);
		}
	}
	if(!res.empty()){
		for (int i = 0; i < res.size(); ++i){
			if(i != res.size()-1)
				cout << res[i] - 2*n << ",";
			else
				cout << res[i] - 2*n;
		}
	}
	else
		cout << -1;
}

vector<size_t> prefix_function (string s) 
{
    size_t n =  s.length();
    vector<size_t> pi(n); // в i-м элементе (его индекс i-1) количество совпавших символов в начале и конце для построки длины i. 
			 // p[0]=0 всегда, p[1]=1, если начинается с двух одинаковых 
    for (size_t i=1; i<n; ++i) 
    {
        size_t j = pi[i-1];
        while ((j > 0) && (s[i] != s[j])) // не равны
            j = pi[j-1];				// берем ранее рассчитанное значение (начиная с максимально возможных)
        if (s[i] == s[j]) // равны 
            ++j; 
        pi[i] = j;
     }
     return pi;
}