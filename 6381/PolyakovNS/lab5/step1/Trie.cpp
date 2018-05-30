#include "Trie.hpp"

void item::print(){
    if(name) std::cout << name << " (" << this << ")" << ": ";
    else std::cout << "root (" << this << "): ";
    for(int i = 0 ; i < 5 ; ++i){
        //if(next[i] != nullptr) std::cout << next[i]->name << " ";
    }
    //std::cout << std::endl ;
    if(ref){
        if(ref->name) std::cout << "ref: " << ref->name << " ";
        else std::cout << "ref: root ";
        
    }
    std::cout << number.first << " " << number.second << std::endl;
    
    for(int i = 0 ; i < 5 ; ++i){
        if(next[i] != nullptr) next[i]->print();
    }
}

item::item(char ch, int b){
    name = ch;
    number.first = b;
    next.resize(5);
    for(int i = 0 ; i < 5 ; ++i){
        next[i] = nullptr;
    }
    ref = nullptr;
}

item::item(char ch){
    name = ch;
    number.first = 0;
    next.resize(5);
    for(int i = 0 ; i < 5 ; ++i){
        next[i] = nullptr;
    }
    ref = nullptr;
}

item::item(){
    next.resize(5);
    name = 0;
    number.first = 0;
    ref = nullptr;
}

item* item::addItem(char ch){
    
    int k = 0;
    switch (ch){
        case 'A':
            k = 0;
            break;
        case 'C':
            k = 1;
            break;
        case 'G':
            k = 2;
            break;
        case 'T':
            k = 3;
            break;
        case 'N':
            k = 4;
            break;
        default:
            return nullptr;
    }
    if(next[k] == nullptr) next[k] = new item(ch);
    
    return next[k];
}

item* item::has(char ch){
    switch (ch){
        case 'A':
            return next[0];
        case 'C':
            return next[1];
        case 'G':
            return next[2];
        case 'T':
            return next[3];
        case 'N':
            return next[4];
        default:
            return nullptr;
    }
}

void item::addRef(item *prev,std::deque<std::pair<item*,item*> > &st){
    item *cur = prev->ref;
    if(prev == prev->ref) ref = prev;
    else if(cur->has(name) != nullptr) ref = cur->has(name);
    else while(cur != cur->ref){
        if(cur->has(name) != nullptr){
            ref = cur->has(name);
            break;
        }
        else{
            cur = cur->ref;
        }
    }
    if(ref == nullptr){
        if(cur->has(name)) ref = cur->has(name);
        else ref = cur;
    }
    for(int i = 0 ; i < 5 ; ++i){
        if(next[i] != nullptr)
            st.push_back(std::pair<item*,item*>(next[i],this));
    }
}

std::vector<std::pair<int,int> > Trie::AK(const std::string& str){
    item *cur = root;
    for(int i = 0 ; i < str.size() ; ++i){
        while(cur->has(str[i]) == nullptr){
            cur = cur->ref;
            if(cur == cur->ref){
                break;
            }
        }
        if(cur->has(str[i]) != nullptr) cur = cur->has(str[i]);
        if(cur->number.first != 0){
            item *tmp = cur;
            while(tmp != tmp->ref){
                if(tmp->number.first != 0) result.push_back(std::pair<int,int>(i - tmp->number.second + 2,tmp->number.first));
                tmp = tmp->ref;
            }
        }
    }
    return result;
}

void Trie::addReferences(){
    std::deque<std::pair<item*,item*> > st;
    item *cur = root;
    root->ref = root;
    for(int i = 0 ; i < 5 ; ++i){
        if(cur->next[i] != nullptr){
            st.push_back(std::pair<item*,item*>(root->next[i],root));
        }
    }
    while(st.size()){
        std::pair<item*,item*> tmp = st.front();
        tmp.first->addRef(tmp.second,st);
        st.pop_front();
    }
}

void Trie::print(){
    root->print();
}

void Trie::printResult(){
    for(int i = 0 ; i < result.size() ; ++i){
        std::cout << result[i].first << " " << result[i].second;
    }
}

void Trie::addString(int number, const std::string& str){
    item *cur = root;
    int k = 0;
    while(k != str.size() - 1){
        cur = cur->addItem(str[k]);
        ++k;
    }
    cur = cur->addItem(str[k]);
    cur->number.first = number;
    cur->number.second = str.size();
}

Trie::Trie(){
    root = new item();
}

std::vector<std::pair<int,int> > Trie::getResult(){
    return result;
}
