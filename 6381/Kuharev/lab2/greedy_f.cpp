    #include <iostream>
    #include <vector>
    #include <string>
    #include <algorithm>
     
    struct connection
    {
        connection(char n, float w) : name(n), weight(w) {}
        char name;
        float weight;
    };
     
    struct node 
    {
        node(char n, connection dest_b = connection('.', 0)) : name(n)
        {
            if( dest_b.name != '.' )
                ways = {dest_b};
        }
        char name;
        std::vector<connection> ways; 
    };
     
    int find( char name, std::vector<node> nodes ) 
    {
        for(node& n : nodes)
            if( n.name == name )
                return &n - &nodes[0];
        return -1;
    }
     
    bool greed( std::vector<node>& nodes, node curr, std::string& been, char end )
    {
        if( curr.ways.empty() ) return false;
        for( size_t i = 0; i < curr.ways.size(); ++i )
        {
            if( curr.ways[i].name == end )
            {
                been.push_back(end);
                been.push_back(curr.name);
                return true;
            }
            if( greed(nodes, nodes[find(curr.ways[i].name,nodes)], been, end) )
            {
                been.push_back(curr.name);
                return true;
            }
        }
        return false;
    }
     
    int main(void)
    {
        char begin, end;
        std::cin >> begin >> end;
     
        char dest_b, source_b;
        float weight;
     
        std::vector<node> nodes;
        int index = 0;
     
        while( std::cin >> source_b >> dest_b >> weight )
        {
            index = find(source_b, nodes);
     
            if( index != -1 )
                nodes[index].ways.push_back(connection(dest_b, weight));
            else
                nodes.push_back(node(source_b, connection(dest_b,weight)));
            if( find(dest_b, nodes) == -1 )
                nodes.push_back(node(dest_b));
        }
     
        for( auto& n : nodes )
            std::sort(n.ways.begin(), n.ways.end(),[](connection& f, connection& s)
            {
                return f.weight < s.weight;
            });
     
        std::string been;
        greed(nodes, nodes[find(begin, nodes)], been, end);
     
        std::reverse(been.begin(), been.end());
        std::cout << been;
     
        return 0;
    }