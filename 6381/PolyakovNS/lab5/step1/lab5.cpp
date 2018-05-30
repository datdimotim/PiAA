#include <iostream>
#include <vector>
#include "Trie.hpp"

int main(){
    std::string text;
    std::cin >> text;
    int n = 0;
    std::cin >> n;
    Trie my_trie;
    std::string tmp;
    for(int i = 0 ; i < n ; ++i){
        std::cin >> tmp;
        my_trie.addString(i + 1,tmp);
    }
    my_trie.addReferences();
    //my_trie.print();
    auto result = my_trie.AK(text);
    //std::cout << result.size() << std::endl;
    for(int i = 0 ; i < result.size() ; ++i){
        std::cout << result[i].first << " " << result[i].second << std::endl;
    }
    return 0;
}
