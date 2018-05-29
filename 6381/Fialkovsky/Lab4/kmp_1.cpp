#include <iostream>
#include <string>
#include <vector>
#include <cstring>

bool test = false; //  переменная тестирования 
// Глобальные переменные  - зло!

void getPrefix(std::vector <int> &ans,  std::string const &str);

int main(int argc, char** argv) {
	if (argc == 2 && !strcmp(argv[1], "-test\0"))
		test = true;

	std::string Needle;
	std::string HayStack;
	std::vector <int> answer;
	std::vector <int> PrefixValue;
	size_t k = 0;

	std::cin >> Needle >> HayStack;

	getPrefix(PrefixValue, Needle);
	if (test){
		std::cout << "Prefix Func Values:\n";
		for (auto const &elem: Needle)
			std::cout << elem << " ";
		std::cout << std::endl;
		for (auto const &elem: PrefixValue)
			std::cout << elem << " ";
		std::cout << std::endl << std::endl;
	}

	for (size_t i = 0; i < HayStack.size(); ++i) {
		if (test) std::cout << "Compare pos " << i << " in Haystack and ";
		while (k > 0 && (k >= Needle.size() || Needle[k] != HayStack[i]))
			k = PrefixValue[k - 1];
		if (test) std::cout << k << " pos in Needle\n";
		if (HayStack[i] == Needle[k]) 
			k++;
		if (k == Needle.size())
			answer.push_back(i - k + 1);
	}
	if (answer.size() > 0) {
		for (size_t i = 0; i < answer.size() - 1; i++)
			std::cout << answer[i] << "," ;
		std::cout << answer.back();
	}
	else 
		std::cout << "-1" << std::endl;
	return 0;
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