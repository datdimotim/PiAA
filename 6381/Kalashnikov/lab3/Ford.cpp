#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

struct node 
{
    struct node *node_camefrom;
    struct edge *edge_camefrom;
    vector<struct edge *> edge_list;
    int mark_flow;
    char ch, mark;  

    node(char ch)
    : ch(ch)
    , node_camefrom(NULL)
    , edge_camefrom(NULL)
    , mark_flow(0)
    , mark(0)
    {}

    friend std::ostream & operator << (std::ostream & os, const node & a)
    {
        cout << a.ch << "(" << a.mark_flow << ") node: "; 
        if ( a.node_camefrom )
            cout << a.node_camefrom->ch;
        else
            cout << "NULL";
        
        cout << " mark (" << (int)a.mark << ")" << endl;

	    return os;
    }

};

struct edge
{
    struct node *from, *to;
    int max, flow;
    bool sogl;

    edge()
    : from(NULL)
    , to(NULL)
    , max(-1)
    , flow(0)
    , sogl(0)
    {

    }

    edge(node *first, node *second, int max)
    : from(first)
    , to(second)
    , max(max)
    , flow(0)
    , sogl(0)
    {
        //cout << "Created: " << *this <<  endl;
    }

    friend std::ostream & operator << (std::ostream & os, const edge & a)
    {
        cout << a.from->ch << " : " << a.max << "/" << a.flow << " : " << a.to->ch;
	    return os;
    }

    bool operator==(const edge& a) const
    {
        return to->ch == a.to->ch && from->ch == a.from->ch;
    }   
};

class PathFinder
{
    public:
    struct node *start, *finish, *current;
    vector <struct edge *> v_edges;
    vector <struct node *> v_nodes;
    int max_flow_capacity, vertices_number;

    PathFinder()
    : max_flow_capacity(0)
    {
        char first, second;
        int length;
        
        cin >> vertices_number >> first >> second;

        v_nodes.push_back(current = start  = new node(first));
        v_nodes.push_back(finish = new node(second));

        start->node_camefrom = NULL;
        start->mark = 1;

        while(cin >> first >> second >> length)
        {
            bool add_first = true, add_second = true;
            
            for(auto i : v_nodes)
            {
                if(i->ch == first) add_first  = false;
                else if(i->ch == second) add_second = false;
            }

            if(add_first)
            {
                //cout << "Add new!" << endl;
                v_nodes.push_back(new node(first));
            }
            if(add_second)
            {
                //cout << "Add new!" << endl;
                v_nodes.push_back(new node(second));
            }

            v_edges.push_back(new edge(find_node(first), find_node(second), length));
            find_node(first)->edge_list.push_back(v_edges.back());
        }

        find_greatest_flow_capacity();

        std::sort(v_edges.begin(), v_edges.end(), [](struct edge *a, struct edge *b) 
        {
            if(a->from->ch > b->from->ch)                                   return false;
            else if (a->from->ch == b->from->ch && a->to->ch > b->to->ch)   return false;
            else                                                            return true;
        });
    }

    struct node *find_node(char ch)
    {
        for(int i = 0; i < v_nodes.size(); i++)
        {
            if(v_nodes[i]->ch == ch) return v_nodes[i];
        }

        cout << "Not found!" << endl;
        return NULL;
    }

    void print_info()
    {
        cout << "Nodes: " << endl;
        for(auto i : v_nodes)
        {
            cout << *i << endl;
        }

        cout << "Edges: " << endl;
        for(auto i : v_edges)
        {
            cout << *i << endl;
        }
    }

    void find_greatest_flow_capacity()
    {
        for(auto i : v_edges)
        {
            if(i->max > max_flow_capacity) max_flow_capacity = i->max;
        }
    }

    void find_path()
    {
        start->mark_flow = max_flow_capacity;
        start->node_camefrom = NULL;
        start->mark = 1;

        while(true)
        {
            func5();

            if(current == finish)
            {
                func6();
                clear_visited_marks();
            }
            else
                break;

            /* print_info(); */
        }

        /* cout << "Done! " << endl;
        print_info(); */
        print_answer();
    }

    void func6()
    {
        while(current != start)
        {
            /* cout << "Now in " << current->ch << endl;
            cout << "Came from " << *current->edge_camefrom << endl; */

            current->node_camefrom->mark_flow = current->mark_flow;
            
            if(current->edge_camefrom->sogl)
                current->edge_camefrom->flow += current->mark_flow;
            else
                current->edge_camefrom->flow -= current->mark_flow;

            current = current->node_camefrom;
        }
    }

    void func5()
    {
        /* cout << "Now in " << current->ch << endl; */
        if(current == finish) return;

        for( auto i: current->edge_list )
        {
            if( i->to->mark == 0 && i->max - i->flow > 0)
            {
                i->to->mark = 1;
                i->to->node_camefrom = i->from;
                i->to->edge_camefrom = i;

                if( i->max > i->flow )
                {
                    i->sogl = true;
                    i->to->mark_flow = min( i->from->mark_flow, i->max - i->flow );
                }
                else
                {
                    i->sogl = false;
                    i->to->mark_flow = min( i->from->mark_flow, i->flow );
                }
            }
        }

        for( auto i: current->edge_list )
        {
            if( i->to->mark == 1 )
            {
                current = i->to;
                func5();
                if(current == finish) return;

                current = i->from;
            }
        }
    }

    void clear_visited_marks()
    {
        for(auto i : v_nodes)
        {
                i->mark = 0;
        }

        start->mark = 1;
    }

    void print_answer()
    {
        int max_flow = 0;

        for(auto i: v_edges)
        {       
            if(i->from == start) max_flow += i->flow;
        }

        cout << max_flow << endl;

        for(auto i: v_edges)
        {
            cout << i->from->ch << " " << i->to->ch << " " << i->flow << endl;
        }
    }
};

int main() 
{
    PathFinder a;
    a.find_path();

    return 0;
}