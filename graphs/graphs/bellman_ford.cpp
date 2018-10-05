#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<vector>
#include<list>
using namespace std;

//graph definition

struct AdjNode {
    int val;
    int w;
    struct AdjNode *next;
};

struct AdjListNode {
    struct AdjNode *head;
};

struct Graph {
    int V;
    struct AdjListNode *array;
};

struct AdjNode *createNode(int val, int w){
    struct AdjNode *root = (struct AdjNode *)malloc(sizeof(struct AdjNode));
    root->val = val;
    root->w = w;
    root->next = NULL;
    return root;
};

struct Graph *createGraph(int V){
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjListNode *)malloc(sizeof(struct AdjListNode)*V);
    int i;
    for (int i=0;i<V;i++){
        graph->array[i].head = NULL;
    }
    return graph;
};

void addEdge(struct Graph *graph, int start, int nodeVal, int weight){
    struct AdjNode *node = createNode(nodeVal, weight);
    //struct AdjNode *backnode = createNode(start, weight);
    node->next = graph->array[start].head;
    graph->array[start].head = node;

    cout<<"graph value node"<<graph->array[start].head->val<<"\n";

    //backnode->next = graph->array[nodeVal].head;
    //graph->array[nodeVal].head = backnode;
};

void printGraphs(struct Graph *graph){
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

void bellman(struct Graph *graph, int source, int &res){
    int len = graph->V;
    cout<<"len = "<<len<<"\n";
    int *sumval = new int[len];
    int i;
    for (i=0;i<len;i++){
        sumval[i] = 9999;
        cout<<"sumval [ "<<i<<"] = "<<sumval[i]<<"\n";
    }
    sumval[source] = 0;
    for (i=0;i<len;i++){
        struct AdjNode *temp = (struct AdjNode *)malloc(sizeof(struct AdjNode));
        temp = graph->array[i].head;
        while (graph->array[i].head != NULL){
            cout<<"graph = "<<graph->array[i].head->val<<"\n";
            if (sumval[graph->array[i].head->val] > sumval[i] + graph->array[i].head->w){
                sumval[graph->array[i].head->val] = sumval[i] + graph->array[i].head->w;
                cout<<"sumval [ "<<graph->array[i].head->val<<"] = "<<sumval[graph->array[i].head->val]<<"\n";

            }

            graph->array[i].head = graph->array[i].head->next;
        }
        //resetting the pointer
        graph->array[i].head = temp;
    }
    //another run
    for (i=0;i<len;i++){
        while (graph->array[i].head != NULL){
            if (sumval[graph->array[i].head->val] > sumval[i] + graph->array[i].head->w)
                res = 1;
            graph->array[i].head = graph->array[i].head->next;
        }
    }
    //res = 0;
}

int main(){
    int V = 4;
    struct Graph *adj = createGraph(V);
    addEdge(adj, 0, 1, 1);
    addEdge(adj, 1, 2, -1);
    addEdge(adj, 2, 3, -1);
    addEdge(adj, 3, 0, -1);
    //kprintGraphs(adj);

    int res = 0;
    bellman(adj, 0, res);
    cout<<"res = "<<res<<"\n";

}
