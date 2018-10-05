#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<vector>
#include<list>
using namespace std;

class Graph{
    int V;
    list <int> *adj;
public:
    Graph(int V){
        this->V = V;
        this->adj = new list<int>[V];
    };
    void addEdge(int u, int v);
    void isOddLength(int start, int parent, int *visited, int c, int n, int &res);

};

void Graph::addEdge(int u, int v){
    this->adj[u].push_back(v);
    //this->adj[v].push_back(u);
};


void Graph::isOddLength(int start, int parent, int *visited, int c, int n, int &res){
    list<int>::iterator i;
    list<int>::iterator j;
    cout<<"start = "<<start<<"\n";
    cout<<"c = "<<c<<"\n";
    cout<<"parent = "<<parent<<"\n";

    if (c == n){

        for (j = adj[start].begin(); j != adj[start].end(); j++ ){
            cout<<"j = "<<*j<<"\n";
            if (visited[*j] == 1 && parent != *j){
                cout<<"*j = "<<*j<<"\n";
                cout<<"\n";
                cout<<"\n";
                res++;
            }
        }
        return;
    }
    visited[start] = 1;
    for (i = adj[start].begin(); i != adj[start].end(); i++ ){
        if (visited[*i] == 0){
            isOddLength(*i, start, visited, c+1, n, res);
            //if (c >= n){
              //c--;
              cout<<"returned value = "<<*i<<"\n";
              visited[*i] = 0;

              //return;
            //}

        }

    }

}

int main(){
    int V = 5;
    struct Graph g(V);
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 4);
    g.addEdge(1, 0);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 1);
    g.addEdge(3, 2);
    g.addEdge(3, 4);
    g.addEdge(3, 0);
    g.addEdge(4, 3);
    g.addEdge(4, 1);

    int *visited = new int[V];
    int j;
    for (j = 0;j < V;j++){
        visited[j] = 0;
    }
    int res = 0;
    for (j = 0;j < V;j++){
        g.isOddLength(j, -1, visited, 1, 4, res);
    }
    cout<<"res = "<<res/2<<"\n";
}
