#include <iostream>
#include <vector>

struct node;

struct way
{
    way(node* n, float w) : dest(n), weight(w){}
    node* dest;
    float weight;
};

struct node
{
    node( char n )
        : name(n){}

    char name;
    node* next = nullptr;
    std::vector<way> childs;
};

struct path
{
    path() {}
    std::vector<way*> seq;
    float weight;
};

node* find(char name, node* nod)
{
    while( nod )
    {
        if( nod->name == name )
        {
            return nod;
        }
        nod = nod->next;
    }
    return nullptr;
}

node* it(node* root)
{
    while( root->next != nullptr ) root = root->next;
    return root;
}

void print(path sol, char begin)
{
    std::cout << begin;
    for( size_t i = 0; i < sol.seq.size(); ++i )
    {
        std::cout << sol.seq[i]->dest->name;
    }
    return;
}

int main(void)
{
    char begin, end;
    std::cin >> begin >> end;

    char source, dest;
    float weight;

    node* root = new node(begin);
    node* iter_s;
    node* iter_d;

    while( std::cin >> source >> dest >> weight )
    {
        if( dest == source ) continue;
        if( !(iter_s = find(source, root)) )
        {
            iter_s = new node(source);
            it(root)->next = iter_s;
        }

        if( !(iter_d = find(dest, root)) )
        {
            iter_d = new node(dest);
            it(root)->next = iter_d;
        }

        iter_s->childs.push_back(way(iter_d, weight));
    }

    std::vector<path> arr;

    for(auto& w : root->childs )
    {
        arr.push_back( path() );
        arr.back().seq.push_back(&w);
        arr.back().weight = w.weight;
    }

    path* min;
    size_t index;
    size_t min_name_dif;
    size_t next_name_dif;

    while(true)
    {
        index = 0;
        while( arr[index].seq.back()->dest->name == end ) if( ++index >= arr.size() ) break;

        if( index < arr.size() )
        {
            min = &arr[index];
        }
        else
        {
            print( arr[0], begin );
            return 0;
        }

        for( size_t i = 0; i < arr.size(); ++i )
        {
            min_name_dif = std::abs( end - min->seq.back()->dest->name );
            next_name_dif = std::abs( end - arr[i].seq.back()->dest->name );

            if( min->weight + min_name_dif > arr[i].weight + next_name_dif )
            {
                min = &arr[i];
                index = i;
            }
        }

        if( min->seq.back()->dest->name != end )
        {
            for(auto& p : min->seq.back()->dest->childs )
            {
                arr.push_back( *min ); //add the same
                arr.back().seq.push_back(&p); //add new way to it
                arr.back().weight += p.weight; //increase weight
            }
            arr.erase(arr.begin()+index);
        }
    }
}