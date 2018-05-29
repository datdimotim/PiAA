#include <iostream>
#include <string>
#include <vector>
#include <cstring>

bool test = false; //  переменная тестирования 
// Глобальные переменные  - зло!

void getPrefix(std::vector <int> &ans,  std::string const &str);

void printAns(int ans){
	std::cout << ans << std::endl;
	exit(0);
}

int main(int argc, char** argv) {
	if (argc == 2 && !strcmp(argv[1], "-test\0"))
		test = true;
	std::string strA;
	std::string strB;
	std::vector <int> PrefixValue;

	std::cin >> strA >> strB;

	int answer = -1;
	if (strA.length() != strB.length())
		printAns(answer);

	std::string tmp = strA + strA;
	getPrefix(PrefixValue, strB);
	size_t k = 0;
	for (size_t i = 0; i < tmp.size(); i++){
		while (k > 0 && strB[k] != tmp[i])
			k = PrefixValue[k - 1];
		if (strB[k] == tmp[i])
			k++;
		if (k == strB.length()) {
			answer = (i + 1 - strB.length());
			break;
		}
	}
	printAns(answer);
}

void getPrefix(std::vector <int> &ans,  std::string const &str){
	ans.resize(str.length());	            
	ans[0] = 0;
    int k = 0;	
	for (size_t i = 1; i < str.length(); i++){	
		while ((k > 0) && (str[k] != str[i])) 
			k = ans[k - 1]; 
		if (str[k] == str[i])
			k++;
		ans[i] = k;
	}
}