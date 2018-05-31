#include <iostream>
#include <string>
#include <vector>

using namespace std;
vector<size_t> compute_prefix_function(const string& connection)
{
	int len = connection.length();
	vector<size_t> p(len);

	for (int i = 1; i < len; ++i) {
		size_t k = p[i - 1];
		while ((k > 0) && (connection[i] != connection[k]))
			k = p[k - 1];
		if (connection[i] == connection[k])
			++k;
		p[i] = k;
	}
	return p;
}

int main() {
	bool first = true;
	vector<size_t> q;
	string needle, haystack, connection;
	cin >> needle;
	cin >> haystack;
	connection = needle + "#" + haystack;
	q = compute_prefix_function(connection);
	
	for (int i = needle.length(); i<q.size(); i++) {
		if (q[i] == needle.length() && first) {
			cout << i - needle.length() * 2<<endl;
			first = false;
		}
		else if (q[i] == needle.length())
			cout << ", " << i - needle.length() * 2<<endl;
	}
	
	if (first)
		cout << "-1" << endl;
	system("pause");
	return 0;
}