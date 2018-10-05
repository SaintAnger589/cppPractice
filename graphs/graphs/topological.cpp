
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
    //struct AdjNode *backnode = createNode(start);
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

void DFS(struct Graphs *graph, int pos, int *visited, vector<int> &stk, int *flag){
    int len = graph->V;
    visited[pos] = 1;
    while(graph->array[pos].head){
        if (visited[graph->array[pos].head->val] == 0){
            DFS(graph, graph->array[pos].head->val, visited, stk, flag);
        }
        graph->array[pos].head = graph->array[pos].head->next;
    }
    cout<<"pushing in the stk pos = "<<pos<<"\n";

    //if (flag[pos] == 0) {
      flag[pos] = 1;
      stk.push_back(pos);
    //}

}

int main (){
int V = 6;
int i;
struct Graphs *adj = createGraph(V);

    addEdge(adj, 2, 3);
    addEdge(adj, 3, 1);
    addEdge(adj, 4, 0);
    addEdge(adj, 4, 1);
    addEdge(adj, 5, 0);
    addEdge(adj, 5, 2);
    printGraphs(adj);
    //printBFS(adj,2);

    int len = adj->V;
    vector<int> stk;
    int *visited = new int[len];
    int *flag = new int[len];
    for (i=0;i<len;i++){
        visited[i] = 0;
        flag[i] = 0;
    }
    for (i=0;i<len;i++){
        DFS(adj, i, visited, stk, flag);
    }

    cout<<"size of stk = "<<stk.size()<<"\n";
    while (stk.size() > 0){
        int temp = stk.back();
        cout<<"temp = "<<temp<<"\n";
        stk.pop_back();
    }

return 0;
}

