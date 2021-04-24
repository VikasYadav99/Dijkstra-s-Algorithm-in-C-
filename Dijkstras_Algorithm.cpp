#include<iostream>
#include<math.h>
#include<map>
#include<vector>
#include<list>
using namespace std;

class node{
    public:
        int id, nearest_node_id;
        float x, y, cost = 100000;
        vector <int> connections;

        void init(int ID, float X, float Y){
            id = ID;
            x = X;
            y = Y;
        }

        float operator - (node &n){
            return sqrt(pow(x-n.x, 2) + pow(y-n.y, 2));
        }

        bool is_connected_to(node &n){
            for(int i=0; i<connections.size(); i++)
                if(n.id == connections[i])   return true;
            return false;
        }

        void connect(node &n){
            if(!is_connected_to(n))                connections.push_back(n.id);
            if(!n.is_connected_to(*this))          n.connections.push_back(id);
        }

        void disp(){
            cout<<"id = "<<id<<"\tcoordinates = "<<x<<", "<<y<<"\tConnections = ";

            for(int i=0; i<connections.size(); i++)    cout<<connections[i]<<"  ";
            cout<<"\tCost = "<<cost;
            cout<<"\tNearest node id = "<<nearest_node_id<<endl;
        }

        void set_costs(map<int, node> &nodes){
            for(auto i=nodes.begin(); i != nodes.end(); i++)
                (*i).second.cost = -1;
            
            cost = 0;
            vector <int> pq;
            pq.insert(pq.begin(), id);

            while(!pq.empty()){
                node &n = nodes[pq[0]];    
                pq.erase(pq.begin());

                for(auto i=n.connections.begin(); i != n.connections.end(); i++){
                    node &next_n = nodes[*i];
                    float g = (n - next_n) + n.cost;

                    if(g < next_n.cost || next_n.cost == -1){
                        next_n.cost = g;
                        next_n.nearest_node_id = n.id;
                
                        int j=0;
                        for(j=0; j<pq.size(); j++)
                            if(nodes[pq[j]].cost > next_n.cost)
                                break;
                
                        pq.insert(pq.begin()+j, next_n.id);
                    }
                }
            }
        }
};

list <int> find_shortest_path(int start, int finish, map<int, node> &nodes){
    nodes[finish].set_costs(nodes);
    list<int> l;

    int id = start;
    while(true){
        l.push_back(id);
        if(id != finish)         id = nodes[id].nearest_node_id;
        else                     break;    
    }

    return l;
}

int main(){
    map<int, node> n;

    n[0].init(0, 0, -20);
    n[1].init(1, 20, 0);
    n[2].init(2, 20, 40);
    n[3].init(3, -20, 40);
    n[4].init(4, -40, 20);
    n[5].init(5, -20, 0);
    n[6].init(6, 0, 20);

    n[0].connect(n[1]);
    n[0].connect(n[5]);
    n[1].connect(n[2]);
    n[1].connect(n[5]);
    n[2].connect(n[3]);
    n[2].connect(n[6]);
    n[3].connect(n[4]);
    n[3].connect(n[5]);
    n[4].connect(n[5]);
    n[4].connect(n[6]);

    list<int> l = find_shortest_path(0, 4, n);
    
    cout<<"Shortest route: ";
    for(auto i=l.begin(); i!=l.end(); i++)
        cout<<*i<<"\t";
    
    return 0;
}