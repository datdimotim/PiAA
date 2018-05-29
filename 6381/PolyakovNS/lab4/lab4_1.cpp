#include <iostream>
#include <vector>
#include <string>

void prefix(std::string text, std::vector<int>& p){
    p[0] = 0;
    for(int i = 1 ; i < text.size() ; ++i){
        int k = p[i - 1];
        while(k > 0 && text[i] != text[k]){
            k = p[k - 1];
        }
        if(text[i] == text[k]) ++k;
        p[i] = k;
    }
}

int main(){
    std::string text;
    std::string pat;
    std::vector<int> result;
    std::cin >> pat;
    std::cin >> text;
    int size_text = text.size();
    int size_pat = pat.size();
    std::vector<int> prefixArray(size_text + size_pat + 1);
    prefix(pat + "#" + text,prefixArray);
    for(int i = 0 ; i < size_text ; ++i){
        if(prefixArray[i + size_pat + 1] == size_pat) result.push_back(i - size_pat + 1);
    }
    if(result.size() == 0){
        std::cout << "-1" << std::endl;
        return 0;
    }
    for(int i = 0 ; i < result.size() - 1 ; ++i){
        std::cout << result[i] << ",";
    }
    std::cout << result[result.size() - 1] << std::endl;
    return 0;
}
