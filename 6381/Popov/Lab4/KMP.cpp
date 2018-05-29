#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> prefix_function(string str){
    vector<int> indexs;
    vector<int> prefixs(str.length());
    for (int i = 1; i < str.length(); i++){
        int j = prefixs[i - 1];
        while ((j > 0) && (str[i] != str[j]))
            j = prefixs[j-1];
        if (str[i] == str[j])
            ++j; 
        prefixs[i] = j;
    }
	int size_obr = 0;
	while(str[size_obr] != '@')
		++size_obr;
	int i = 0;
	for(int x: prefixs){
		if(x == size_obr)
			indexs.push_back(i - 2 * size_obr);
		i++;
	}
    return indexs;
} 

int main() {
    string P, T;
    cin >> P;
    cin >> T;
	P += '@';
	P += T;
    vector<int> indexs = prefix_function(P);
	if(!indexs.empty())
		for(int index: indexs)
			if(index == indexs[0])
				cout << index;
			else
				cout << "," << index;
	else
		cout << "-1";
    return 0;
}