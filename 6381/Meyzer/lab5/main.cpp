#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stdexcept>
// #define DEBUG
// #define OUT_INP

using namespace std;

namespace DM
{
	const vector<char> alphabet = {'A', 'C', 'G', 'T', 'N'};
	char to_char(unsigned index)
	{
		if ((index < 0) || (index >= alphabet.size()))
			throw out_of_range("There is no such symbol in alphabet with index " + to_string(index));
		return alphabet[index];
	}
	unsigned to_uns(char a)
	{
		for (unsigned i = 0; i < alphabet.size(); ++i)
		{
			if (alphabet[i]==a)
				return i;
		}
		throw out_of_range(string("There is no symbol ") + a + " in alphabet");
	}

	struct uuStruct
	{
		unsigned a;
		unsigned b;
	};


	class Trie
	{
	public:
		struct Node
		{
			vector<int> next; // Keeps edges to each symbol
				// -1 if there is no edge to symbol with such index
			unsigned parent = 0; // Parent addr
			char parentChar = 0; // Symbol in edge between parent and current node
			std::list<unsigned> pattNum;
			int ref = 0; // = 0 by default
			Node()
			{
				next = vector<int>(alphabet.size(), -1);
			}
		};

		Trie(const vector<string>& patterns)
		{
			buildTrie(patterns);
		}

		void searchSubStrings(const string& text, list<uuStruct>& result)
		{
			#ifdef DEBUG
				cout << "Searching sub strings:" << endl
					<< "  Processing nodes:" << endl << "  ";
			#endif
			unsigned current = 0;
			// For each character
			for (unsigned i = 0, size = text.size(); i < size; ++i)
			{
				char c = text[i];
				// While there is no edge with such char we are going to other node by ref until its root
				while ((nodes[current].next[to_uns(c)] == -1) && current != 0)
				{
					current = nodes[current].ref;
				}
				if (nodes[current].next[to_uns(c)] != -1)
				{
					current = nodes[current].next[to_uns(c)];
				}
				else
					continue;

				// For current node and all its references
				// If it's one of the patterns then add it to result
				unsigned tmp = current;
				while (tmp != 0)
				{
					// cout << tmp;
					if (!nodes[tmp].pattNum.empty())
						for (auto j : nodes[tmp].pattNum)
							result.push_back({i+2-pattSizes[j-1],
								static_cast<unsigned>(j)});
					tmp = nodes[tmp].ref;
				}
				#ifdef DEBUG
					cout << current << " ";
				#endif
			}
			#ifdef DEBUG
				cout << endl;
			#endif
		}

		// Prints all the patterns that trie keeps
		void print() const
		{
			_print(nodes[0], "");
		}
	private:
		vector<Node> nodes;
		vector<int> pattSizes;
		void buildTrie(const vector<string>& patterns)
		{
			nodes.push_back(Node{});
			for (unsigned i = 0, size = patterns.size(); i < size; ++i)
			{
				#ifdef DEBUG
					cout << "Adding to trie pattern " << patterns[i] << endl;
				#endif
				addPattern(patterns[i], i+1);
			}
			calcReferences();
		}
		void addPattern(const string &pattern, unsigned pattN)
		{
			// Node &tmp = nodes[0];
			unsigned current = 0;
			for (char i : pattern)
			{
				// If we already have edge with this symbol
					// Then we just move to it
				if (nodes[current].next[to_uns(i)] != -1)
				{
					#ifdef DEBUG
						cout << "   Edge with " << i
							<< " character is already exists. Moving to it." << endl;
					#endif
					current = nodes[current].next[to_uns(i)];
				}
				// Else we are adding new edge, creating vertex and reference
				else
				{
					// Creating empty node
					nodes.push_back(Node{});
					// Setting parent node in new node
					nodes.back().parent = current;
					nodes.back().parentChar = i;
					// Setting edge to the new node from the current
					nodes[current].next[to_uns(i)] = nodes.size() - 1;

					#ifdef DEBUG
						cout << "   There is no edge with " << i
							<< " character. Creating it and new node." << endl
							<< "      Number of the new node is      "
							<< nodes.size() - 1 << endl
							<< "      It's parent is                 "
							<< nodes.back().parent << endl;
					#endif
					// Moving to the created node
					current = nodes.size() - 1;
				}
			}
			// if (nodes[current].pattNum == -1)
			// {
			#ifdef DEBUG
				cout << "   Added pattern " << pattern << " with number "
					<< pattN << endl;
			#endif
			nodes[current].pattNum.push_back(pattN);
			pattSizes.push_back(pattern.size());
			// }
			// else
			// {
			// 	#ifdef DEBUG
			// 		cout << "   Trie already has this pattern." << endl;
			// 	#endif
			// }
		}
		void calcReferences()
		{
			#ifdef DEBUG
				cout << endl << "Calculating references:" << endl;
			#endif
			list<unsigned> queue;
			queue.push_back(0);
			while(!queue.empty())
			{
				unsigned current = queue.front();
				queue.pop_front();
				for(int i : nodes[current].next)
				{
					if (i != -1)
						queue.push_back(i);
				}
				if (nodes[current].parent == 0)
					continue;
				// Setting reference in the new node:
				// Moves on a references until reaching root or having edge with needed symbol
				unsigned parRef = nodes[nodes[current].parent].ref;
				char parChar = nodes[current].parentChar;
				while (nodes[parRef].next[to_uns(parChar)] == -1
					&& parRef != 0)
				{
						parRef = nodes[parRef].ref;
				}
				// If edge is found, sets a reference to the node with this edge
				if (nodes[parRef].next[to_uns(parChar)] != -1)
					nodes[current].ref = nodes[parRef].next[to_uns(parChar)];
				#ifdef DEBUG
					cout << "   Reference in node " << current << " is set to "
						<< nodes[current].ref << endl;
					cout << "   It's parent char: " << parChar << endl;
					cout << "   It's parent ref: " << parRef << endl;
				#endif
			}
		}
		void _print(const Node &arg, string str) const
		{
			for (unsigned i = 0, size = alphabet.size(); i < size; ++i)
				if (arg.next[i] != -1)
					_print(nodes[arg.next[i]], str+to_char(i));
			if (!arg.pattNum.empty())
			{
				cout << str << " ";
				for (auto i : arg.pattNum)
					cout << i << " ";
				cout << endl;
			}
		}
	};
};

void readData(string &text, unsigned& pattN, vector<string> &patterns)
{
	cin >> text >> pattN;
	string Pattern;
	for (unsigned i = 0; i < pattN; ++i)
	{
		cin >> Pattern;
		patterns.push_back(Pattern);
	}
	#ifdef OUT_INP
		cout << text << '\n' << pattN << endl;
		for (auto &i : patterns)
			cout << i << endl;
	#endif
}

void splitInPatterns(const string &text, const char sep,
	vector<string> &patterns, vector<unsigned> &pattBeg, unsigned &pattN)
{
	auto lhs = text.begin();
	auto rhs = text.begin();
	while (rhs != text.end())
	{
		while ((*lhs) == sep)
		{
			++lhs;
		}
		if (lhs == text.end())
			break;
		rhs = lhs;
		while ((*rhs) != sep && rhs != text.end())
		{
			++rhs;
		}
		patterns.push_back({lhs, rhs});
		pattBeg.push_back(lhs-text.begin()+1);
		++pattN;
		if (rhs == text.end())
			break;
		++rhs;
		lhs = rhs;
	}
}

int main()
{
	string text;
	list<DM::uuStruct> result;
	unsigned pattN = 0;
	char joker;
	vector<string> patterns;
	// Step1
		// readData(text, pattN, patterns);
	// Step2
	 	string pattern;
		vector<unsigned> pattBeg;
		cin >> text;
		cin >> pattern;
		cin >> joker;
		#ifdef OUT_INP
			cout << text << '\n' << pattern << '\n' << joker << endl;
		#endif
		splitInPatterns(pattern, joker, patterns, pattBeg, pattN);
		#ifdef DEBUG
		cout << "Splitted in patterns: " << endl;
		for (unsigned i = 0, size = patterns.size(); i < size; ++i)
			cout << patterns[i] << " " << pattBeg[i] << endl;
		#endif


	DM::Trie trie{patterns};
	trie.searchSubStrings(text, result);
	result.sort([](const DM::uuStruct &lhs, const DM::uuStruct &rhs)
		{
			return lhs.b<rhs.b;
		});
	result.sort([](const DM::uuStruct &lhs, const DM::uuStruct &rhs)
		{
			return lhs.a<rhs.a;
		});

	// Answer output:
	// Step1 First is position, second is pattern number both starting from 1
		// for (auto &i : result)
		// 	cout << i.a << " " << i.b << endl;
	// Step2
		// tmp[i] keeps number of subpatterns that match
		// the pattern with beginning in i of text
		vector<unsigned> tmp(text.size(), 0);
		#ifdef DEBUG
			cout << "Printing answer:" << endl
				<< "   Text size - " << text.size() << endl;
			#endif
		for (auto &i : result)
		{
			// Beginning of current subpattern in pattern starting from 0
			unsigned subPattBeg = pattBeg[i.b-1]-1;
			// if it's bigger than beginning of a pattern
			// then it exceeds start of the text
			if (subPattBeg > (i.a-1))
				continue;
			// Beginning of a pattern in text starting from 0
			unsigned pattBeg = i.a-1-subPattBeg;
			// if pattern exceeds end of the text
			if (pattBeg+pattern.size()>text.size())
				continue;
			++tmp[pattBeg];
			// If in this point number of subpatterns is max
			// then it's beginning of a pattern
			#ifdef DEBUG
				cout << "   Subpattern pos    - " << i.a << endl
					  << "         , number    - " << i.b << endl;
				cout << "   Pattern beginning - " << pattBeg << endl
					  << "              , size - " << pattern.size() << endl;
			#endif
			if ((tmp[pattBeg] == pattN))
				cout << pattBeg+1 << endl;
		}

	return 0;
}
