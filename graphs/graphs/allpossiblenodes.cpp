
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



int printBFS(struct Graphs *graph, int start, int endval){
    int len = graph->V;
    int i;
    int count = 0;
    int *visited = new int[len];
    for (i=0;i<len;i++){
        visited[i] = 0;
    }
    list<int> temp;
    temp.push_back(start);
    while (temp.size() > 0){
        int value = temp.back();
        if (!visited[value]){
            visited[value] = 1;
        }
        temp.pop_back();
        while (graph->array[value].head != NULL){
            int temp2 = graph->array[value].head->val;
            if (visited[temp2] == 0){
              temp.push_back(temp2);
              //visited[temp2] = 1;
              if (temp2 == endval){
                cout<<"endval = "<<temp2<<"\n";
                cout<<"count = "<<count<<"\n";
                count++;
              }

            }
            graph->array[value].head = graph->array[value].head->next;
        }
    }
    return count;
}

int main (){
int V = 6;
struct Graphs *adj = createGraph(V);

    addEdge(adj, 0, 1);
    addEdge(adj, 0, 4);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 4);
    addEdge(adj, 1, 3);
    //addEdge(adj, );
    addEdge(adj, 2, 4);
    addEdge(adj, 3, 2);
    addEdge(adj, 4, 5);

    int len = V;
        int *visited = new int[len];
        int i;
    for (i=0;i<len;i++){
        visited[i] = 0;
    }
int count = printBFS(adj,0,5);
cout<<"number of possible edges" << count<<"\n";
return 0;
}


