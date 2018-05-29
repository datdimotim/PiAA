#include <iostream>
#include <list>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstring>

bool test = false; //  переменная тестирования 
// Глобальные переменные  - зло!

struct vertex_id {
	char ID;
	explicit vertex_id(char id) : ID(id) {} ;
	explicit vertex_id() : ID(0) {} ;

	friend bool operator==(vertex_id lhs, vertex_id rhs){
		if (lhs.ID == rhs.ID) 
			return true;
		else
			return false;
	}

	friend bool operator!=(vertex_id lhs, vertex_id rhs){
		return !(lhs == rhs);
	}

	friend bool operator>(vertex_id const &lhs, vertex_id const &rhs){
		return lhs.ID > rhs.ID;
	}

	friend bool operator<(vertex_id const &lhs, vertex_id const &rhs){
		return lhs.ID < rhs.ID;
	}

	friend std::ostream& operator<<(std::ostream &out, vertex_id id){
		out << id.ID;
		return out;
	}	
};


// Полуребро: вершина на втором конце ребра и его вес
// Элемент в списке смежности (с какой вершиной смежно)
struct SemiEdge { 
	vertex_id Name;
	int length;

	SemiEdge(vertex_id name, int length) : Name(name), length(length) {} ;

	friend std::ostream& operator<<(std::ostream &out, SemiEdge semiEdge){
		out << semiEdge.Name << "(" << semiEdge.length << ")";
		return out;
	}
};

// Элемент списка смежности (какие вершины смежны)
struct VertexOfAdjacencyList { 
	vertex_id Name;
	std::list <SemiEdge> AdjacentVertices;

	VertexOfAdjacencyList(vertex_id name) : Name(name) {} ; 

	friend std::ostream& operator<<(std::ostream &out, VertexOfAdjacencyList vertexList){
		out << vertexList.Name;
		for (auto &ListElem : vertexList.AdjacentVertices)
			out << " - " << ListElem;
		out << " - End!";
		return out;
	}
};

// Список смежности. Реализация хранения графа.
// В векторе находятся структуры типа: (название вершины, список смежных ей вершин с расстояниями до них)
class Graph { 
	std::vector <VertexOfAdjacencyList> AdjList;
public:
	void addVertex(vertex_id name){
		for (auto &cur_vertex : AdjList)
			if (cur_vertex.Name == name)
				return;
		AdjList.emplace_back(name);
	}

	void addEdge(vertex_id start, vertex_id destination, int length){
		addVertex(start);
		addVertex(destination);
		for (auto &vectorElem : AdjList){
			if (vectorElem.Name == start){
				vectorElem.AdjacentVertices.emplace_back(SemiEdge(destination, length));
			}
		}
	}

	// Возвращает копию списка смежности у заданной вершины.
	std::list <SemiEdge> operator[](vertex_id name){
		for (auto vertex : AdjList)
			if (vertex.Name == name)
				return vertex.AdjacentVertices;
	}

	friend std::ostream& operator<<(std::ostream &out, Graph &list){
		out << "\n";
		for (auto &cur_vertex : list.AdjList){
			out << cur_vertex << std::endl;
			out << "|\n";
			// if (list.AdjList.back().Name != cur_vertex.Name) out << "|\n";
		}
		out << "End!\n" << std::endl;
		return out;
	}



/////////////////////////// Секция алгоритмы \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

public:
typedef std::pair<vertex_id, vertex_id> Vertex_Vertex_Pairs;
	void Ford_Falkerson(vertex_id source, vertex_id destination){
		Graph Network;
		Graph FinalNetwork;
		std::list <Vertex_Vertex_Pairs> ImaginaryVertices;
		initResidualNetwork(Network, ImaginaryVertices); // дополняет граф обратными ребрёми с 0 длиной
		// if (test) {
		// 	std::cout << "Мнимые рёбра:\n";
		// 	for (auto const &elem : ImaginaryVertices)
		// 		std::cout << elem.first << "-" << elem.second << " ";
		// 	std::cout << std::endl;
		// }
		while (increaseNetwork(Network, findAugmentingPath(Network, ImaginaryVertices, source, destination)));
		int maxFlow = biuldFinalNetwork(FinalNetwork, Network, ImaginaryVertices, source);
		if (test) std::cout << FinalNetwork << std::endl;
		std::cout << maxFlow << std::endl;
		for (auto const &Vertex : FinalNetwork.AdjList){
			for (auto const &AdjVertex : Vertex.AdjacentVertices)
				std::cout << Vertex.Name << " " << AdjVertex.Name << " " << AdjVertex.length << std::endl;
		}
	}
private:
	std::list <SemiEdge> findAugmentingPath(Graph const &Network, std::list <Vertex_Vertex_Pairs> const &ImVertices, vertex_id source, vertex_id destination){
		std::list <SemiEdge> currentPath;
		std::deque <vertex_id> markedVertices;

		currentPath.push_back({source, 0});
		markedVertices.push_back(source);

		while (!currentPath.empty() && currentPath.back().Name != destination){
			vertex_id currentVertex = currentPath.back().Name;
			if (test) std::cout << "\nНачало цикла поиска след вершины! Текущая вершина: " << currentVertex << std::endl;
			SemiEdge currPair (source, 0);
			for (auto const &curAdjVertex : getAdjacentVertices(Network.AdjList, currentVertex)) {
				if (std::find(markedVertices.begin(), markedVertices.end(), curAdjVertex.Name) == markedVertices.end()){ // если не помечена
					if (std::find(ImVertices.begin(), ImVertices.end(), std::make_pair(currentVertex, curAdjVertex.Name)) == ImVertices.end()){ // если не мнимое ребро
						if (test) std::cout << "Проверяем вершину через прямое ребро из " << currentVertex << " в " << curAdjVertex << std::endl;
						if (test) std::cout << "	Сравниваем длину действительного с текущей (" << currPair.length << "): " << curAdjVertex.length << std::endl;
						if (curAdjVertex.length > abs(currPair.length))
							currPair = curAdjVertex;
					} 
					else { // если прямое ребро оказалось мнимым, тогда тогда проверяем обратное
						// тогда имеем дело с весом мнимного ребра, ибо мы "забираем" пришедший поток
						// проп способность ребра затем нужно будет увеличить, а текущ поток по ребру уменьшить
						for (auto const &reverse : getAdjacentVertices(Network.AdjList, curAdjVertex.Name)) {
							if (reverse.Name == currentVertex){
								if (std::find(ImVertices.begin(), ImVertices.end(), std::make_pair(curAdjVertex.Name, currentVertex)) == ImVertices.end()){
									if (test) std::cout << "Проверяем вершину через обратное ребро из " << curAdjVertex.Name << " в " << reverse.Name << std::endl;
									if (test) std::cout << "	Сравниваем длину мнимого ребра с текущей (" << currPair.length << "): " << curAdjVertex.length << std::endl;
									if (curAdjVertex.length > abs(currPair.length))
										currPair = {curAdjVertex.Name, -curAdjVertex.length};
								}
							}
						}
					}
				}
			}
			markedVertices.push_back(currPair.Name);

			if (currPair.Name == source && currPair.length == 0){
				currentPath.pop_back();
			}
			else
				currentPath.push_back(currPair);
		}

		return currentPath;
	}

	const std::list <SemiEdge>& getAdjacentVertices(std::vector <VertexOfAdjacencyList> const &Verteces, vertex_id to_find){
		for (auto &currVertex : Verteces)
			if (currVertex.Name == to_find)
				return currVertex.AdjacentVertices;
	}

	std::list <SemiEdge>& getAdjacentVertices(std::vector <VertexOfAdjacencyList> &Verteces, vertex_id to_find){
		for (auto &currVertex : Verteces)
			if (currVertex.Name == to_find)
				return currVertex.AdjacentVertices;
	}
	// std::find(Network.AdjList.begin(), Network.AdjList.end(), currentVertex).AdjacentVertices

	bool increaseNetwork(Graph &Network, std::list <SemiEdge> Path){
		if (Path.empty())	
			return false;
		if (test) {
			std::cout << "Chain: ";
			for (auto const &edge: Path)
				std::cout << edge << " ";
			std::cout << std::endl;
		}

		int minWeightInPath = abs(Path.back().length);
		for (auto const &elem : Path)
			if (abs(elem.length) < minWeightInPath && elem.length != 0)
				minWeightInPath = abs(elem.length);
		if (test) std::cout << "Min wieght: " << minWeightInPath << std::endl;

		auto nextEdge = Path.begin();
		auto curEdge = nextEdge++;
		while (nextEdge != Path.end()){
			for (auto &directEdge : getAdjacentVertices(Network.AdjList, curEdge->Name)){
				if (directEdge.Name == nextEdge->Name){
					if (nextEdge->length > 0)
						directEdge.length -= minWeightInPath;
					else
						directEdge.length += minWeightInPath;
				}
			}
			for (auto &reverseEdge : getAdjacentVertices(Network.AdjList, nextEdge->Name)){
				if (reverseEdge.Name == curEdge->Name){
					if (nextEdge->length > 0)
						reverseEdge.length += minWeightInPath;
					else
						reverseEdge.length -= minWeightInPath;
				}
			}
			curEdge = nextEdge++;
		}

		if (test) std::cout << Network;
		return true;
	}

	void initResidualNetwork(Graph &network, std::list <Vertex_Vertex_Pairs> &ImaginaryVertices){
		for (auto const &Vertex : AdjList){
			for (auto const &AdjVertex : Vertex.AdjacentVertices){
				network.addEdge(Vertex.Name, AdjVertex.Name, AdjVertex.length);
				network.addEdge(AdjVertex.Name, Vertex.Name, 0);
				ImaginaryVertices.push_back({AdjVertex.Name, Vertex.Name});
			}
		}
	}
	
	int biuldFinalNetwork(Graph &FinalNetwork, Graph const &Network, std::list <Vertex_Vertex_Pairs> const &ImVertices, vertex_id source){
		for (auto const &Vertex : Network.AdjList){
			for (auto const &AdjVertex : Vertex.AdjacentVertices){
				if (std::find(ImVertices.begin(), ImVertices.end(), std::make_pair(Vertex.Name, AdjVertex.Name)) != ImVertices.end()) // если мнимое ребрj
					FinalNetwork.addEdge(AdjVertex.Name, Vertex.Name, AdjVertex.length);
			}
		}
		// сортируем
		std::sort(FinalNetwork.AdjList.begin(), FinalNetwork.AdjList.end(), cmpVertexOfAdjacencyList);
		for (auto &Vertex : FinalNetwork.AdjList){
			Vertex.AdjacentVertices.sort(cmpSemiEdge);
		}

		int maxFlow = 0;
		for (auto const &Vertex : getAdjacentVertices(FinalNetwork.AdjList, source))
			maxFlow += Vertex.length;
		return maxFlow;
	}

	static bool cmpSemiEdge(SemiEdge const &lhs, SemiEdge const &rhs){
		return lhs.Name < rhs.Name;
	}

	static bool cmpVertexOfAdjacencyList(VertexOfAdjacencyList const &lhs, VertexOfAdjacencyList const &rhs){
		return lhs.Name < rhs.Name;	
	}
};


int main(int argc, char** argv) {
	if (argc == 2 && !strcmp(argv[1], "-test\0"))
		test = true;

	Graph graph;

	char word1;
	char word2;
	int length;
	int numberOfEdges;
	std::cin >> numberOfEdges;
	std::cin >> word1;
	vertex_id start(word1);
	std::cin >> word1;
	vertex_id destination(word1);

	while (std::cin >> word1 >> word2 >> length){
		graph.addEdge(vertex_id(word1), vertex_id(word2), length);
	}

	if (test){
		std::cout << "Adjacency List from input data:\n";
		std::cout << graph << std::endl;
		std::cout << "Source: " << start << std::endl;
		std::cout << "Destination " << destination << "\n\n";
	}

	graph.Ford_Falkerson(start, destination);
}

// мб алгоритмы в отдельные классы?