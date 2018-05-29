#include <string> 
#include <vector> 
#include <iostream> 

using namespace std; 

vector<size_t> prefix_function(const string& pattern) { 
	vector<size_t> pi (pattern.length()); 
	pi[0] = 0; 
	for (size_t k = 0, i = 1; i < pattern.length(); ++i) { 

		while ((k > 0) && (pattern[i] != pattern[k]))	k = pi[k-1]; 

		if (pattern[i] == pattern[k])	k++; 

		pi[i] = k; 
	} 
	return pi; 
} 

void algorithm_KMP(const string& str, const string& pattern, vector<size_t>& positions) { 
	vector<size_t> pi = prefix_function(pattern); 

	for (size_t k = 0, i = 0; i < str.length(); ++i){ 
		while ((k > 0) && (pattern[k] != str[i]))		k = pi[k-1]; 

		if (pattern[k] == str[i])		k++; 

		if (k == pattern.length())	positions.push_back(i - pattern.length() + 1); 
	} 

	if(positions.size() == 0)	positions.push_back(-1); 
} 

int main() { 
	string P, T; 
	vector<size_t> entry_positions; 
	getline(cin, P);// шаблон 
	getline(cin, T);// текст

	algorithm_KMP(T, P, entry_positions); 

	size_t i = 0; 
	for(const auto& pos : entry_positions) { 
		cout << pos; 
		if(i != entry_positions.size() - 1) cout << ","; 
		i++; 
	} 
	cout << endl; 

return 0; 
}