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

vector<int> kmp(const string& str, const string& key, const vector<int> &prefix){
    vector<int> pos;
    int matched=0;
    for(int i=0;i<str.size();i++){
        const char c=str[i];
        while(key[matched]!=c&&matched!=0)matched=prefix[matched-1];
        if(key[matched]==c)matched++;
        if(matched==key.size()){
            pos.push_back(i-key.size()+1);
            matched=prefix[matched-1];
        }
    }
    return pos;
}

void printResult(const vector<int>& res){
    if(res.empty()){
        cout<<-1;
        return;
    }
    cout<<res[0];
    for(int i=1;i<res.size();i++)cout<<','<<res[i];
}

int main() {
    string str;
    string key;
    cin>>key;
    cin>>str;
    printResult(kmp(str,key,prefix(key)));
    return 0;
}