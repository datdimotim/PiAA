// lab4_2.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <vector>
#include <string>

int* prefix(const std::string& pattern) {
	int *result = new int[pattern.length()];//prefix values
	result[0] = 0;
	int j = 0;//to control the suffix
	for (int i = 1; i < pattern.length(); i++)
	{
		while (j > 0 && pattern[j] != pattern[i])//try to find how much symbols in the suffix are equals the prefix
			j = result[j - 1];
		if (pattern[j] == pattern[i])//if symbols are equals, go to the next symbol in the suffix
			j++;
		result[i] = j;
	}
	return result;
}

int findEntries(std::string text, std::string pattern) {
	int* pref = prefix(pattern);
	int patternLength = pattern.length();
	int numberOfEquals = 0;
	for (int i = 0; i<text.length(); ++i) {
		while (pattern[numberOfEquals] != text[i] && numberOfEquals > 0)
		{
			numberOfEquals = pref[numberOfEquals - 1];//take new position for equals
		}
		if (pattern[numberOfEquals] == text[i])
		{
			numberOfEquals = numberOfEquals + 1;//go to the next symbol in the pattern
			if (numberOfEquals == patternLength)//we've found the pattern in the text
			{
				return i + 1 - numberOfEquals;
			}
		}
	}
	return -1;
}

int main() {
	std::string text, pattern;
	std::cin >> text >> pattern;

	std::cout << findEntries(text + text, pattern)<<std::endl;

	return 0;
}
