#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <set>

using namespace std;

struct Node{
    map<char,Node*> v;
    Node* failNode= nullptr;
    Node* nearPattern= nullptr;
    vector<int> patternMatched;
    static void deleteBor(Node* root){
        for(auto ch:root->v)deleteBor(ch.second);
        delete root;
    }
};

void addToBor(Node* bor,string& key, int indexOfPattern){
    for(char c:key){
        if(bor->v.find(c)!=bor->v.end()){
            bor=bor->v.find(c)->second;
        }
        else{
            Node* newNode=new Node();
            bor->v.insert(pair<char,Node*>(c,newNode));
            bor=newNode;
        }
    }
    bor->patternMatched.push_back(indexOfPattern);
}

void createFails(Node* root){
    root->failNode=root;
    list<Node*> queue;
    for(auto p:root->v){
        p.second->failNode=root;
        queue.push_back(p.second);
    }
    while(!queue.empty()){
        Node* parent=*queue.begin();
        queue.pop_front();
        for(auto n:parent->v){
            char letter=n.first;
            Node* child=n.second;
            queue.push_back(child);
            ////////////////////////
            Node* failNode=parent->failNode;
            while (failNode->v.find(letter)==failNode->v.end() && failNode!= root){
                failNode=failNode->failNode;
            }
            if(failNode->v.find(letter)!=failNode->v.end())failNode=failNode->v.find(letter)->second;
            child->failNode=failNode;
        }
    }
}

void createSubPatterns(Node* root) {
    list<Node *> queue={root};
    while (!queue.empty()) {
        Node *current = *queue.begin();
        queue.pop_front();
        for(auto child:current->v)queue.push_back(child.second);
        if(!current->failNode->patternMatched.empty())current->nearPattern=current->failNode;
        else current->nearPattern=current->failNode->nearPattern;
    }
}

vector<int> findPatterns(string str, Node* root){
    vector<int> res(str.size());
    Node* current=root;
    for(int i=0;i<str.size();i++){
        char c=str[i];
        while(current->v.find(c)==current->v.end()&&current!=root){
            current=current->failNode;
        }
        if(current->v.find(c)!=current->v.end())current=current->v.find(c)->second;
        Node *t=current;
        while(t->nearPattern!= nullptr){
            t=t->nearPattern;
            for(int pm:t->patternMatched)if(i+1-pm>=0)res[i+1-pm]++;
        }
        for(int pm:current->patternMatched)if(i+1-pm>=0)res[i+1-pm]++;
    }
    return res;
};

Node* initBor(string str, char joker, int &count) {
    Node* bor=new Node();
    count=0;
    int from=0;
    str+=joker;
    for(int i=0;i<str.size();i++){
        if(str[i]!=joker)continue;
        if(i-from==0){
            from=i+1;
            continue;
        }

        string s=str.substr(from, i-from);
        from=i+1;

        addToBor(bor,s,i);
        count++;
    }
    return bor;
}

vector<int> findWithJoker(string& txt, string& key, char joker){
    int count;
    Node* bor= initBor(key, joker, count);
    createFails(bor);
    createSubPatterns(bor);
    vector<int> found=findPatterns(txt,bor);
    Node::deleteBor(bor);
    vector<int> res;
    for(int i=0;i<found.size();i++)if(found[i]==count)res.push_back(i);
    return res;
}

int main() {
    string txt;
    string pattern;
    char joker;
    cin>>txt;
    cin>>pattern;
    cin>>joker;

    vector<int> res=findWithJoker(txt,pattern,joker);

    for (int p:res)cout<<p+1<<endl;
    return 0;
}