#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include <stdlib.h>
#include <fstream>
#include <ctime>
#include <algorithm> 

#define numNodes 8

using namespace std;

	struct AdjListNode{
		int dest;
		int weight;
		struct AdjListNode *next;
	};

	struct AdjList{
		struct AdjListNode *head;
	};

	struct Graph{
		int V;
		struct AdjList *array;
	};

	struct AdjListNode* newListNode(int dest, int weight){
		struct AdjListNode *newNode = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
		newNode->weight = weight;
		newNode->dest = dest;
		return newNode;
	}

	struct Graph* createGraph(int val){
		struct Graph *graph = (struct Graph*)malloc(sizeof(struct Graph));
		graph->V = val;
		graph->array = (struct AdjList*)malloc(sizeof(struct AdjList) * val);
		int i;
		for (i=0;i<val;i++){
			graph->array[i].head = NULL;
	    }
	    return graph;
    }

    void addEdge (struct Graph *graph, int src, int dest, int weight){
    	struct AdjListNode *newNode= newListNode(dest, weight);
    	newNode->next = graph->array[src].head;
    	graph->array[src].head = newNode; 
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
	            printf("-> %d\t", pCrawl->dest);
	            printf("weight-> %d\n", pCrawl->weight);
	            pCrawl = pCrawl->next;
	        }
	        printf("\n");
	    }
	}

	struct Graph* createNewGraph(){
		int V = numNodes;
		struct Graph *graph = createGraph(V);
		//reading file
		int iter = 0;
		ifstream myfile("temp.txt");
		string s;
		int n;
		int count_num = 2;
		if (myfile.is_open()){
			while(getline(myfile,s)){
				count_num = 2;
				std::vector<int> temp;
				std::stringstream stream(s);
				cout<<"stream"<<s<<"\n";
				char c;
				int len_string = s.size();

				while (count_num < len_string){
					n = s[count_num] - '0';
					cout<<"n = "<<n<<"\n";
					temp.push_back(n);
					n = s[count_num+2] - '0';
					cout<<"weight = "<<n<<"\n";
					temp.push_back(n);
					count_num = count_num + 4;
				}
				/*
				while (stream >> n){
					cout<<"edge"<<n<<"\n";
					//count_num = count_num + 2;
					//temp.push_back(n);
					//if (!stream)
					//	break;

				} //while (stream >> n)
				*/
			int len = temp.size();
			//std::cout<<"len = "<<len<<"\n";
			int temp2;
			//for (temp2 = 0;temp2 <len;temp2++){
				//std::cout<<"temp[0] = "<<temp[0]<<"\n";
				//std::cout<<"temp[temp2] = "<<temp[temp2]<<"\n";
				while (!temp.empty()){
					int temp_weight = temp.back();
					cout<<"temp_weight = "<<temp_weight<<"\t";
					temp.pop_back();
					int temp7 = temp.back();
					cout<<"temp7 = "<<temp7<<"\n";
					temp.pop_back();
                    //if (temp7 != iter+1)
					    addEdge(graph,iter,temp7-1,temp_weight);
				}
				iter++;
			} //while
		} //if(myfile)
		else{
			cout<<"Unable to open File";
		}
	return graph;
	}
	int main(){
		int V = numNodes;
	    struct Graph* graph;
		graph = createNewGraph();
		printGraph(graph);
		return 0;
	}