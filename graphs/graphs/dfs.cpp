
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<vector>
#include<list>

using namespace std;

struct AdjNode{
    int val;
    struct AdjNode *next;
};

struct AdjListNode{
    struct AdjNode *head;
};

struct Graphs{
    int V;
    struct AdjListNode *array;
};

struct AdjNode *createNode(int v){
    struct AdjNode *root = (struct AdjNode *)malloc(sizeof(struct AdjNode));
    root->val = v;
    root->next = NULL;
    return root;
};

struct Graphs *createGraph(int V){
    struct Graphs *graph = (struct Graphs *)malloc(sizeof(struct Graphs));
    graph->V = V;
    graph->array = (struct AdjListNode *)malloc(sizeof(struct AdjListNode)*V);
    for (int i=0;i<V;i++){
        graph->array[i].head = NULL;
    }
    return graph;
};

void addEdge(struct Graphs *graph, int start, int nodeVal){
    struct AdjNode *node = createNode(nodeVal);
    struct AdjNode *backnode = createNode(start);
    node->next = graph->array[start].head;
    graph->array[start].head = node;

    backnode->next = graph->array[nodeVal].head;
    graph->array[nodeVal].head = backnode;
};

void printGraphs(struct Graphs *graph){
    int i;
    for (i=0;i<graph->V;i++){
        cout<<"Adjency list of vertex"<<i<<"\n";
        while (graph->array[i].head){
            cout<<graph->array[i].head->val;
            graph->array[i].head = graph->array[i].head->next;
        }
        cout<<"\n";
    }
};

int isCycle(struct Graphs *graph, int start, int *visited){
  int contains_cycle = 0;
  int len = graph->V;
  if (visited[start] == 0){
    visited[start] = 1;
  }
  while (graph->array[start].head != NULL){
    if (visited[graph->array[start].head->val] == 1){
        contains_cycle = 1;
        break;
    } else {
        contains_cycle = isCycle(graph, graph->array[start].head->val, visited);
    }
    if (contains_cycle == 0){
        graph->array[start].head = graph->array[start].head->next;
    } else {
        break;
    }
  }

}

int isCycleUndirected(struct Graphs *graph, int start, int *visited, int parent){
  int contains_cycle = 0;
  int len = graph->V;
  if (visited[start] == 0){
    visited[start] = 1;
  }
  while (graph->array[start].head != NULL){
    if (visited[graph->array[start].head->val] == 1){
            cout<<"parent = "<<parent<<"\n";
            cout<<"start = "<<graph->array[start].head->val<<"\n";
        if (parent != graph->array[start].head->val){
          contains_cycle = 1;
          break;
        }

    } else {
        contains_cycle = isCycleUndirected(graph, graph->array[start].head->val, visited, start);
    }
    if (contains_cycle == 0){
        graph->array[start].head = graph->array[start].head->next;
    } else {
        break;
    }
  }
}

void DFSiterative(struct Graphs *graph, int start, int *visited) {
  int len = graph->V;
  if (visited[start] == 0){
    visited[start] = 1;
    cout<<start<<"\t";
  }
  while (graph->array[start].head != NULL){
    if (visited[graph->array[start].head->val] == 0){
            cout<<"graph = "<<graph->array[start].head->val<<"\n";
        DFSiterative(graph, graph->array[start].head->val, visited);
    }
    graph->array[start].head = graph->array[start].head->next;
  }
}



void printBFS(struct Graphs *graph, int start){
    int len = graph->V;
    int i;
    int *visited = new int[len];
    for (i=0;i<len;i++){
        //cout<<"i = "<<i<<"\n";
        visited[i] = 0;
    }
    //cout<<"\n";
    list<int> temp;
    temp.push_back(start);
    while (temp.size() > 0){
        int value = temp.back();
        if (!visited[value]){
            visited[value] = 1;
            cout<<value<<"\n";
        }
        temp.pop_back();
        //cout<<"printing all the nodes"<<"\n";
        while (graph->array[value].head != NULL){
            //cout<<"same node"<<"\n";
            int temp2 = graph->array[value].head->val;
            //cout<<temp2<<"\n";
           // cout<<"visited = "<<visited[temp2]<<" temp = "<<temp2<<"\n";
            if (visited[temp2] == 0){
                    //cout<<"Inside if statement"<<"\n";
              temp.push_back(temp2);
              //visited[temp2] = 1;
              //cout<<temp2<<"\n";
            }
            graph->array[value].head = graph->array[value].head->next;
        }
    }



}

int main (){
int V = 5;
struct Graphs *adj = createGraph(V);

    addEdge(adj, 0, 1);
    addEdge(adj, 0, 4);
    addEdge(adj, 1, 2);
    addEdge(adj, 1, 3);
    //addEdge(adj, 1, 4);
    addEdge(adj, 1, 0);
    //addEdge(adj, 2, 3);
    addEdge(adj, 2, 1);
    //addEdge(adj, 3, 4);
    addEdge(adj, 3, 1);
    //addEdge(adj, 3, 2);
    addEdge(adj, 4, 0);
    //addEdge(adj, 4, 1);
    //printGraphs(adj);
    //printBFS(adj,2);
    //printBFS(adj,2);
    int len = V;
        int *visited = new int[len];
        int i;
    for (i=0;i<len;i++){
        //cout<<"i = "<<i<<"\n";
        visited[i] = 0;
    }
    int cycle = 0;
    //DFSiterative(adj, 2, visited);
    for (i=0;i<V;i++){
      cycle = 0;
      cycle = isCycleUndirected(adj,i,visited, -1);
      if (cycle == 1)
            break;
    }


    cout<<"cycle_present"<<cycle<<"\n";

return 0;
}

