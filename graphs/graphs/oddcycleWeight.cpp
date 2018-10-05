#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<vector>
#include<list>
using namespace std;


class Graph{
    int V;
    list <int> *adj;
    list <int> *adjw;
public:
    Graph(int V){
        this->V = V;
        this->adj = new list<int>[V];
        this->adjw = new list<int>[V];
    };
    void addEdge(int u, int v, int w);
    void isOddLength(int start, int parent, int *visited, int sum, int &res);

};

void Graph::addEdge(int u, int v, int w){
    this->adj[u].push_back(v);
    this->adjw[u].push_back(w);
    //this->adj[v].push_back(u);
    //this->adjw[v].push_back(w);
};

void Graph::isOddLength(int start, int parent, int *visited, int sum, int &res){
    list<int>::iterator i;
    list<int>::iterator j;
    visited[start] = 1;
    for (i= adj[start].begin(), j = adjw[start].begin(); i != adj[start].end(), j != adjw[start].end();i++, j++){
        if (visited[*i] == 0){
            isOddLength(*i, start, visited, sum + *j, res);
            visited[*i] = 0;
            sum = sum - *j;
        } else if (visited[*i] == 1 && *i != parent){
            cout<<"*i = "<<*i<<"\n";
            cout<<"sum = "<<sum<<"\n";
            if ((sum + *j)  % 2 != 0)
              res = res | 1;
        }
    }

}


int main(){
    int V = 4;
    struct Graph g(V);
    g.addEdge(0, 1, 12);
    g.addEdge(0, 3, 20);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 0, 12);
    g.addEdge(2, 3, 1);
    g.addEdge(2, 1, 1);
    g.addEdge(3, 0, 20);
    g.addEdge(3, 2, 1);

    int *visited = new int[V];
    int j;
    for (j = 0;j < V;j++){
        visited[j] = 0;
    }
    int res = 0;
    for (j = 0;j < V;j++){
        g.isOddLength(j, -1, visited, 0, res);
    }
    cout<<"res = "<<res<<"\n";
}
