#include <iostream>
#include <map>
#include <vector>
#include <list>

using namespace std;

class Node {
public:
    Node(int parent, char symb) : parent(parent), symb(symb), flag(false), sfx_link(-1) {}

    map<char, int> next_nodes;
    map<char, int> move;
    bool flag;
    int pattern_index;
    int sfx_link;
    int parent;
    char symb;
};

class Bohr {
public:
    vector<Node*> bohr;
    vector<string> patterns;
    list<pair<int, int>> result;

    Bohr() {
        bohr.push_back(new Node(0, '$'));
    }

    void addToBohr(const string& pattern);

    int getSuffixLink(int node);

    int getMove(int node, char symb);

    void check(int node, int i);

    void find(const string& text);
};

void Bohr::addToBohr(const string& pattern) {
    int num = 0;
    for(char symb : pattern) {
        if(bohr[num]->next_nodes.find(symb) == bohr[num]->next_nodes.end()) {
            bohr.push_back(new Node(num, symb));
            bohr[num]->next_nodes[symb] = bohr.size() - 1;
        }
        num = bohr[num]->next_nodes[symb];
    }
    bohr[num]->flag = true;
    patterns.push_back(pattern);
    bohr[num]->pattern_index = patterns.size() - 1;
}

int Bohr::getSuffixLink(int node) {
    if(bohr[node]->sfx_link == -1) {
        if(node == 0 || bohr[node]->parent == 0) {
            bohr[node]->sfx_link = 0;
        } else {
            bohr[node]->sfx_link = getMove(
                    getSuffixLink(bohr[node]->parent), bohr[node]->symb);
        }
    }
    return bohr[node]->sfx_link;
}

int Bohr::getMove(int node, char symb) {
    if(bohr[node]->move.find(symb) == bohr[node]->move.end()) {
        if(bohr[node]->next_nodes.find(symb) != bohr[node]->next_nodes.end()) {
            bohr[node]->move[symb] = bohr[node]->next_nodes[symb];
        } else if(node == 0) {
            bohr[node]->move[symb] = 0;
        } else {
            bohr[node]->move[symb] = getMove(getSuffixLink(node), symb);
        }
    }
    return bohr[node]->move[symb];
}

void Bohr::check(int node, int i) {
    for(int u = node; u != 0; u = getSuffixLink(u)) {
        if(bohr[u]->flag) {
            result.emplace_front(i + 2 - patterns[bohr[u]->pattern_index].length(), bohr[u]->pattern_index + 1);
        }
    }
}

void Bohr::find(const string& text) {
    int u = 0;
    for(int i = 0; i < text.length(); i++) {
        u = getMove(u, text[i]);
        check(u, i);
    }
}


int main() {
    Bohr* bohr = new Bohr();
    string text;
    string input;
    int num;
    cin >> text;
    cin >> num;
    for(int i = 0; i < num; i++) {
        cin >> input;
        bohr->addToBohr(input);
    }
    bohr->find(text);
    bohr->result.sort([](const pair<int, int>& a, const pair<int, int>& b) {
        if(a.first == b.first) {
            return a.second < b.second;
        }
        return a.first < b.first;
    });

    for(auto elem : bohr->result) {
        cout << elem.first << " " << elem.second << endl;
    }
    return 0;
}