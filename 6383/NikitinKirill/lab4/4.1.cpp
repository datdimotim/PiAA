#include <iostream>
# include <string>
# include <vector>

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
vector<int> kmp(const string &text, const string &str) {
    vector<int> answer;
    vector<int> z;
    prefix_func(str,z);
    int pos = 0;
    for (int i=0; i<text.size(); ++i) {
        while (pos > 0 && (pos >= str.size() || str[pos] != text[i]) )
            pos = z[pos-1];
        if (text[i] == str[pos]) pos++;
        if (pos == str.size())
            answer.push_back(i - pos + 1);
    }
    return answer;
}

int main() {
    string P, T;
    vector<int> answer;
    cin >> P;
    cin >>T;
    answer = kmp(T,P);
    if (answer.size() == 0) {cout << "-1"; return 0;}
    for (int i = 0; i < answer.size() - 1; i++)
        cout << answer[i] << ",";
    cout << answer.back();
    return 0;
}
