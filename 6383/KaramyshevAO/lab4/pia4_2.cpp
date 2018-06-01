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
int Cycle (const string & s, const string & t)
{
    if (s.size() != t.size()) return -1;
    string new_s = s + s;
    vector < size_t > pref = prefix(t);
    size_t j = 0;
    size_t k = 0;
    size_t find = -1;
    for (size_t i = 0; i < new_s.size(); i++)
    {
        while (j > 0 && t[j] != new_s[i]) j = pref[j - 1];
        if (t[j] == new_s[i]) j++;
        if (j == t.size())
        {
            find = (i + 1 - t.length());
            break;
        }
    }
    return find;
}

int main()
{
    string s, t;
    cin >> t;
    cin >> s;
    cout << Cycle(t,s);
}
