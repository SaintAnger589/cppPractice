#include <iostream>
#include <fstream>
#include<vector>

using namespace std;

#define nodes 1000000
//#define nodes 8

void printarr(long long arr[], int size){
	int len = size;
	int i;
	for (i=0;i<len;i++){
		cout<<arr[i]<<"\t";
	}
}

void merge(long long arr[], int l, int m, int r){
	int i = 0;
	int j = 0;
	int p = l;

	int temp;
	int n1 = m - l + 1;
	int n2 = r - m;
	long long *arr1 = (long long *)malloc(sizeof(long long)*n1);
	long long *arr2 = (long long *)malloc(sizeof(long long)*n2);

	for (temp = 0;temp<n1;temp++){
		arr1[temp] = arr[temp + l];
		//printarr(arr1);
	}
	for (temp = 0;temp<n2;temp++){
		arr2[temp] = arr[temp + 1 + m];
		//printarr(arr2);
	}
	int *res;
		while (i < n1 && j < n2){
			if (arr1[i] <= arr2[j]){
				arr[p++] = arr1[i++];
			} //if (arr1[i] < arr2[j])
			else {
				arr[p++] = arr2[j++];
			}
		} 
		while (i<n1){
			arr[p++] = arr1[i++];
		}
		while (j<n2){
			arr[p++] = arr2[j++];
		}
	//return res;
}

void partition(long long arr[], int l, int r){
	if (l < r){
		int m = l + (r-l)/2;
		//cout<<"m = "<<m<<endl;
		partition(arr, l, m);
		partition(arr, m + 1, r);
		merge(arr,l,m,r);
	}
	
}


bool findtargetsum(long long target, long long initial, long long arr[], int arr_size, int visited[]){
	//cout<<"initial = "<<initial<<endl;
	long long num_to_find = target - initial;
	if (num_to_find == initial)
		return false;
	//binary search to the sorted array
	int l = 0;
	int flag = 0;
	int r = arr_size;
	while (l < r){
		int m = (l + r)/2;
		if (arr[m] == num_to_find && visited[m] == 0){
			flag = 1;
			visited[m] = 1;
			//visited[initial] = 1;
			break;
		}
		else if (arr[m] > num_to_find)
			r = m;
		else 
			l = m + 1;
	}

	if (flag==1){
		//cout<<"num_to_find = "<<num_to_find<<endl;
		//cout<<"target = "<<target<<"\n"; 
	    return true;
	}
	else 
		return false;
}

int removeDuplicates(long long A[], int n) {
    if(n < 2) return n;
    int id = 1;
    for(int i = 1; i < n; ++i) 
        if(A[i] != A[i-1]) A[id++] = A[i];
    return id;
}

void resetvisited(int visited[], int arr_size){
	for (int iter = 0;iter<arr_size;iter++){
		visited[iter] = 0;
	}
}

int main(){

	long long *arr = (long long *)malloc(sizeof(long long)*nodes);
	int *visited = (int *)malloc(sizeof(int)*nodes);
	for (int iter = 0;iter<nodes;iter++){
		visited[iter] = 0;
	}
	long long arrint;
	ifstream myfile;
	int k = 0;
	myfile.open("week6data.txt");
	//myfile.open("temp.txt");
	if (myfile.is_open()){
		while (myfile >> arrint){
			//cout<<arrint<<endl;
			arr[k] = arrint;
			//cout<<"arr[k]= "<<arr[k]<<endl;
			//cout<<"k = "<<k<<"\n";
			k++;
		}
	}else {
		cout<<"Unable to open file";
	}

	int *t;
	int arr_size = k;
	//cout<<"arr_size = "<<arr_size<<endl;
	//printarr(arr,arr_size);
	//sort the array by mergesort
	partition(arr,0,arr_size-1);
	//printitng the array
	//printarr(arr, arr_size);

	//remove duplicates
	arr_size = removeDuplicates(arr,arr_size);
	//printarr(arr,arr_size);
	int i;
	long long target = -10000;
	//long long target = 10;
	int count = 0;
	int flag_found = 0;
	for (int j = 0;j<=20000;j++){
	//for (int j = 0;j<=2;j++){
		long long target1 = target + j;
		flag_found = 0;
		resetvisited(visited,arr_size);
		for (i=0;i<arr_size;i++){
		//i = arr_size-1;
			if (flag_found == 1)
				break;
			// for (int j = i+1; j<arr_size;j++){
			// 	if ((arr[i] + arr[j]) >=-10000 && (arr[i] + arr[j]) <= 10000){
			// 	    //if (arr[i])
			// 	    count++;
			// 	    //cout<<count<<endl;
			//     }
			// }
			//visited[i] = 1;
			
		    if (findtargetsum(target1, arr[i],arr, arr_size, visited)){
		    // if (count > 
		    //     cout<<"count = "<<count<<endl;
		    	flag_found = 1;
		    	count++;
	        }
	    } 
    }
	cout<<"count = "<<count<<endl;

}