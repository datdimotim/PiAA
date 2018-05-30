#include <iostream>
#include <list>
#include <algorithm>
#include <iomanip>
#include <cstring>

bool test = false; //  переменная тестирования 
// Глобальные переменные  - зло!

struct Vertex {
    char ch;
    std::tuple <bool, size_t, size_t> label;
    Vertex* parent;
    Vertex* suffLink;
    Vertex* comprSuffLink;
    std::list <Vertex*> children;

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
    // #define isEnd std::get<0>(label)
    // #define patternNumber std::get<1>(label)
    // #define patternSize std::get<2>(label)
    Vertex* head;
public:
    Bor() : head(new Vertex(nullptr, '~')) {} ;
    void addString(std::string const &str){
        static int number = 1;
        auto ptr = head;
        for (auto const &elem : str)
            ptr = addCharacterInVertex(elem, ptr);
        ptr->label = { true, number, str.size() };
        number++;
    }

    void findPositions(std::string const &str){
        
    }

    void processText(std::string const &str){
        Vertex* cur  = head;
        for (size_t i = 0; i < str.size(); i++){
            cur = getLink(cur, str[i]);
            for (Vertex* ptr = cur; ptr != head; ptr = getSuffLink(ptr))
                if (std::get<0>(ptr->label))
                    std::cout << i - std::get<2>(ptr->label) + 1 + 1 << " " << std::get<1>(ptr->label) << std::endl;
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
        // std::cout << std::setw(indent*2) << v->ch << "(" << v << ")";
        v->suffLink = getSuffLink(v);
        // if (v->suffLink == head)
            // std::cout << "-root" << std::endl;
        // else
            // std::cout << "-" << v->suffLink->ch << "(" << v->suffLink << ")" << std::endl;
        for (auto const &el : v->children)
            inDeep(el, indent+1);
    }

    Vertex* getSuffLink(Vertex* v){
        if (test) std::cout << "\nПолучаем суф ссылку для вершины " << v->ch << "\n";
        if (v->suffLink == nullptr){
            if (test) std::cout << "Сслыки нет\n";
            if (v == head || v->parent == head){
                v->suffLink = head;
                if (test) std::cout << "Вершина - голова  или её сын\n";
            }
            else {
                if (test) std::cout << "Вызовём функцию getLink c аргументами: " << v->parent->ch << " и " << v->ch << "\n";
                v->suffLink = getLink(getSuffLink(v->parent), v->ch);
            }
        }
        if (test) std::cout << "Наша ссылка: " << v->suffLink->ch << std::endl;
        return v->suffLink;
    }

    Vertex* getLink(Vertex* v, char ch){
        if (test) std::cout << "GEtlink. Просмотрим сыновей переданной вершины " << v->ch << "(" << v << ")\n";
        for (auto const &elem : v->children){
            if (test) std::cout << "Провряем " << elem->ch << " и " << ch << std::endl;
            if (elem->ch == ch){
                if (test) std::cout << "Совпадение! Возвращаем " << elem->ch << "(" << elem << ")\n";
                return elem;
            }
        }
        if (test) std::cout << "Совападений не найдено!\n";
        if (v == head){
            if (test) std::cout << "Голова, и мы вернём голову!\n";
            return head;
        }
        if (test) std::cout << "вызов getlink из getlink, аргументы: getsufflink(" << v->ch << ") и " << v->ch << "\n";
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

int main(int argc, char** argv) {
	if (argc == 2 && !strcmp(argv[1], "-test\0"))
		test = true;
    Bor bor;
    std::string HayStack;
    std::string pattern;
    int numberOfPatterns;
    std::cin >> HayStack >> numberOfPatterns;
    for (int i = 0; i < numberOfPatterns; i++){
        std::cin >> pattern;
        bor.addString(pattern);
    }
    bor.setSuffixLinks();
    if (test) {
        std::cout << "\nBuilded bor:\n";
        std::cout << bor << std::endl;
        std::cout << std::endl;
    }
    // bor.setCompressedSuffLinks();

    bor.processText(HayStack);
    return 0;
}
