#include<iostream>
#include<stdio.h>
#include<list>

using namespace std;

class Graph{
	int V;
	list <int> *adj;

public:
	Graph(int V){
		this->V = V;
		this->adj = new list<int>[V];
	}
	void addedge(int u, int v);
	void kcores(int start, int *visited, int parent, int &flag);
	void printgraph();
};


void Graph::addedge(int u, int v){
	this->adj[u].push_back(v);
}

void Graph::kcores(int start, int *visited, int parent, int &flag){
	if (adj[start].size() < 3){
		visited[start] = 1;
		cout<<"start = "<<start<<"\n";
		flag = 1;
		V--;
		return;
	}
	visited[start] = 1;
	list<int>::iterator i;
	for (i = adj[start].begin(); i != adj[start].end();i++){
		if (visited[*i] == 0){
			kcores(*i, visited, start, flag);
		}
		if (flag == 1){
			cout<<"start1 = "<<start<<"\n";
			cout<<"*i = "<<*i<<"\n";
			flag = 0;
			adj[start].remove(*i);
			adj[*i].remove(start);
		}
		cout<<"start2 = "<<start<<"\n";
		cout<<"start size = "<<adj[start].size()<<"\n";
		if (adj[start].size() < 3){
		    flag = 1;
		    V--;
		    return;
	    }

	}

}

void Graph::printgraph(){
	list<int>::iterator i;
	int j;
	cout<<"V = "<<V<<"\n";
	for (j = 0; j<V;j++){
		cout<<j<<"->"<<"\t";
		for (i = adj[j].begin(); i != adj[j].end();i++){
			cout<<*i<<"\t";
		}
		cout<<"\n";
	}
}

int main(){
	int V = 9;
	Graph g(V);
	g.addedge(0,1);
	g.addedge(0,2);
	g.addedge(1,0);
	g.addedge(1,2);
	g.addedge(1,5);
	g.addedge(2,0);
	g.addedge(2,1);
	g.addedge(2,4);
	g.addedge(2,3);
	g.addedge(2,6);
	g.addedge(3,2);
	g.addedge(3,4);
	g.addedge(3,6);
	g.addedge(3,7);
	g.addedge(4,2);
	g.addedge(4,3);
	g.addedge(4,6);
	g.addedge(4,7);
	g.addedge(5,6);
	g.addedge(5,8);
	g.addedge(5,1);
	g.addedge(6,2);
	g.addedge(6,5);
	g.addedge(6,8);
	g.addedge(6,3);
	g.addedge(6,4);
	g.addedge(6,7);
	g.addedge(7,4);
	g.addedge(7,6);
	g.addedge(7,3);
	g.addedge(8,5);
	g.addedge(8,6);

	g.printgraph();
	int *visited = new int[V];
	int p;
	for (p = 0; p < V;p++){
		visited[p] = 0;
	}
	int flag = 0;
	for (p=0;p<V;p++){
		for (int q = 0; q < V;q++){
		    visited[q] = 0;
	    }
		cout<<"p = "<<p<<"\n";
		g.kcores(p, visited, -1, flag);	
	}
	cout<<"\n";
	cout<<"\n";
	g.printgraph();
}