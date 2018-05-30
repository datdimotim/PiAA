#include <iostream>
#include <vector>
#include <algorithm>
#include "Trie.hpp"

const std::vector<char> alf = {'A','C','G','T','N'};

void addString(Trie &tr, std::string pat, char joker){
    bool has_jockers = false;
    for(int i = 0 ; i < pat.size() ; ++i){
        if(pat[i] == joker){
            has_jockers = true;
            for(int j = 0 ; j < alf.size() ; ++j){
                pat[i] = alf[j];
                addString(tr,pat,joker);
                pat[i] = joker;
            }
        }
        
    }
    if(!has_jockers) tr.addString(1,pat);
}



int main(){
    std::string text;
    std::string pat;
    char joker;
    std::cin >> text >> pat >> joker;
    Trie my_trie;
    std::vector<int> c(text.size());
    int prev_joker = -1;
    int n = 0;
    for(int i = 0 ; i < pat.size() ; ++i){
        if(pat[i] == joker){
            std::string tmp = pat;
            tmp.resize(i);
                tmp.erase(0, prev_joker + 1);
            if(tmp.size()){
                my_trie.addString(i - tmp.size(),tmp);
                ++n;
            }
            prev_joker = i;
        }
        if(i == pat.size() - 1){
            std::string tmp = pat;
            tmp.erase(0,prev_joker + 1);
            if(tmp.size()){
                my_trie.addString(i - tmp.size() + 1,tmp);
                ++n;
            }
        }
    }
   
    my_trie.addReferences();
    //my_trie.print();
    //std::cout << n << std::endl;
    auto result = my_trie.AK(text);
    
    for(int i = 0 ; i < result.size() ; ++i){
        int tmp = result[i].first - result[i].second + 1;
        if(tmp >= 0) ++c[tmp];
        //++c[result[i].first - result[i].second + 1];
        //std::cout << c[result[i].first - result[i].second + 1] << " " ;
    }
    for(int i = 0 ; i < c.size() ; ++i){
        if(c[i] == n) std::cout << i << std::endl;
        //if(c[i] >= 0) std::cout << c[i] << " " << i << std::endl;
    }
    //std::sort(result.begin(),result.end());
    
    
    
    //std::cout << result.size() << std::endl;
    for(int i = 0 ; i < result.size() ; ++i){
        //std::cout << "res: " << result[i].first << " " << result[i].second << std::endl;
    }
    return 0;
}
