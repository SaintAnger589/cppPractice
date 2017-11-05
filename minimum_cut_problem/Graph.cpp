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
			//std::cout<<"createGraph: val = "<<val<<"\n";
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
    //std::cout<<"in printGraphs"<<"\n";
    //std::cout<<"V = "<<graph->V<<"\n";
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

//creating combine
struct Graph * combinegraph(struct Graph *graph, int index1, int index2){
	//size of new graph is one less
	int valNew = graph->V;
	struct Graph *graphNew = createGraph(valNew);
	std::cout<<"index1: "<<index1<<"\t index2: "<<index2<<"\n";
	int i;
	for (i=0;i<valNew;i++){
		if (i != index1 && i != index2){
			graphNew->array[i].head = graph->array[i].head;
		}
	}
	//joining on the minindex of the two
	//int minindex = index1 > index2 ? index2: index1;
	graphNew->array[index1] = graph->array[index1];
	struct AdjListNode *pCrawl = graphNew->array[index1].head;
	while (pCrawl->next != NULL){
		pCrawl = pCrawl->next;
	}
	//if (minindex == index1){
		pCrawl->next = graph->array[index2].head;
	//} else{
	//	pCrawl->next = graph->array[index1].head;
	//}
    //changing all index2 to index1
    for (i=0;i<valNew;i++){
    	struct AdjListNode *pCrawl = graphNew->array[i].head;
    	while (pCrawl != NULL){
    		if (pCrawl->next){
    			if (pCrawl->next->dest == index2)
    			    pCrawl->next->dest = index1;	
    		}
    		
    		pCrawl = pCrawl->next;
    	}

    }
    //removing cycles for index1
    	struct AdjListNode *pCrawl1 = graphNew->array[index1].head;
    	while(pCrawl1 != NULL){
    		if (pCrawl1->next != NULL){
    			if (pCrawl1->next->dest == index1){
    			    pCrawl1->next = pCrawl1->next->next;
    		    }	
    		}
    		//printGraph(graphNew);
    		if (pCrawl1 != NULL)
    		    pCrawl1 = pCrawl1->next;
    	}
    
    //deleting the index2 and changing size
    for (i=index2;i<valNew-1;i++){
    	graphNew->array[i].head = graphNew->array[i+1].head;
    }
    //reducing all values by 1
    for (i=0;i<valNew-1;i++){
    	struct AdjListNode *pCrawl2 = graphNew->array[i].head;
    	while (pCrawl2 != NULL){
    		if (pCrawl2->dest > 0){
    			pCrawl2->dest = pCrawl2->dest - 1;
    		}
    	    pCrawl2 = pCrawl2->next;
    	}
    }
     //removing cycles
    for (i=0;i<valNew - 1;i++){
    	struct AdjListNode *pCrawl2 = graphNew->array[i].head;
    	//checking for head
    	if (pCrawl2 != NULL){
    	    if (pCrawl2->dest == i){
    		    if (pCrawl2->next != NULL)
    		        pCrawl2->next = pCrawl2->next->next;
    	    }	
    	}
    	while (pCrawl2 != NULL){
    		if (pCrawl2->next != NULL){   
    		    if (pCrawl2->next->dest == i){
    		    	std::cout<<"\n removing the cycle \n";
    		    	pCrawl2->next = pCrawl2->next->next;
    		    }	
    		}
    		if (pCrawl2 != NULL)
    		    pCrawl2 = pCrawl2->next;
    	}//while
    }//for

    graphNew->V = valNew - 1;
	return graphNew;
}

int calcsize(struct Graph *graph){
	struct AdjListNode *pCrawl = graph->array[0].head;
	int count  = 0;
	while(pCrawl != NULL){
		count++;
		pCrawl = pCrawl->next;
	}
	return count;
}
// Driver program to test above functions
int main()
{
    // create the graph given in above fugure
    int V = 4;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 3);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    //addEdge(graph, 1, 0);
    //addEdge(graph, 2, 0);
    //addEdge(graph, 2, 1);
    addEdge(graph, 2, 3);
    //addEdge(graph, 3, 2);
    //addEdge(graph, 3, 0);
 

 	std::cout<<"printing original graph \n";
    // print the adjacency list representation of the above graph
    printGraph(graph);


    struct Graph* graph2 = combinegraph(graph,0,1);
    std::cout<<"graph2->V : "<<graph2->V<<"\n";
    //graph2 = combinegraph(graph2,0,1);
    //std::cout<<"graph2->V : "<<graph2->V;
    printGraph(graph2);	
    while (graph2->V > 2){
    	graph2 = combinegraph(graph2,0,1);
    	//printGraph(graph2);	
    }
    
    printGraph(graph2);

    //calculate size
    int maxcut = calcsize(graph2);
    std::cout<<"*****************\n";
    std::cout<<"maxcut = "<<maxcut<<"\n";
    std::cout<<"*****************\n";
 
    return 0;
}