#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

struct Info {
    Info(char name, float flow, float first_flow): name(name), flow(flow), first_flow(flow){};
	Info(){};
	
	bool operator <(const Info b) const {
        return name < b.name;
    }
	
    char name;
	float flow;
	float first_flow;
};

class Vertex {
public:
    Vertex(char name) : name(name), back_flow(-1), back_name('&'){};
	Vertex(){};

    char get_name() const {
        return name;
    }
	
	bool isVisited() const{
		return visit;
	}
	
	list<Info> list_edge;// список всевозможных путей, в другие вершины + вес
	
	bool visit = 0;
	
	float back_flow;// обратный поток
	char back_name;// вершина из которой пришли
private:
    char name;
};

class Adjacency_list {
public:
    Adjacency_list() {
        for (char i = 'a'; i <= 'z'; i++)	list_vertex.push_back(Vertex(i));
        for (char i = '0'; i <= '9'; i++)	list_vertex.push_back(Vertex(i));
    }
    
    Vertex& at(char a){
		if ((a >= 'a') && (a <= 'z'))		return list_vertex[a - 'a'];
		else if ((a >= '0') && (a <= '9'))	return list_vertex[a - '0' + 26];
    }
	
	void print_list(){
		for (const Vertex& temp : list_vertex){
			if ((temp.back_flow != -1) && (temp.back_name != '&')){
				cout << temp.get_name() << ": ";
				for (const Info& next : at(temp.get_name()).list_edge) {
					cout << next.name << "(" << next.flow << "), ";
				}
				cout << "[ " << temp.back_flow << ", " << temp.back_name << "]" << ", visit: " << temp.isVisited() << endl;
			}			
		}
		
	}
	
	void algorithm_Ford_Falkerson (const Vertex& i_source, const Vertex& i_effluent){
		//print_list();
		while(path_effluent(i_source, i_effluent) != 0){
			residual_capacity(i_source, i_effluent);
			cleaning_labels();
		}
		cout << max_flow << endl;
		//print_list();
		
		optimal_flow();
	}
	
	bool path_effluent(const Vertex& i_source, const Vertex& i_effluent){// находим путь от истока к стоку
		Vertex temp = i_source;
		at(temp.get_name()).visit = 1;
		//cout << "Visit: " << temp.get_name() << "= " << at(temp.get_name()).isVisited() << endl;
		
		Vertex prev;
		at(i_source.get_name()).back_name = '-';
		at(i_source.get_name()).back_flow = 10000;	
		
		//print_list();
		
		//cout << "multiplicity:" << endl;
		while (temp.get_name() != i_effluent.get_name()){
			curr.flow = 0;
			curr.name = '-';
			for (const Info& i : at(temp.get_name()).list_edge){
				if ((i.flow > curr.flow) && (at(i.name).visit == 0)){
					curr.flow = i.flow;
					curr.name = i.name;
				}				
			}
			
			multiplicity.push_back({curr.name, curr.flow, 0});
			
			//print_list();
			/*cout << "multiplicity: " << endl;
			for (const Info& curr : multiplicity){
				cout << curr.name << " " << curr.flow << endl;
			}*/
			
			prev = temp;
			if (curr.flow == 0){
				//cout << "tut" << endl;
				multiplicity.clear();
				at(temp.get_name()).visit = 1;
				temp = i_source;
				at(temp.get_name()).back_name = '-';
				at(temp.get_name()).back_flow = 0;
				int z = 0;
				for (const Info& next : at(i_source.get_name()).list_edge) {
					if ((at(next.name).visit == 0) && (next.flow != 0))	z++;	
				}
				//cout << "zzzz" << z << endl;
				if (z == 0)	return 0;				
			}
			else {
				temp = at(curr.name);
				at(temp.get_name()).visit = 1;
				//cout << "Visit: " << temp.get_name() << "= " << at(temp.get_name()).isVisited() << endl;
				at(temp.get_name()).back_name = prev.get_name();
				at(temp.get_name()).back_flow = curr.flow;
			}
		}
		return 1;
	}
	
	void residual_capacity(const Vertex& i_source, const Vertex& i_effluent){// остаточная пропускная способность
		curr.flow = 10000;
		curr.name = '-';
		for (const Info& i : multiplicity){
			if (i.flow < curr.flow){
				curr.flow = i.flow;
				curr.name = i.name;
			}				
		}
		max_flow += curr.flow;
		/*cout << "min: " << curr.flow << endl;
		cout << "multiplicity: " << endl;
		for (const Info& curr : multiplicity){
			cout << curr.name << " " << curr.flow << endl;
		}
		cout << "vi4444444444444444" << endl << endl;*/
		Vertex temp = i_source;
		while (temp.get_name() != i_effluent.get_name()){
			//if (temp.isVisited() == 1){
				//cout << temp.get_name() << ": " << endl;
				//cout << "temp.back_name: " << temp.back_name << endl;
				vector<Info>::iterator it;
				it = multiplicity.begin();
				for (Info& next : at(temp.get_name()).list_edge) {
					//cout << "next.name: " << next.name << endl;
					int k = -1;
					//cout << "first:" << it->name << endl;
					if (next.name == it->name){
						/*cout << it->name << " delete" << endl;
						cout << "multiplicity: " << endl;
						for (const Info& curr : multiplicity){
							cout << curr.name << " " << curr.flow << endl;
						}	*/
						next.flow -= curr.flow;
						//cout << "EEEEEEEEEEEE BOY" << endl;
						for (Info& dk : at(next.name).list_edge){
							if (dk.name == temp.get_name())		dk.flow += curr.flow;
						}
						//print_list();
						k++;
					}
					//cout << "ia vishel" << endl;
					if (k == 0)	break;
					//cout << next.name << "(" << next.flow << "), ";
				}
				//cout << "[ " << temp.back_flow << ", " << temp.back_name << "]";
				//cout << endl;
				temp = at(it->name);
				multiplicity.erase(multiplicity.begin());
			
		}
		//cout << "END::::" << endl << endl;
		//print_list();
	}	
	
	void cleaning_labels(){
		for (Vertex& temp : list_vertex){
			if ((temp.back_flow != -1) && (temp.back_name != '&')){
				temp.back_flow = 0;
				temp.back_name = '-';
				temp.visit = 0;
			}			
		}	
	}
	
	void optimal_flow(){
		for (const Vertex& temp : list_vertex){
			if ((temp.back_flow != -1) && (temp.back_name != '&')){
				at(temp.get_name()).list_edge.sort();
				for (Info& next : at(temp.get_name()).list_edge) {
					
					next.flow = next.first_flow - next.flow;
					if (next.flow < 0) next.flow = 0;
					cout << temp.get_name() << " " << next.name  << " " << next.flow << endl;
				}
			}			
		}
		
	}
	
	float max_flow = 0;// максимальный поток сети
	Info curr;
	vector<Info> multiplicity;// мн-во вершин в которые можно перейти из текущей
	vector<Vertex> list_vertex;
};

int main(){
	int N;// количество ориентированных рёбер графа
	char source;// исток
	char effluent;// сток
	char vertex1, vertex2;
	float flow;// поток
	
	Adjacency_list adjacency_list;
	
	cin >> N;
	cin >> source; 
	cin >> effluent;
	Vertex i_source (source);
	Vertex i_effluent (effluent);
	
	while (cin >> vertex1 >> vertex2 >> flow){
		adjacency_list.at(vertex1).list_edge.push_back({vertex2, flow, flow});
		adjacency_list.at(vertex1).back_flow = 0;
		adjacency_list.at(vertex1).back_name = '-';
		adjacency_list.at(vertex2).back_flow = 0;
		adjacency_list.at(vertex2).back_name = '-';
	}
	
	
	adjacency_list.algorithm_Ford_Falkerson(i_source, i_effluent);
	
	return 0;
}

