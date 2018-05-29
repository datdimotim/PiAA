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
    std::string text1;
    std::string text2;
    std::cin >> text1;
    std::cin >> text2;
    int size = text1.size();
    if(size != text2.size()){
        std::cout << "-1\n";
        return 0;
    }
    std::vector<int> prefixArray(size * 2 + 1);
    prefix(text1 + "#" + text2, prefixArray);
    int result = prefixArray[size * 2];
    if(result == size){
        std::cout << "0\n";
        return 0;
    }
    if(text2.compare(0,size - result,&text1[result]) == 0){
        std::cout << result << std::endl;
    }
    else{
        std::cout << "-1\n";
    }
    return 0;
}
