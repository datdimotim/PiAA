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
    int patternMatched=-1;
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
    bor->patternMatched=indexOfPattern;
}

Node* createBor(vector<string>& strs){
    Node* root=new Node();
    for(int i=0;i<strs.size();i++)addToBor(root, strs[i],i);
    return root;
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
        if(current->failNode->patternMatched!=-1)current->nearPattern=current->failNode;
        else current->nearPattern=current->failNode->nearPattern;
    }
}

vector<pair<int,int>> findPatterns(string str, Node* root, vector<string>& strs){
    vector<pair<int,int>> res;
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
            res.push_back(pair<int,int>(i-strs[t->patternMatched].size()+1,t->patternMatched));
        }
        if(current->patternMatched!=-1){
            res.push_back(pair<int,int>(i-strs[current->patternMatched].size()+1,current->patternMatched));
        }
    }
    return res;
};

vector<pair<int,int>> ahoCorasick(string& txt, vector<string>& keys){
    Node* bor=createBor(keys);
    createFails(bor);
    createSubPatterns(bor);
    vector<pair<int,int>> res=findPatterns(txt,bor,keys);
    Node::deleteBor(bor);
    return res;
};

int main() {
    string txt;
    vector<string> keys;
    cin>>txt;
    int k;
    cin>>k;
    for(int i=0;i<k;i++){
        string s;
        cin>>s;
        keys.push_back(s);
    }
    vector<pair<int,int>> res=ahoCorasick(txt,keys);
    struct Comparator{
        bool operator()(pair<int,int> const & l,pair<int,int> const & r)const {
            if(l.first!=r.first)return l.first<r.first;
            return l.second<r.second;
        }
    };
    set<pair<int,int>,Comparator> sorted;
    for(auto p:res)sorted.insert(p);
    for(auto p:sorted)cout<<p.first+1<<" "<<p.second+1<<"\n";
    return 0;
}