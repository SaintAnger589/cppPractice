#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<vector>
#include<list>
using namespace std;

//graph definition

class Graph{
    int V;
    list <int> *adj;
    list<int> *adjw;

public:
    Graph(int V, int w){
        this->V = V;
        this->adj = new list<int>[V];
        this->adjw = new list<int>[V];
    };
    void addEdge(int u, int v, int w);
    //void isOddLength(int source, int parent, int &res, int *visited);
    void allpaths(int, int, vector < vector <int> > &, vector <int > &, int);

};

void Graph::addEdge(int u, int v, int w){
    this->adj[u].push_back(v);
    this->adjw[u].push_back(w);
    //this->adj[v].push_back(u);
    //this->adjw[u].push_back(w);
};

void Graph::allpaths(int s, int e, vector <vector <int> > &res, vector < int > &p, int l){
    cout<<"start = "<<s<<"\n";
    if (s == e){
        p.push_back(e);
        cout<<"p size"<<p.size()<<"\n";
        res.push_back(p);
        //p.clear();
        //jp.push_back(l);
        return;
    }
    p.push_back(s);
    list <int>::iterator u;
    for (u = adj[s].begin(); u != adj[s].end();u++){
        allpaths(*u, e, res, p, l);
        p.pop_back();
        //cout<<"array->head = "<<graph->array[start].head->val<<"\n";
        //graph->array[start].head = graph->array[start].head->next;
    }
    //visited[s] = 0;
    //p.clear();
}
int main(){
    int V = 4;
    struct Graph g(V,V);
    g.addEdge(0, 1, -1);
    g.addEdge(0, 4, -1);
    g.addEdge(0, 2, -1);
    g.addEdge(1, 4, -1);
    g.addEdge(1, 3, -1);
    g.addEdge(2, 4, -1);
    g.addEdge(3, 2, -1);
    //kprintGraphs(adj);
    //bellman(adj, 0, res);
    vector<vector <int> > res;
    vector<int> p;
    g.allpaths(0, 4, res, p, 0);
    //cout<<"res = "<<res<<"\n";
    cout<<"size of result"<<res.size()<<"\n";
    int i;
    while (res.size() > 0){
            cout<<"res size"<<res.size()<<"\n";
        vector<int> temp;
        temp = res.back();
        res.pop_back();
        cout<<"temp size"<<temp.size()<<"\n";
        while(temp.size() > 0){
            cout<<"value = "<<temp.back()<<"\n";
            temp.pop_back();
        }
    }
}

