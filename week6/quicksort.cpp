#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

void swap(int a, int b){
	int temp;
	temp = a;
	a = b;
	b = temp;
}

int qsort(int *n, int low, int high, long *total_lenght){
	int i=low+1;
	int j;
	int temp;
	int len = high;

	*total_lenght = *total_lenght + (high - low);
	
	//computing median
	//////////////////////////////
     int mid = (((high - low))%2 == 0) ? low + ((high - low))/2: low + ((high - low))/2;
     //getting median
     int median = (n[low] > n[high]) ? max(n[high], min(n[low],n[mid])) :
                                  min(n[high], max(n[low],n[mid]));
     cout<<"len = "<<(high - low)<<"\n";
     cout<<"mid = "<<mid<<"\n";
     cout<<"m[mid] = "<<n[mid]<<"\n";
     cout<<"median = "<<median <<"\n";
     if (n[high] == median){
         temp = n[high];
         n[high] = n[low];
         n[low] = temp;	
     } else if (n[mid] == median){
     	temp = n[mid];
     	n[mid] = n[low];
     	n[low] = temp;
     }
     cout<<"n[high] = "<<n[high]<<"\n";
     cout<<"n[low] = "<<n[low]<<"\n";
     cout<<"n[mid] = "<<n[mid]<<"\n";
	/////////////////////////////
	
/*
	//swapping n[high] and n[low]
	/////////////////////////////
      temp = n[high];
      n[high] = n[low];
      n[low] = temp;
	////////////////////////////
*/
	for (j=low+1;j<=len;j++){
        if(n[j] < n[low]){
        	//swap(n[i],n[j]);
        	////////////////////
        	
	        temp = n[i];
	        n[i] = n[j];
	        n[j] = temp;
        	///////////////////
        	i++;
        }
	}
	//swapping pivot
	i = i-1;
	//cout<<"i = "<<i<<"\n";
	temp = n[low];
	n[low] = n[i];
	n[i] = temp;
	return i;
}

void partitioning(int *n, int low, int high, long *total_lenght){
	if (low<high){
		//cout<<"low = "<<low<<"\n";
		//cout<<"high = "<<high<<"\n";
	    int pivot = qsort(n,low,high, total_lenght);
	    
	    //cout<<"pivot = "<<pivot<<"\n";
	    partitioning(n, low, pivot - 1, total_lenght);
	    partitioning(n, pivot+1, high, total_lenght);	
	}
}
int main(){
	int i;
	
	long total_lenght = 0;
	
	//reading textfile
	////////////////////////////////
    int n[10000];
    int iter = 0;
    ifstream myfile("text.txt");
    if (myfile.is_open()){
    	while (myfile>>n[iter++]);
    	//myfile.close();
    } else {
    	cout<<"Unable to open File";
    }
	/////////////////////////////////
	
	//int n[8] = {8,2,4,5,7,1,9,6};
	int len = sizeof(n)/sizeof(n[0]);
	cout<<"length = "<<len<<"\n";
	partitioning(n,0,len-1, &total_lenght);
	//cout<<"\n";
	cout<<"total length = " << total_lenght<<"\n";
	return 0;
}