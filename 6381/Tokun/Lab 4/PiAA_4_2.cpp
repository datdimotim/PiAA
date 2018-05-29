#include <iostream>
#include <string>
#include <vector>

using namespace std;

void prefix(vector<int> &values, const string &line)
{
	values.resize(line.size());
	values[0] = 0;
	for (unsigned int i = 1; i < values.size(); i++)
    {
		int k = values[i - 1];
		while (k > 0 && line[k] != line[i]) k = values[k - 1];
		values[i] = k + (line[k] == line[i] ? 1 : 0);
	}
}

int main()
{
	string line_1;
    string line_2;

	vector<int> values;
    
	cin >> line_1 >> line_2;
	if (line_1.length() == line_2.length())
    {
		string double_line = line_1 + line_1;
        int answer = -1;

		prefix(values, line_2);
		for (int i = 0, k = 0; i < double_line.size(); ++i)
        {
			while (k > 0 && line_2[k] != double_line[i]) k = values[k - 1];
			if (line_2[k] == double_line[i]) k++;
			if (k == line_2.length())
            {
				answer = (i + 1 - line_2.length());
				break;
			}
		}
		cout << answer;
	}
	else cout << -1;
	return 0;
}