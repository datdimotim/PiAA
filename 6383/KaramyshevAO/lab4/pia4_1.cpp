#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector < size_t > prefix (string s)
{
    vector < size_t > p(s.size(), 0);
    for (size_t i = 1; i < s.size(); i++)
    {
        size_t j = p[i - 1];
        while (j > 0 && s[i] != s[j]) j = p[j - 1];
        if (s[i] == s[j]) j++;
        p[i] = j;
    }
    return p;
}

vector < size_t > kmp (string s, string t)
{
    vector < size_t > prefix_func = prefix(t);
    size_t j = 0;
    size_t k = 0;
    vector < size_t > find;
    for (size_t i = 0; i < s.size(); i++)
    {
        while (j > 0 && t[j] != s[i]) j = prefix_func[j - 1];
        if (t[j] == s[i]) j++;
        if (j == t.size())
        {
            find.push_back(i + 1 - t.size());
        }
    }
    return find;
}

int main()
{
    string s, t;
    cin >> t;
    cin >> s;
    vector < size_t > res = kmp(s,t);
    if (res.size() > 0)
    {
        for (size_t i = 0; i < res.size() - 1; i++)
            cout << res[i] << ",";
        cout << res[res.size() - 1];
    }
    else std::cout << -1;
}
