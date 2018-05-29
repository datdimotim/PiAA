#include <string> 
#include <vector> 
#include <iostream> 

using namespace std; 

vector<int> prefix_function(const string& pattern) { 
	vector<int> pi (pattern.length()); 
	pi[0] = 0; 
	for (int k = 0, i = 1; i < pattern.length(); ++i) { 

		while ((k > 0) && (pattern[i] != pattern[k]))	k = pi[k-1]; 

		if (pattern[i] == pattern[k])	k++; 

		pi[i] = k; 
	} 
	return pi; 
} 

void KMP(const string& str, const string& pattern, vector<int>& positions) { 
	vector<int> pi = prefix_function(pattern); 

	for (int k = 0, i = 0; i < str.length(); ++i){ 
		while ((k > 0) && (pattern[k] != str[i]))		k = pi[k-1]; 

		if (pattern[k] == str[i])		k++; 

		if (k == pattern.length())	positions.push_back(i - pattern.length() + 1); 
	} 

	if(positions.size() == 0)	positions.push_back(-1); 
} 

int main()
 { 
	string P, T; 
	vector<int> entry_positions; 
	getline(cin, P);// шаблон 
	getline(cin, T);// текст

	KMP(T, P, entry_positions); 

	size_t i = 0; 
	for (i; i < entry_positions.size(); i++) 
	{ 
		cout << entry_positions[i]; 
		if(i != entry_positions.size() - 1) cout << ","; 
	} 
	cout << endl; 

return 0; 
}