#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include "Node.h"
#include "Rib.h"

void ProcessingData(int Number, std::string& CurrentLine, Node& Start, std::vector<Node*>& MyGraph);

void setSuffixLinks(std::vector<Node*>& MyGraph, Node& Start);

void algorithmAhoCorasick(Node& Start, std::string& Text,std::vector<std::pair<int, int>*>& Answer);