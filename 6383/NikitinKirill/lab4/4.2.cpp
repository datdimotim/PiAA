#include <iostream>
#include <string>
#include <vector>

using namespace std;

void prefix_func(const string &str, vector<int> &z) {
    z.resize(str.size());
    z[0] = 0;
    for (int i=1;i<z.size();++i) {
        int pos = z[i-1];
        while (pos > 0 && str[pos] != str[i])
            pos = z[pos-1];
        z[i] = pos + (str[pos] == str[i] ? 1 : 0);
    }
}

int cycle(const std::string & text, const std::string & str)
{
    if (text.length() != str.length()) return -1;
    string new_s = text + text;
    vector<int> z;
    prefix_func(str,z);
    int pos = 0;
    int answer = -1;
    for (int i=0; i<new_s.size(); ++i) {
        while (pos > 0 && str[pos] != new_s[i])
            pos = z[pos-1];
        if (str[pos] == new_s[i]) pos++;
        if (pos == str.length())
        {
            answer = (i + 1 - str.length());
            break;
        }
    }
    return answer;
}
int main() {
    string a,b;
    cin >> a;
    cin >> b;
    cout << cycle(a,b);
    return 0;
}
