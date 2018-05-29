#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> prefix_function(string &str){
	vector<int> prefixs(str.length());
    for (int i = 1; i < str.length(); i++){
        int j = prefixs[i - 1];
        while ((j > 0) && (str[i] != str[j]))
            j = prefixs[j-1];
        if (str[i] == str[j])
            ++j; 
        prefixs[i] = j;
    }
	// vector<int> prefixs(str.length());
    // prefixs[0] = 0;
    // for(int i = 1; i < prefixs.size(); ++i){
        // int pos = prefixs[i-1];
        // while(pos > 0 && str[pos] != str[i])
            // pos = prefixs[pos-1];
        // prefixs[i] = pos + (str[pos] == str[i] ? 1 : 0);
    // }
	return prefixs;
}

int cycle(string &str1, string &str2){
    if (str1.length() != str2.length())
		return -1;
    string doub_str = str1 + str1;
    vector<int> prefixs = prefix_function(str2);
    int pos = 0;
    int index = -1;
    for(int i = 0; i < doub_str.size(); ++i) {
        while (pos > 0 && str2[pos] != doub_str[i])
            pos = prefixs[pos-1];
        if(str2[pos] == doub_str[i])
			pos++;
        if(pos == str2.length()){
            index = (i + 1 - str2.length());
            break;
        }
    }
    return index;
}
int main() {
    string str1, str2;
    cin >> str2;
    cin >> str1;
    cout << cycle(str1, str2);
    return 0;
}