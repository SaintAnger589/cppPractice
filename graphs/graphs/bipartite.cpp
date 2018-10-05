

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


void bipartite(struct Graphs *graph, int start, int *visited, int *color, int parent, int &res, list<int> b){

    int len = graph->V;
    while (graph->array[start].head != NULL){
        cout<<"visited ["<<graph->array[start].head->val<<"] = "<<visited[graph->array[start].head->val]<<"\n";
        //cout<<"parent = "<<parent<<"\n";
        //cout<<"start = "<<start<<"\n";
        if (visited[graph->array[start].head->val] == 0 && parent != start){
            color[graph->array[start].head->val] = 1 - color[start];
            cout<<"color change of node [ "<<graph->array[start].head->val<<" ] = "<< color[graph->array[start].head->val]<<"\n";
            cout<<"color change of node [ "<<start<<" ] = "<< color[start]<<"\n";
            b.push_back(graph->array[start].head->val);
        }
            graph->array[start].head = graph->array[start].head->next;
    }
    visited[start]  =1;
    while (b.size() > 0){
        int temp = b.front();
        b.pop_front();
        cout<<"temp = "<<temp<<"\n";
        if (visited[temp] == 0 && parent != start){
            bipartite(graph, temp, visited, color, start, res, b);
        }
        else if (visited[temp] == 1 && parent != temp && temp != start){
            if (color[temp] != (1 - color[start])){
                res = res & 0;
                cout<<"start in bipartitie = "<<start<<"\n";
                cout<<"temp in bipartitie = "<<temp<<"\n";
                cout<<"parent in bipartitie = "<<parent<<"\n";
                cout<<"visited in bipartitie = "<<visited[temp]<<"\n";
                cout<<"color tempt in bipartitie = "<<color[temp]<<"\n";
                cout<<"color start in bipartitie = "<<color[start]<<"\n";

            }

        }
    }
}

int isodd(int count){
    if (count % 2 == 0)
        return 0;
    else return 1;
}
void DFSiterative(struct Graphs *graph, int start, int *visited, int parent, int count, int &res) {
  int len = graph->V;
  visited[start] = 1;
  while (graph->array[start].head != NULL){
    if (visited[graph->array[start].head->val] == 0 && parent != graph->array[start].head->val){
        DFSiterative(graph, graph->array[start].head->val, visited, start, count, res);
    }
  }
    graph->array[start].head = graph->array[start].head->next;
}


void printBFS(struct Graphs *graph, int start, int endval, int &count){
    int len = graph->V;
    int i;
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
            cout<<value<<"\n";
        }
        temp.pop_back();
        while (graph->array[value].head != NULL){
            int temp2 = graph->array[value].head->val;
           if (temp2 == endval){
            count++;
            //continue;
           }
            if (visited[temp2] == 0){
              //cout<<"pushing"<<temp2<<"\n";
              temp.push_back(temp2);
            }
            graph->array[value].head = graph->array[value].head->next;
        }
    }



}

int main (){
int V = 6;
struct Graphs *adj = createGraph(V);
    list <int> b;

    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 0);
    addEdge(adj, 1, 3);
    addEdge(adj, 2, 0);
    addEdge(adj, 2, 4);
    addEdge(adj, 3, 1);
    addEdge(adj, 3, 5);
    addEdge(adj, 4, 2);
    addEdge(adj, 4, 5);
    addEdge(adj, 5, 3);
    addEdge(adj, 5, 4);
    //printGraphs(adj);
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
    //printBFS(adj, 0, 4, count);
    //DFSiterative(adj, 0,visited, NULL, 0, res);
    bipartite(adj, 0, visited, color, 10, res, b);

    for (i=0;i<V;i++)
        cout<<"color of "<<i<<" = "<<color[i]<<"\n";

    cout<<"res = "<<res<<"\n";
return 0;
}


