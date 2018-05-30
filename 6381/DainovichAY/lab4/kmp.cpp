#include <iostream>
#include <string>
#include <vector>

using namespace std;

void prefix_func(const string &needle, vector<int> &z) {
    z.resize(needle.size());
    z[0] = 0;
    for (int i=1;i<z.size();++i) {
        int pos = z[i-1];
        while (pos > 0 && needle[pos] != needle[i])
            pos = z[pos-1];
        z[i] = pos + (needle[pos] == needle[i] ? 1 : 0);
    }
}
vector<int> kmp(const string &haystack, const string &needle) {
    vector<int> answer;
    vector<int> z;
    prefix_func(needle,z);
    int pos = 0;
    for (int i=0; i<haystack.size(); ++i) {
        while (pos > 0 && (pos >= needle.size() || needle[pos] != haystack[i]) )
            pos = z[pos-1];
        if (haystack[i] == needle[pos]) pos++;
        if (pos == needle.size())
            answer.push_back(i - pos + 1);
    }
    return answer;
}

int main() {
    string needle, haystack;
    vector<int> answer;
    cin >> needle;
    cin >> haystack;
    answer = kmp(haystack,needle);
    if (answer.size() == 0) {
        cout << "-1"; 
        return 0;
    }
    for (int i = 0; i < answer.size() - 1; i++)
        cout << answer[i] << ",";
    cout << answer.back();
    return 0;
}
