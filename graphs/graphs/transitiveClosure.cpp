
#include<iostream>
#include <stdio.h>
#include <vector>
#include <list>
using namespace std;
struct AdjNode {
     int val;
     struct AdjNode *next;
};

struct AdjListNode {
    struct AdjNode *head;
};

struct Graph {
    int V;
    struct AdjListNode *array;
};

struct AdjNode *createNode (int val){
    struct AdjNode *node = new struct AdjNode;
    node->val = val;
    node->next = NULL;
    return node;
}

struct Graph *createGraph(int V){
    struct Graph *graph = new struct Graph;
    graph->V = V;
    graph->array = new AdjListNode[V];
    int i;
    for (i=0;i<V;i++){
        graph->array[i].head = NULL;
    }
    return graph;
};

void addEdge (Graph *graph, int pos, int val){
    struct AdjNode *node = createNode(val);
    struct AdjNode *backnode = createNode(pos);

    node->next = graph->array[pos].head;
    graph->array[pos].head = node;

    //backnode = graph->array[val].head;
    //backnode = graph->array[val].head;

}

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

void printvisited(int *visited, int len){
   int i;
   for (i=0;i<len;i++)
    cout<<visited[i]<<"\t";
   cout<<"\n";
}

void DFS(Graph *graph, int *visited, int pos, vector < vector < int > > &arr, int V ){
    //printvisited(visited, V);
    cout<<"pos = "<<pos<<"\n";

    visited[pos] = 1;
    //arr[pos] = 1;
    arr[pos][pos] = 1;
    list <int>::iterator k;
    while(graph->array[pos].head != NULL) {
        cout<<"pos head = "<<graph->array[pos].head->val<<"\n";
        if (visited[graph->array[pos].head->val] == 0){
            visited[graph->array[pos].head->val] =1;
            arr[pos][graph->array[pos].head->val] = 1;

            //cout<<"arr = "<<graph->array[pos].head->val<<"\n";
            DFS(graph, visited, graph->array[pos].head->val, arr, V);
        }
        graph->array[pos].head = graph->array[pos].head->next;
    }
}

void resetVisited(Graph *graph, int *visited, int len){

    int i;
    for (i=0;i<len;i++){

    }
    for (i=0;i<len;i++){
        visited[i] = 0;
    }
}

int main(){
    cout<<"Starting the program"<<"\n";

    const int V = 4;
    int i,j;
    Graph *graph = createGraph(V);
    int *visited = new int[V];
    //int arr[V][V] = {0};
    vector <vector<int> >arr;
    vector <int> row;
    for (i=0;i<V;i++)
        row.push_back(0);



    for (i=0;i<V;i++){
        visited[i] = 0;
        //arr[i]     = 0;
    }
    cout<<"updating arr" <<"\n";

    for (i=0;i<V;i++){
            arr.push_back(row);
    }

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 0);
    addEdge(graph, 2, 3);

    printGraphs(graph);
        Graph *temp = graph;

    //cout<<"arr = "<<*arr[0].back()<<"\n";
    for(i=0;i<V;i++){

        //resetVisited(graph, visited, V);
        DFS(graph, visited, i,arr, V);
        //graph = temp;
    }


    for (i=0;i<V;i++){
        for (j=0;j<V;j++){
            cout<<arr[i][j]<<"\t";
        }
        cout<<"\n";
    }
    return 0;
}

