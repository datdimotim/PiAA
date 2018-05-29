#include <iostream>
#include <string>
#include <vector>

using namespace std;

void prefix(vector<int> &values, const string &obraz)
{
	values.resize(obraz.size());
	values[0] = 0;
	for (unsigned int i = 1; i < values.size(); i++)
    {
		int k = values[i - 1];
		while (k > 0 && obraz[k] != obraz[i]) k = values[k - 1];
		values[i] = k + (obraz[k] == obraz[i] ? 1 : 0);
	}
}

int main()
{
	string obraz;
    string line;
	
    vector<int> values;
	vector<int> answer;

	cin >> obraz >> line;
	prefix(values, obraz);
	for (unsigned int i = 0, k = 0; i < line.size(); i++)
    {
		while (k > 0 && (k >= obraz.size() || obraz[k] != line[i])) k = values[k - 1];
		if (line[i] == obraz[k]) k++;
		if (k == obraz.size()) answer.push_back(i - k + 1);
	}
	if (answer.size() > 0)
    {
		for (unsigned int i = 0; i < answer.size() - 1; i++) cout << answer[i] << "," ;
		cout << answer.back();
	}
	else cout << -1 << endl;
	return 0;
}