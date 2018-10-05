#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<vector>
#include<list>

using namespace std;


//------------------------------

struct WeightNode{
    int valw;
    struct WeightNode *nextw;
};

struct WeightListNode{
    struct WeightNode *headw;
};

struct Weights{
    int V;
    struct WeightListNode *arrayw;
};

struct WeightNode *createWeightNode(int w){
    struct WeightNode *rootw = (struct WeightNode *)malloc(sizeof(struct WeightNode));
    rootw->valw = w;
    rootw->nextw = NULL;
    return rootw;
};

struct Weights *createWeight(int V){
    struct Weights *graphw = (struct Weights *)malloc(sizeof(struct Weights));
    graphw->V = V;
    graphw->arrayw = (struct WeightListNode *)malloc(sizeof(struct WeightListNode)*V);
    for (int i=0;i<V;i++){
        graphw->arrayw[i].headw = NULL;
    }
    return graphw;
};

void addEdgeWeight(struct Weights *graphw, int start, int w){
    //struct WeightNode *node = createWeightNode(nodeVal);
    struct WeightNode *node = createWeightNode(w);
    node->nextw = graphw->arrayw[start].headw;
    graphw->arrayw[start].headw = node;

    //backnode->nextw = graphw->arrayw[nodeVal].headw;
    //graphw->arrayw[nodeVal].headw = backnode;
};


//---------------------------------

struct AdjNode{
    int val;
    int w;
    struct AdjNode *next;
};

struct AdjListNode{
    struct AdjNode *head;
};

struct Graphs{
    int V;
    struct AdjListNode *array;
};


struct AdjNode *createNode(int v, int w){
    struct AdjNode *root = (struct AdjNode *)malloc(sizeof(struct AdjNode));
    root->val = v;
    root->w = w;
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

void addEdge(struct Graphs *graph, int start, int nodeVal, int w){
    struct AdjNode *node = createNode(nodeVal, w);
    //cout<<"created node\n";
    struct AdjNode *backnode = createNode(start, w);
    //cout<<"created weight\n";
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
            cout<<graph->array[i].head->val<<"\n";
            graph->array[i].head = graph->array[i].head->next;
        }
        cout<<"\n";
    }
};

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

int checkCount(int count, int k){
    if (count >= k)
        return 1;
    else return 0;
}

void DFS(Graphs *graph, int *visited, int parent, int start, int &count, int &res, int k){
    visited[start] = 1;
    cout<<start<<"\n";
    //cout<<"weight = "<<graph->array[start].head->w<<"\n";
    struct AdjNode *temp = (struct AdjNode *)malloc(sizeof(struct AdjNode));
    temp = graph->array[start].head;
    while (graph->array[start].head != NULL){
        //cout<<"start = "<<start<<"\n";
        //cout<<"visited = "<<graph->array[start].head->val<<"\n";
        
        if (visited[graph->array[start].head->val] == 0 && parent != graph->array[start].head->val)
        {
            cout<<"weight = "<<graph->array[start].head->w<<"\n";
            count = count + graph->array[start].head->w;
            res = res | checkCount(count, k);
            cout<<"countdfs = "<<count<<"\n";

            DFS(graph, visited, start, graph->array[start].head->val, count, res, k);
            cout<<"returning back\n";
            count = count - graph->array[start].head->w;
            visited[graph->array[start].head->val] = 0;

            //cout<<"begin = "<<graph->array[start].begin()<<"\n";
           
        } 
        graph->array[start].head = graph->array[start].head->next;
        //visited[start] = 0;

    }

    graph->array[start].head = temp;
}

int main (){
int V = 9;
struct Graphs *adj = createGraph(V);
struct Weights *wei = createWeight(V);
//struct Graphs *adj = createGraph(V);

    addEdge(adj, 0, 1, 4);
    addEdge(adj, 0, 7, 8);
    addEdge(adj, 1, 7, 11);
    //addEdge(adj, 1, 0, 4);
    addEdge(adj, 1, 2, 8);
    addEdge(adj, 2, 8, 2);
    //addEdge(adj, 2, 1, 8);
    addEdge(adj, 2, 5, 4);
    addEdge(adj, 2, 3, 7);
    addEdge(adj, 3, 5, 14);
    addEdge(adj, 3, 4, 9);
    //addEdge(adj, 3, 2, 7);
    //addEdge(adj, 4, 3, 9);
    addEdge(adj, 4, 5, 10);
    //addEdge(adj, 5, 4, 10);
    //addEdge(adj, 5, 3, 14);
    //addEdge(adj, 5, 2, 4);
    addEdge(adj, 5, 6, 2);
    //addEdge(adj, 6, 5, 2);
    addEdge(adj, 6, 8, 6);
    addEdge(adj, 6, 7, 1);
    //addEdge(adj, 7, 6, 1);
    addEdge(adj, 7, 8, 7);
    //addEdge(adj, 7, 1, 11);
    //addEdge(adj, 7, 0, 8);
    //addEdge(adj, 8, 7, 7);
    //addEdge(adj, 8, 6, 6);
    //addEdge(adj, 8, 2, 2);

/*
    //-----------------------
    addEdgeWeight(wei, 0, 4);
    addEdgeWeight(wei, 0, 8);
    addEdgeWeight(wei, 1, 11);
    addEdgeWeight(wei, 1, 4);
    addEdgeWeight(wei, 1, 8);
    addEdgeWeight(wei, 2, 2);
    addEdgeWeight(wei, 2, 8);
    addEdgeWeight(wei, 2, 4);
    addEdgeWeight(wei, 2, 7);
    addEdgeWeight(wei, 3, 14);
    addEdgeWeight(wei, 3, 9);
    addEdgeWeight(wei, 3, 7);
    addEdgeWeight(wei, 4, 9);
    addEdgeWeight(wei, 4, 10);
    addEdgeWeight(wei, 5, 10);
    addEdgeWeight(wei, 5, 14);
    addEdgeWeight(wei, 5, 4);
    addEdgeWeight(wei, 5, 2);
    addEdgeWeight(wei, 6, 2);
    addEdgeWeight(wei, 6, 6);
    addEdgeWeight(wei, 6, 1);
    addEdgeWeight(wei, 7, 1);
    addEdgeWeight(wei, 7, 7);
    addEdgeWeight(wei, 7, 11);
    addEdgeWeight(wei, 7, 8);
    addEdgeWeight(wei, 8, 7);
    addEdgeWeight(wei, 8, 6);
    addEdgeWeight(wei, 8, 2);
*/
    int res = 0;
    int k = 58; 
    int count = 0;

    int *visited = new int[V];
    int i;
    for (i=0;i<V;i++)
        visited[i] = 0;
    
    //DFS(adj, wei, visited, NULL, 0);
    DFS(adj, visited, NULL, 0, count, res, k);

    cout<<"res = "<<res<<"\n";
    cout<<"count = "<<count<<"\n";

    //printGraphs(adj);
    //printBFS(adj,2);



return 0;
}
