#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <deque>

struct item{
    std::vector<item*> next;
    char name;
    std::pair<int,int> number;
    item *ref;
    item(char,int);
    item(char);
    item();
    item* addItem(char);
    void addRef(item*,std::deque<std::pair<item*,item*> > &);
    item* has(char); //return pointer to next character
    void print();
    
};

class Trie{
public:
    Trie();
    void addString(int number, const std::string&);
    void addReferences();
    std::vector<std::pair<int,int> > AK(const std::string&);
    std::vector<std::pair<int,int> > getResult();
    void print();
    void printResult();
private:
    item *root;
    std::vector<std::pair<int,int> > result;
};
