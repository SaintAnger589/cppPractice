#include <iostream>
#include <fstream>
#include <vector>

#define numNode 14

using namespace std;

struct AdjListNode {
	int dest;
	struct AdjListNode *next;
};

struct AdjNode {
	struct AdjListNode *head;
};

struct Graph {
	int V;
	struct AdjNode *array;
};

//function to create AdjListNode

struct AdjListNode *newAdjListNode (int dest){
	struct AdjListNode *newAdjListNode = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));
	newAdjListNode->dest = dest;
	newAdjListNode->next = NULL;
	return newAdjListNode;
}

//adding AdjNode to Graph
struct Graph* createGraph(int val){
	struct Graph *graph = (struct Graph*) malloc(sizeof(struct Graph));
	 graph->array = (struct AdjNode *) malloc(sizeof(struct AdjNode) * val);

	 int i;
	 for (i = 0;i<val;i++){
	 	graph->V = val;
	 	graph->array[i].head = NULL;
	 }
	 return graph;
}

//adding an edge
void addedge (struct Graph *graph, int src, int dest){
	struct AdjListNode *node = newAdjListNode(dest);
	node->next = graph->array[src].head;
	graph->array[src].head = node;
}

void printgraph(struct Graph *graph) {
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

void dfs(struct Graph *graph, int src, vector<int> &res, int *visited){
	if (!visited[src]){
		vector <int> temp;
		visited[src] = 1;
		int flag = 0;
		temp.push_back(src);
		while (temp.size() > 0){
			int node = temp.back();
			temp.pop_back();
			flag = 0;
			cout<<"val = "<<node<<endl;
			struct AdjListNode *pCrawl = graph->array[node].head;
			while (pCrawl){
				if (!visited[pCrawl->dest]){
					temp.push_back(pCrawl->dest);
					visited[pCrawl->dest] = 1;
					flag = 1;
				}
				pCrawl = pCrawl->next;
			}
			if (flag == 0){
				//cout<<"res = "<<node<<"\n";
				res.push_back(node);
		    } 
		}
	}
}
void printres(vector<int> res){
	int len = res.size();
	for (int i=0;i<len;i++){
		cout<<"res ["<<i<<"] = "<<res[i]<<endl;
	}
}

int dfscount(struct Graph *graph, int src, int *visited){
	int count = 0;
	if (!visited[src]){
		vector <int> temp;
		visited[src] = 1;
		temp.push_back(src);
		while (temp.size() > 0){
			int node = temp.back();
			temp.pop_back();
			cout<<"val = "<<node<<endl;
			struct AdjListNode *pCrawl = graph->array[node].head;
			while (pCrawl){
				if (!visited[pCrawl->dest]){
					temp.push_back(pCrawl->dest);
					visited[pCrawl->dest] = 1;
					count++;
				}
				pCrawl = pCrawl->next;
			} 
		}
	}
	return count;
}

void dfsfirstpass(struct Graph *graph, struct Graph *graphrev){
	vector<int> res;
	int *visited = (int *)malloc(sizeof(int)*graph->V);
	int i;
	cout<<"graph->v = "<<graph->V<<endl;
	for (i=0;i<graph->V;i++){
		visited[i] = 0;
	}
	for (i=0;i<graph->V;++i){
		dfs(graph, i, res, visited);
	}
	//printres(res);
	//now in reverse graph counting

	for (i=0;i<graph->V;i++){
		visited[i] = 0;
	}

	while (res.size() > 0){
		int sccnode = res.back();
		res.pop_back();
		int countscc = dfscount(graphrev, sccnode, visited);
		cout<<"count = "<<(countscc + 1)<<endl;
	}

}

int main(){
    ifstream myfile;
    myfile.open("temp.txt");
    int arrint;
    int len = 0;
    int i;
    int temp_var = 0;
    vector<int> temp;
    if (myfile.is_open()){
    	while (myfile>>arrint){
    		//cout<<"arrint"<<arrint<<"\n";
    		temp.push_back(arrint);
    		len++;
    	}

    }	else {
    	cout<<"Error opening file"<<"\n";
    }
    // creating new graph
    struct Graph *graph = createGraph(numNode);  
    while (temp.size() > 0){
    	int dest = temp.back();
    	//cout<<"dest = "<<dest<<endl;
    	temp.pop_back();
    	int src = temp.back();
    	//cout<<"src"<<src<<endl;
    	temp.pop_back();
    	addedge(graph, src-1, dest-1);
    }

    struct Graph *revGraph = createGraph(numNode);
    int iter1;
    for (iter1 = 0; iter1 < graph->V;++iter1){
    	struct AdjListNode *pCrawl = graph->array[iter1].head;
    	while (pCrawl){
    		addedge(revGraph,pCrawl->dest, iter1);
    		pCrawl = pCrawl->next;
    	}
    }
    cout<<"printing reverse graph"<<endl;
    printgraph(graph);

    //first pass
    vector<int> firstpassstk;
    dfsfirstpass(graph, revGraph);

    //printgraph(graph);
}