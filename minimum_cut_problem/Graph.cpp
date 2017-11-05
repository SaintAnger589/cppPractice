#include<iostream>
		struct AdjListNode {
			int dest;
			struct AdjListNode *next;
		};

		struct AdjList {
			struct AdjListNode *head;
		};
		struct Graph
		{
			int V;
			struct AdjList *array;
		};
		//function to create adjlistnode
		struct AdjListNode* newAdjListNode(int dest){
			struct AdjListNode *newAdjNode = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
			newAdjNode->dest = dest;
			newAdjNode->next = NULL;
			return newAdjNode;
		}
		//creating Graphs
		struct Graph* createGraph(int val){
			std::cout<<"createGraph: val = "<<val<<"\n";
			struct Graph *newGraph = (struct Graph *)malloc(sizeof(struct Graph));
			newGraph->array = (struct AdjList*)malloc(sizeof(struct AdjList)*val);
			int i;
			for (i=0;i<val;i++){
				newGraph->V = val;
				newGraph->array[i].head = NULL;
			}
			return newGraph;
		}

		void addEdge(struct Graph* graph, int src, int dest){

			struct AdjListNode *newNode = newAdjListNode(dest);
			newNode->next = graph->array[src].head;
			graph->array[src].head = newNode;

			newNode = newAdjListNode(src);
			newNode->next = graph->array[dest].head;
			graph->array[dest].head = newNode;
		}

		// A utility function to print the adjacenncy list representation of graph
void printGraph(struct Graph* graph)
{
    int v;
    std::cout<<"in printGraphs"<<"\n";
    std::cout<<"V = "<<graph->V<<"\n";
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

// Driver program to test above functions
int main()
{
    // create the graph given in above fugure
    int V = 5;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
 
    // print the adjacency list representation of the above graph
    printGraph(graph);
 
    return 0;
}