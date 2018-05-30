#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 2147483647

using namespace std;

class WayTo{
public:
    char from,to;
    float weight;
    bool correct;
    //int flow;
    WayTo(): from('\0'), to('\0'), weight(0), correct(true){}
    WayTo(char _from, char _to, double _weight): from(_from), to(_to), weight(_weight), correct(true){}
};

int heuristic_func(char a,char b){
    int _a=(int)a;
    int _b=(int)b;
    return _b-_a;
}

int Solution(vector<WayTo> &way, char a, int k, vector<char> &answer){
    WayTo min;
    int min_heur=MAX;
    vector<WayTo> wayAnother;
 
    for (int i = 0; i < way.size(); i++)
        if ((way[i].from == a) && (way[i].correct)) {
        //cout << way[i].from <<" "<<way[i].to<<endl;
        wayAnother.push_back(way[i]);}
      
    for (int i = 0; i < wayAnother.size(); i++){
        if(min_heur>=(heuristic_func(wayAnother[i].to,'e')+wayAnother[i].weight)&&(wayAnother[i].from == a) && (wayAnother[i].correct)) 
        {
        min = wayAnother[i];k=i;        
        min_heur=heuristic_func(wayAnother[i].to,'e')+wayAnother[i].weight;
        //cout << min.from<<"-min-"<<min.to<<"-->"<<min_heur<<endl;
        }//
        }
    
    for (int i = 0; i < way.size(); i++){
       if ((way[i].from == min.from) && (way[i].to == min.to)){ k = i; break;}}
    //cout <<"INDEX:"<<k<<endl;  
    //cout << min.from<<"->"<<min.to<<" "<<min.correct<<endl;    
           
    if (min.weight == 0.0f )
     {
        way[k].correct = false; 
        return -1;
     }

    for (int i = 0; i < way.size(); i++){
        if ((way[i].weight < min.weight) && (way[i].from == a) && (way[i].correct)) 
        {
                //min = way[i]; k = i;
        }
    }
    
    if (find(answer.begin(), answer.end(), way[k].to) != answer.end()) 
    {
        way[k].correct = false; 
        return -1;
    }
    return k;
}

int main(){
    //int edges;
    //cin>>edges;
    char a, b;
    cin >> a; 
    cin >> b;
    vector<WayTo> way;
    //WayTo currway;
    char tmp,tmp2;
    
    float weight;
    while (tmp2!=b){
        cin >> tmp >> tmp2 >> weight;
        WayTo currway(tmp, tmp2, weight);
        way.push_back(currway);
    }
    char curr = a;
    int i = 0;
    vector<char> sequence;
    
    vector<WayTo> go;
    double minway=MAX;
    int indexMin=0,maxFlow=0;
    bool breakFrom=true;
    
   while(true){
        //
        breakFrom=true;
        for(int y=0;y<way.size();y++){
            if(way[y].from==a) {
               if(way[y].correct){
               //cout << way[y].from<<"->"<<way[y].to<<" "<<way[y].correct<<endl;
               breakFrom=false;
               }
               //else breakFrom=true;
            }
        }
        
        if(breakFrom) break;
                    
        sequence.push_back(curr);
        i = Solution(way, curr, i, sequence);
        
        if (i == -1) {//error in way
                i = 0;
                curr = a;
                sequence.clear();
                
        }
        else {         
        curr = way[i].to;
        }
        
        if (way[i].to == b) { //way finished, do some special actions
        
        sequence.push_back(b);
     
                      
        for(int i=0;i<sequence.size();i++) cout << sequence[i];
        cout << endl;
        
        break;
        sequence.clear();
        
        }
    }
    //cout << heuristic_func('a','b')<<endl;
            
    //for (int i = 0; i<way.size(); i++){
    //cout << way[i].from<<" "<<way[i].to<<" "<<way[i].flow<<endl;
    //}
   
}
