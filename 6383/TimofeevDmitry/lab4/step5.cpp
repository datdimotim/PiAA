#include <iostream>
#include <vector>
using namespace std;

vector<int> prefix(const string& str){
    vector<int> prefs(str.size());
    for(int i=1;i<prefs.size();i++){
        int j=prefs[i-1];
        while (str[i]!=str[j] && j!=0)j=prefs[j-1];
        if(str[i]==str[j])j++;
        prefs[i]=j;
    }
    return prefs;
}

int cyclicAnalisis(string &a, string &b){
    vector<int> prefB=prefix(b);
    string str=a+a;
    int m=0;
    for(int i=0;i<str.size();i++){
        while (b[m]!=str[i]&&m!=0)m=prefB[m-1];
        if(b[m]==str[i])m++;
        if(m==b.size())return i-m+1;
    }
    return -1;
}

int main() {
    string str;
    string key;
    cin>>key;
    cin>>str;
    cout<< cyclicAnalisis(key, str);
    return 0;
}