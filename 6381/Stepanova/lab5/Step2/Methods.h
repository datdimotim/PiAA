#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "Node.h"
#include "Rib.h"

int ProcessingData(char Joker, std::string& CurrentLine, Node& Start, std::vector<Node*>& MyGraph);

void setSuffixLinks(std::vector<Node*>& MyGraph, Node& Start);

void algorithmAhoCorasick(Node& Start, std::string& Text, int SubstringNumber, std::vector<int>& Answer);