#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include <stdlib.h>
#include <fstream>
#include <ctime>
#include <algorithm> 

#define numNodes 200

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
    // void dfs(struct Graph *graph, int *visited, vector<int>temp){
    // 	while (temp.size() != 0){
    // 	    int src = temp.back();
    // 	    temp.pop_back();
    // 	    struct AdjListNode *pCrawl = graph->array[src].head;
    // 	    while(pCrawl != NULL){
    // 	        if (!visited[pCrawl->dest]){
    // 		        temp.push_back(pCrawl->dest);
    // 		        visited[pCrawl->dest] = 1;
    // 	        }	
    // 	    pCrawl = pCrawl->next;
    //         }	
    // 	}
    	
    // }
	void dfs(struct Graph *graph, int src){
		vector<int> temp;
		int *visited = (int *)malloc(sizeof(int)*graph->V);
		for (int i=0;i<graph->V;i++){
			visited[i] = 0;
		}
		temp.push_back(src);
		visited[src] = 1;
		while (temp.size() > 0){
			int node = temp.back();
			temp.pop_back();
			cout<<(node + 1)<<endl;
			struct AdjListNode *pCrawl = graph->array[node].head;
			while (pCrawl != NULL){
				if (!visited[pCrawl->dest]){

					temp.push_back(pCrawl->dest);
					visited[pCrawl->dest] = 1;
				}
				pCrawl = pCrawl->next;
			}
		}

	}
    
    int* calc_min_weight(struct Graph *graph, int src, int dest){
    	
    	cout<<"calcmin: src = "<<src<<endl;
    	cout<<"calcmin: dest = "<<dest<<endl;
    	int *visited = (int *) malloc(sizeof(int)*graph->V);
    	vector<int> temp;
    	int i;
    	int flag = 0;
    	int minw_temp = 0;
    	int *minweight = (int *)malloc(sizeof(int)*graph->V);
    	for (i=0;i<graph->V;i++){
    		minweight[i] = 10000;
    	}
    	minweight[src] = 0;
    	for (i=0;i<graph->V;i++){
    		visited[i] = 0;
    	}
    	visited[src] = 1;
    	temp.push_back(src);

		while (temp.size() > 0){
			cout<<"calcmin: temp.size = "<<temp.size()<<"\n";
			int node = temp.back();
			temp.pop_back();
			cout<<"calcmin: node = "<<node<<endl;
			struct AdjListNode *pCrawl = graph->array[node].head;
			while (pCrawl != NULL){
				if (pCrawl->weight + minweight[node] < minweight[pCrawl->dest]){
					minweight[pCrawl->dest] = pCrawl->weight + minweight[node];
					visited[pCrawl->dest] = 0;
					temp.push_back(pCrawl->dest);
				} else {
					visited[pCrawl->dest] = 1;
				}

				// if (!visited[pCrawl->dest]){
				// 	cout<<"pCrawl->dest = "<<pCrawl->dest<<endl;
				// 	cout<<"calcmin: dest = "<<dest<<endl;
				// 	if (pCrawl->dest == dest){
				// 		if (flag == 0)
				// 		    minw_temp += pCrawl->weight;
				// 		cout<<"calcmin: dest reached, weight = "<<minw_temp<<"\n";
    //                     if (minw_temp < minweight)
    //                     	minweight = minw_temp;
				// 	}
				// 	else {
				// 		cout<<"calcmin pCrawl->dest = "<<pCrawl->dest<<" dest = "<<dest<<endl;
				// 		minw_temp +=  pCrawl->weight;
				// 		temp.push_back(pCrawl->dest);
				// 	    visited[pCrawl->dest] = 1;
				// 	    flag = 1;
				// 	} 

				// }
				pCrawl = pCrawl->next;
			} //pcrawl
		} //temp >0
		return minweight;
    }

    void pop_from(vector<int> &vminusx, int src){
    	int len = vminusx.size();
    	int i;
    	for (i=0;i<len;i++) {
    		if (vminusx[i] == src){
    			vminusx.erase(vminusx.begin() + i);
    			break;
    		}
    	}
    }
    int* dijkistra (struct Graph *graph, int src, int dest){
    	vector<int> x; //for storing the x part of dijkistra
    	vector<int> vminusx;
    	int *minw = (int *)malloc(sizeof(int)*graph->V);
    	/*
    	int *minweight = (int *)malloc(sizeof(int)*graph->V);

    	//assigning all weights to be 1000000
    	for (int i=0;i<graph->V;i++){
    		minweight[i] = 1000000;
    	}
    	*/
    	//minweight of the dest to be 1000000 intially
    	int minweight = 1000000;
    	//putting all values in vminusx initially
    	int i;
    	for (i=0;i<graph->V;i++){
    		vminusx.push_back(i); //i is analogous to all the nodes
    	}
    	//pop src from vminusx
    	pop_from(vminusx,src);
    	//adding src to x
    	x.push_back(src);
    	//calculating weights of dest
    	for (i=1;i<graph->V;i++){
    	    //minweight = calc_min_weight(graph, src, i);
    	    minw = calc_min_weight(graph, src, i);
    	    cout<<"dijkistra: minweight = "<<minweight<<endl;
    	    pop_from(vminusx,i);
    	    x.push_back(i);	
    	    //minw[i] = minweight;
    	}
    	
    	return minw;
    }
	struct Graph* createNewGraph(){
		int V = numNodes;
		struct Graph *graph = createGraph(V);
		//reading file
		int iter = 0;
		ifstream myfile("dijkistra_data.txt");
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
		//printGraph(graph);
		//dfs(graph,0);
		int *w = (int *)malloc(sizeof(int)*graph->V);
		w = dijkistra(graph, 0,1);
		for (int i=0;i<graph->V;i++){
			cout<<"Weights of "<<i<<" = "<<w[i]<<"\n";
		}

		return 0;
	}