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

    //backnode->next = graph->array[nodeVal].head;
    //graph->array[nodeVal].head = backnode;
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

void DFSiterative(struct Graphs *graph, int start, int level, int n, int *visited, int parent, int &count, int callnode) {
  int len = graph->V;
  //cout<<"inside dfs iterative"<<"\n";
  //cout<<"level = "<<level<<"\n";
  //cout <<"n = "<<n<<"\n";

  if (level == n)
  //if (0)
  {
      struct AdjNode *temp = (struct AdjNode *)malloc(sizeof(struct AdjNode));
      temp = graph->array[start].head;
      while (graph->array[start].head != NULL){
        if (graph->array[start].head->val == callnode){
            count++;
        }
        cout<<"count = "<<count<<"\n";
        graph->array[start].head = graph->array[start].head->next;
      }
      graph->array[start].head = temp;
  }
  cout<<"start = "<<start<<"\n";
  visited[start] = 1;
  //cout<<"starting the while loop\n";
  while (graph->array[start].head != NULL){
    if (visited[graph->array[start].head->val] == 0 && parent != graph->array[start].head->val){
        //cout<<"val = "<< graph->array[start].head->val<<"\n";
        level = level + 1;
        DFSiterative(graph, graph->array[start].head->val,level, n, visited, start, count, callnode);
    }
    graph ->array[start].head = graph->array[start].head->next;
  }
  level--;
  visited[start] = 0;
}

void reset_visited(int *visited, int len){
    int i;
    for (i=0;i<len;i++){
        visited[i] = 0;
    }
}

void print_visited(int *visited, int len){
    int i;
    for (i=0;i<len;i++)
        cout<<visited[i]<<"\t";
    cout<<"\n";
    cout<<"\n";

}


struct Graphs *createnewGraph(){
    int V = 5;
struct Graphs *adj = createGraph(V);
    list <int> b;

    addEdge(adj, 0, 1);
    addEdge(adj, 0, 3);
    addEdge(adj, 1, 0);
    addEdge(adj, 1, 4);
    addEdge(adj, 2, 2);
    addEdge(adj, 2, 1);
    addEdge(adj, 2, 3);
    addEdge(adj, 3, 2);
    addEdge(adj, 3, 0);
    addEdge(adj, 3, 4);
    addEdge(adj, 4, 1);
    addEdge(adj, 4, 3);

    return adj;
};
int main (){
int V = 5;
struct Graphs *adj = createGraph(V);

    int len = V;
        int *visited = new int[len];
        int *color = new int[len];
        int i;
    for (i=0;i<len;i++){
        //cout<<"i = "<<i<<"\n";
        visited[i] = 0;
        color[i] = 0;
    }
    int cycle = 0;
    int count = 0;
    int res = 1;
    int level = 1;
    int n = 4;

    for (i=0;i<V;i++){
      reset_visited(visited, V);
      adj = createnewGraph();
      print_visited(visited, V);
      cout<<"starting new node"<<"\n";
      //cout<<"visited[i] = "<<visited[i]<<"\n";
      DFSiterative(adj, i, level, n, visited, NULL, count, i);
    }




    //for (i=0;i<V;i++)
        //cout<<"color of "<<i<<" = "<<color[i]<<"\n";

    cout<<"count = "<<count<<"\n";
return 0;
}


