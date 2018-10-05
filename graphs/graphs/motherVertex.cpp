#include<iostream>
#include <stdio.h>
#include<malloc.h>
#include<list>

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

struct AdjNode *createNode(int v){
    struct AdjNode *root = (struct AdjNode*) malloc(sizeof(struct AdjNode));
    root->val = v;
    root->next = NULL;
    return root;
};

struct Graph *createGraph(int V){
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjListNode *)malloc(sizeof(struct AdjListNode)*V);
    //graph->array = (struct AdjListNode *)malloc(sizeof(struct AdjListNode)*V);
    int i;
    for (i=0;i<V;i++){
        graph->array[i].head = NULL;
    }
    return graph;
};

void addEdge (Graph *graph, int start, int val){
    struct AdjNode *node = createNode(val);
    //struct AdjNode *backnode = createNode(start);
    node->next = graph->array[start].head;
    graph->array[start].head = node;

    //backnode->next = graph->array[val].head;
    //graph->array[val].head = backnode;
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

void visitedReset(int *visited, int len){
    int i;
    for (i=0;i<len;i++){
        visited[i] = 0;
    }
}

int checkVisited(int *visited, int len){
    int flag = 0;
    int i;
    for (i=0;i<len;i++){
        if (visited[i] == 0){
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    return 1;
    else return 0;
}

void dfsRun(struct Graph *graph, int start, int *visited){
    //for (i=0;i<len;i++){
        //cout<<"i = "<<i<<"\n";
    //    visited[i] = 0;
    //}
    //cout<<"\n";
    list<int> temp;
    temp.push_back(start);
    while (temp.size() > 0){
        int value = temp.back();
        if (!visited[value]){
            visited[value] = 1;
            cout<<"value = "<<value<<"\n";
        }
        temp.pop_back();
        //cout<<"printing all the nodes"<<"\n";
        cout<<"graph head = "<<graph->array[value].head<<"\n";
        while (graph->array[value].head){
            cout<<"same node"<<"\n";
            int temp2 = graph->array[value].head->val;
            cout<<temp2<<"\n";
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
void printVisited(int *arr, int len){
    int i;
    for (i=0;i<len;i++){
        cout<<"visited["<<i<<"] = "<<arr[i]<<"\n";
    }

}

int motherVertex(Graph *graph){
    int len = graph->V;
    int *visited = new int[len];
    int i;
    for (i=0;i<len;i++){
        //turn visited
        visitedReset(visited, len);
        cout<<"after Reset"<<"\n";
        printVisited(visited, len);

    //DFS
    dfsRun(graph, i, visited);
    cout<<"after DFS Run"<<"\n";
    printVisited(visited, len);
    //check visited all i
    if (checkVisited(visited, len))
        return i;
    }
}

int main (){
int V = 7;
struct Graph *adj = createGraph(V);

    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 4, 1);
    addEdge(adj, 5, 2);
    addEdge(adj, 5, 6);
    addEdge(adj, 6, 0);
    addEdge(adj, 6, 4);
    printGraphs(adj);

    int result = motherVertex(adj);
    cout<<"MotherVertex is  = "<<result;
return 0;
}
