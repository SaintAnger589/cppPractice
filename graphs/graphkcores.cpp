#include<iostream>

using namespace std;

class Graph{
	int V;
	list <int> *adj;
public:
	Graph(int V);
	void addedge(int u, int v);
	bool DfsUtil()
	void printKcores();
};

Graph :: Graph(int V){
	this->V = V;
	adj = new list[V];
}

void Graph :: addedge(int u, int v){
	adj[u].push_back(v);
	adj[v].push_back(u);
}

bool DfsUtil(startvertex, visited, vdegrees, k){
	visited[startvertex] = 1;

	if (vdegrees[startvertex] < k){

	}

	list <int>:: itrerator i;
	for (i=adj[startvertex].begin(); i!= adj[startvertex].end();i++){
		if (visited[*i] == 0){
			

		}
	}

}