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

int algorithm_KMP(const string& S, const string& pattern){ 
	vector<size_t> pi = prefix_function(pattern); 

	for (size_t k = 0, i = 0; i < S.length(); ++i){ 
		while ((k > 0) && (pattern[k] != S[i]))		k = pi[k-1]; 

		if (pattern[k] == S[i])		k++; 

		if (k == pattern.length())	return (i - pattern.length() + 1); 
	} 
	return -1; 
} 

int main() { 
	string A, B; 
	getline(cin, A); 
	getline(cin, B); 
	cout << algorithm_KMP(A + A, B) << endl; 
	return 0; 
}