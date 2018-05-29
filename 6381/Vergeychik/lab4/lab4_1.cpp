// lab4_1.cpp: определяет точку входа для консольного приложения.
//

#include <string>
#include <iostream>
#include <vector>

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

std::vector<int> findEntries(const std::string& text, const std::string& pattern) {
	std::vector<int> result;
	int patternLength = pattern.length();
	int* pref = prefix(pattern);
	int numberOfEquals= 0;

	for (int i = 0; i < text.length(); ++i)
	{
		while (pattern[numberOfEquals] != text[i] && numberOfEquals > 0)
		{
			numberOfEquals = pref[numberOfEquals - 1];//take new position for equals
		}
		if (pattern[numberOfEquals] == text[i])
		{
			numberOfEquals = numberOfEquals + 1;//go to the next symbol in the pattern
			if (numberOfEquals == patternLength)//we've found the pattern in the text
			{
				result.push_back(i + 1 - numberOfEquals);
				numberOfEquals = pref[numberOfEquals - 1];
			}
		}

	}
	return result;
}

int main()
{
	std::string pattern;
	std::string text;

	std::cin >> pattern;
	std::cin >> text;

	std::vector<int> entries = findEntries(text, pattern);

	if (entries.size()>0)
	{
		std::cout<<entries[0];
		for (int i = 1; i<entries.size(); i++)
		{
			std::cout<<","<< entries[i]<<std::endl;
		}

	}
	else
		std::cout<< - 1<<std::endl;

	return 0;
}
