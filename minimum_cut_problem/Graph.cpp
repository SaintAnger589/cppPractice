#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include <stdlib.h>
#include <fstream>
#include <ctime>
#include <algorithm> 
#define numNodes 200
#define debug 0

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
			/*
			newNode = newAdjListNode(src);
			newNode->next = graph->array[dest].head;
			graph->array[dest].head = newNode;
			*/
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
	if (debug){
        std::cout<<"printgraph in combinegraph\n";
        printGraph(graph);
    }
    int valNew = graph->V;
	struct Graph *graphNew = createGraph(valNew);
	if (debug){
        std::cout<<"newGraph returned \n";
        std::cout<<"index1: "<<index1<<"\t index2: "<<index2<<"\n";
    }
    int i;
	for (i=0;i<valNew;i++){
		if (i != index1 && i != index2){
			graphNew->array[i].head = graph->array[i].head;
		}
	}
    if (debug)
	    std::cout<<"added all nodes except index1 and index2 \n";
	//joining on the minindex of the two
	//int minindex = index1 > index2 ? index2: index1;
	graphNew->array[index1] = graph->array[index1];
	struct AdjListNode *pCrawl = graphNew->array[index1].head;
	while (pCrawl->next != NULL){
		pCrawl = pCrawl->next;
	}
    if (debug)
	    std::cout<<"reached end of index1\n";
	//if (minindex == index1){
		pCrawl->next = graph->array[index2].head;
        if (debug){
            std::cout<<"after adding index2 to index1"<<"\n";
            printGraph(graphNew);    
        }
        
	//} else{
	//	pCrawl->next = graph->array[index1].head;
	//}
    /*
    //changing all index2 to index1
    std::cout<<"valNew = "<<valNew<<"\n";
    for (i=0;i<valNew;i++){
    	//std::cout<<"i = "<<i<<"\n";
    	struct AdjListNode *pCrawl5 = graphNew->array[i].head;
    	while (pCrawl5 != NULL){
    		//if (pCrawl->next != NULL){
    		//std::cout<<"pcrawl->val"<<pCrawl5->dest<<"\n";
    		//std::cout<<"index2 = "<<index2<<"\n";
    		//std::cout<<"pCrawl5 = "<<pCrawl5->dest<<"\n";
    			if (pCrawl5->dest == index2)
    			    pCrawl5->dest = index1;	
    		//}
    		
    		pCrawl5 = pCrawl5->next;
    		//std::cout<<"pcrawl->val"<<pCrawl->dest;
    	}

    }
    */
    if (debug)
        std::cout<<"changed all index2 to index1\n";
    //printGraph(graphNew);
    //deleting the index2 and changing size
    for (i=index2;i<graphNew->V;i++){
    	graphNew->array[i].head = graphNew->array[i+1].head;
    	
    }
    graphNew->V = graphNew->V - 1;
    if (debug)
        {
            std::cout<<"After removing index2\n";
            printGraph(graphNew);
        }
    //reducing all values by 1 from index2
    for (i=0;i<graphNew->V;i++){
    	struct AdjListNode *pCrawl8 = graphNew->array[i].head;
    	while (pCrawl8 != NULL){
            if (pCrawl8->dest == index2)
                pCrawl8->dest = pCrawl8->dest - index2 + index1;
    		if (pCrawl8->dest > index2){
    			pCrawl8->dest = pCrawl8->dest - 1;
    		}
    	    pCrawl8 = pCrawl8->next;
    	}
    }
    if (debug)
        {
            std::cout<<"After reducing the graph dest by 1\n";
            printGraph(graphNew);
        }
/*
    //changing all index2 to index1
    //std::cout<<"valNew = "<<valNew<<"\n";
    for (i=0;i<graphNew->V;i++){
        //std::cout<<"i = "<<i<<"\n";
        struct AdjListNode *pCrawl10 = graphNew->array[i].head;
        while (pCrawl10 != NULL){
            //if (pCrawl->next != NULL){
            //std::cout<<"pcrawl->val"<<pCrawl5->dest<<"\n";
            //std::cout<<"index2 = "<<index2<<"\n";
            //std::cout<<"pCrawl5 = "<<pCrawl5->dest<<"\n";
                if (pCrawl10->dest == index2)
                    pCrawl10->dest = index1; 
            //}
            
            pCrawl10 = pCrawl10->next;
            //std::cout<<"pcrawl->val"<<pCrawl->dest;
        }

    }
*/
/*
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
*/
//removing cycles
    //for (i=0;i<graphNew->V;i++){
        
        //checking for head
        //if (pCrawl13 != NULL){
            //std::cout<<"dest: "<<pCrawl13->dest<<"\n";
        //for (i=0;i<graphNew->V;i++){
             if (graphNew->array[index1].head != NULL){
                while (graphNew->array[index1].head->dest == index1){
                    graphNew->array[index1].head = graphNew->array[index1].head->next;
                    if (graphNew->array[index1].head == NULL)
                        break;
                }   
             } //if graphNew
               
        //} //i loop
        struct AdjListNode *pCrawl13 = graphNew->array[index1].head;
        while (pCrawl13 != NULL){
            if (pCrawl13->next != NULL){   
                  if (pCrawl13->next->dest == index1){
                    //std::cout<<"\n removing the cycle \n";
                        while (pCrawl13->next->dest == index1){
                            pCrawl13->next = pCrawl13->next->next;
                            if (pCrawl13->next == NULL)
                                break;
                    }
                } //if pcrawl13->next != NULL  
            }
            if (pCrawl13 != NULL)
                pCrawl13 = pCrawl13->next;
        }//while
    //}//for

    //graphNew->V = graphNew->V - 1;
    if (debug)
        {
            std::cout<<"After the iteration"<<"\n";
            printGraph(graphNew);
        }
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

//creatint the basic graph
struct Graph * createNewGraph(){
	    // create the graph given in above fugure
    int V = numNodes;
    struct Graph* graph = createGraph(V);
    //reading file
    /////////////////////////////
    int iter = 0;
    std::ifstream myfile("graphval.txt");
    std::string s;
    int n;
    if (myfile.is_open()){
    	while (getline(myfile,s)){
    		std::vector<int> temp;
    		std::stringstream stream(s);
    		//std::cout<<"string s = "<<s<<"\n";
    		while(stream >> n) {
   				//std::cout<<"n = "<<n<<"\n";
   				temp.push_back(n);
   				if(!stream)
      			    break;
   				//std::cout << "Found integer: " << n << "\n";
			} //while
			int len = temp.size();
			//std::cout<<"len = "<<len<<"\n";
			int temp2;
			//for (temp2 = 0;temp2 <len;temp2++){
				//std::cout<<"temp[0] = "<<temp[0]<<"\n";
				//std::cout<<"temp[temp2] = "<<temp[temp2]<<"\n";
				while (!temp.empty()){
					int temp7 = temp.back();
					temp.pop_back();
                    if (temp7 != iter+1)
					    addEdge(graph,iter,temp7-1);
				}
				
			//}
			iter++;
    	}//while
    	//myfile.close();
    } else {
    	std::cout<<"Unable to open File";
    }
    return graph;
}

int randomgen(int min, int max)
{
    return rand()%max + min ;
}

// Driver program to test above functions
int main()
{
    srand ( time(0) );
	int V = numNodes;
	struct Graph* graph;
	graph = createNewGraph();
    //std::sort(graph->array[0], graph->array + graph->V);
 	std::cout<<"printing original graph \n";
    // print the adjacency list representation of the above graph
    //printGraph(graph);
    int temp3 = 0;
    int maxcut = INT8_MAX;
    //for(temp3 = 0;temp3 < 2;temp3++)
    do
    {
    	graph = createNewGraph();
    	struct Graph* graph2 = createGraph(V);
    	if (debug){
            std::cout<<"temp3 = "<<temp3<<"\n";
            std::cout<<"Before Calling CombineGraph in main\n";
        }
        int randnode_initial = randomgen(0,graph->V);

        struct AdjListNode *pCrawl = graph->array[randnode_initial].head;
        //std::cout<<"pCrawl->dest = "<<pCrawl->dest<<"\n";
    	//printGraph(graph);
        if (pCrawl->dest > randnode_initial)
    	    graph2 = combinegraph(graph,randnode_initial,pCrawl->dest);
        else
            graph2 = combinegraph(graph,pCrawl->dest, randnode_initial);
        //std::cout<<"graph2->V : "<<graph2->V<<"\n";
        //graph2 = combinegraph(graph2,0,1);
     	//std::cout<<"graph2->V : "<<graph2->V;
        //printGraph(graph2);	
    	while (graph2->V > 2){
            int randnode = randomgen(0,graph2->V);
            //std::cout<<"randnode = "<<randnode<<"\n";
            struct AdjListNode *pCrawl12 = graph2->array[randnode].head;
    		//std::cout<<"graph2->V = "<<graph2->V<<"\n";
            //std::cout<<"pCrawl->dest = "<<pCrawl12->dest<<"\n";
            if (pCrawl12->dest == randnode)
                pCrawl12 = pCrawl12->next;
            if (randnode < pCrawl12->dest)
    		    graph2 = combinegraph(graph2,randnode,pCrawl12->dest);
            else 
                graph2 = combinegraph(graph2,pCrawl12->dest,randnode);

    		//printGraph(graph2);	
    	}
        if (debug){
            std::cout<<"graph2->V = "<<graph2->V<<"\n";
            printGraph(graph2);
        }
    	int temp4 = calcsize(graph2);
        if (temp4 < maxcut)
        	maxcut = temp4;
        temp3++; 
        //std::cout<<"temp4: "<<temp4<<"\n";   
        //graph = graph2;  
    } while (temp3 < 60);
    //printGraph(graph2);

    //calculate size
    // printGraph(graph2);
    std::cout<<"*****************\n";
    std::cout<<"maxcut = "<<maxcut<<"\n";
    std::cout<<"*****************\n";

    return 0;
}