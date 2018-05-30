#include <iostream>
#include <list>
#include <algorithm>
#include <iomanip>
#include <vector>

struct Vertex {
    char ch;
    std::tuple < bool, size_t, size_t > label; // конец?, номер строки, её длина
    Vertex* parent;
    Vertex* suffLink;
    Vertex* comprSuffLink;
    std::list <Vertex*> children;
    std::vector <int> positionsInOriginalText;

    Vertex(Vertex* p, char ch) : ch(ch), label({false, 0, 0}), parent(p), suffLink(nullptr), comprSuffLink(nullptr) {};

    void print(std::ostream &out, size_t indent = 0){
        out << std::setw(indent) << ch;
        if (std::get<0>(label)) out << "+";
        out << std::endl;
        // for_each(begin(children), end(children), print(out, ++indent));
        for (auto const &el : children)
            el->print(out, indent+1);
    }
};

class Bor {
    Vertex* head;
public:
    Bor() : head(new Vertex(nullptr, '~')) {} ;
    void addString(std::string const &str, int positionInOriginalText){
        static int number = 1;
        auto ptr = head;
        for (auto const &elem : str)
            ptr = addCharacterInVertex(elem, ptr);
        // if (std::get<0>(ptr->label))
        //     std::cout << "Uje est! Сейчас запушим: " << positionInOriginalText << std::endl;
        ptr->label = { true, number, str.size() };
        ptr->positionsInOriginalText.push_back(positionInOriginalText);
        // std::cout << "Теперь: \n";
        number++;
    }

    void findPositions(std::string const &str){
        
    }

    void processText(std::string const &str, int numberOfSubStrings){
        Vertex* cur  = head;
        std::vector <int> helpArray(str.size());

        for (size_t i = 0; i < str.size(); i++){
            cur = getLink(cur, str[i]);
            for (Vertex* ptr = cur; ptr != head; ptr = getSuffLink(ptr))
                if (std::get<0>(ptr->label)){
                    int position = i - std::get<2>(ptr->label) + 1 + 1;
                    int index = std::get<1>(ptr->label);

                    for (auto const startPos : ptr->positionsInOriginalText){
                        // std::cout << "Позиция в haystack: " << position << " Позиция " << startPos << " " << index << std::endl;
                        int arr_index = position;
                        arr_index -= startPos;
                        arr_index += 1;
                        if (arr_index >= 0) helpArray[arr_index]++;
                    }
                }
        }
        for (long int i = 0; i < helpArray.size(); i++){
            // std::cout << helpArray[i] << " ";
            if (helpArray[i] == numberOfSubStrings)
                std::cout << i << std::endl;
        }
    }

    void setSuffixLinks(){
        inDeep(head);
    }

    void setCompressedSuffLinks(){
        inDeepCompressed(head);
    }

private:
    void inDeepCompressed(Vertex* v, size_t indent = 0){
        std::cout << std::setw(indent*2) << v->ch << "(" << v << ")";
        getComprSuffLink(v);
        if (v->comprSuffLink == head)
            std::cout << "-root" << std::endl;
        else
            std::cout << "-" << v->comprSuffLink->ch << "(" << v->comprSuffLink << ")" << std::endl;
        for (auto const &el : v->children)
            inDeepCompressed(el, indent+1);
    }

    Vertex* getComprSuffLink(Vertex* v){
        if (v->comprSuffLink == nullptr){
            auto link = getSuffLink(v);
            if (std::get<0>(link->label))
                v->comprSuffLink = link;
            else if (link == head)
                    v->comprSuffLink = head;
            else 
                v->comprSuffLink = getComprSuffLink(getSuffLink(v));
        }
            return v->comprSuffLink;
    }

    void inDeep(Vertex* v, size_t indent = 0){
        v->suffLink = getSuffLink(v);
        for (auto const &el : v->children)
            inDeep(el, indent+1);
    }

    Vertex* getSuffLink(Vertex* v){
        if (v->suffLink == nullptr){
            if (v == head || v->parent == head)
                v->suffLink = head;
            else 
                v->suffLink = getLink(getSuffLink(v->parent), v->ch);
        }
        return v->suffLink;
    }

    Vertex* getLink(Vertex* v, char ch){
        for (auto const &elem : v->children)
            if (elem->ch == ch)
                return elem;
        if (v == head)
            return head;
        return getLink(getSuffLink(v), ch);
    }

    Vertex* addCharacterInVertex(char newCh, Vertex* vertex){
        // auto res = std::find(vertex->children.begin(), vertex->children.end(), [&](Vertex* elem){ return elem->ch == newCh; });
        for (auto &el: vertex->children)
            if (el->ch == newCh)
                return el;
        Vertex* newElem = new Vertex(vertex, newCh);
        vertex->children.push_back(newElem);
        return newElem;
    }   

    friend std::ostream& operator<<(std::ostream &out, Bor const &ptr){
            ptr.head->print(out);
            return out;
    }
};

std::vector <std::pair<std::string, size_t>>  parse(std::string str, char symbolMask){
        std::vector <std::pair<std::string, size_t>> ret;
        int curPos = 1;
        for (int pos = str.find(symbolMask); pos != std::string::npos ; pos = str.find(symbolMask)){
            std::string founded = str.substr(0, pos);
            if (founded.size() == 0){
                str = str.substr(pos+1);
                curPos++;
                continue;    
            }
            pos++;
            str = str.substr(pos);
            ret.push_back({founded, curPos});
            // std::cout << ret.back().first << " " << ret.back().second << std::endl;
            curPos += pos;
        }
        if (str.size() != 0){
            ret.push_back({str, curPos});
            // std::cout << ret.back().first << " " << ret.back().second << std::endl;
        }
        return ret;
    }

int main() {
    Bor bor;
    std::string HayStack;
    std::string pattern;
    char symbolMask;
    std::cin >> HayStack >> pattern >> symbolMask;

    auto withoutMask = parse(pattern, symbolMask);

    for (auto const &el : withoutMask)
        bor.addString(el.first, el.second);
    bor.setSuffixLinks();

    
    bor.processText(HayStack, withoutMask.size());

    size_t pos;

    
    return 0;
}
