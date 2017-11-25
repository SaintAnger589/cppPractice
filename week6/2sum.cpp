#include <iostream>
#include <fstream>
#include<vector>

using namespace std;

#define nodes 1000000
#define nodes 8

void printarr(double arr[], int size){
	int len = size;
	int i;
	for (i=0;i<len;i++){
		cout<<arr[i]<<"\t";
	}
}

void merge(double arr[], int l, int m, int r){
	int i = 0;
	int j = 0;
	int p = l;

	int temp;
	int n1 = m - l + 1;
	int n2 = r - m;
	double *arr1 = (double *)malloc(sizeof(double)*n1);
	double *arr2 = (double *)malloc(sizeof(double)*n2);

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

void partition(double arr[], int l, int r){
	if (l < r){
		int m = l + (r-l)/2;
		//cout<<"m = "<<m<<endl;
		partition(arr, l, m);
		partition(arr, m + 1, r);
		merge(arr,l,m,r);
	}
	
}


int findtargetsum(double target, double initial, double arr[], int arr_size){
	//cout<<"initial = "<<initial<<endl;
	double num_to_find = target - initial;
	if (num_to_find == initial)
		return 0;
	//binary search to the sorted array
	int l = 0;
	int flag = 0;
	int r = arr_size;
	while (l < r){
		int m = (l + r)/2;
		if (arr[m] == num_to_find){
			flag = 1;
			break;
		}
		else if (arr[m] > num_to_find)
			r = m;
		else 
			l = m + 1;
	}

	if (flag==1){
		//cout<<"num_to_find = "<<num_to_find<<endl;
	    return 1;
	}
	else 
		return 0;
}
int main(){

	double *arr = (double *)malloc(sizeof(double)*nodes);
	double arrint;
	ifstream myfile;
	int k = 0;
	//myfile.open("week6data.txt");
	myfile.open("temp.txt");
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
	cout<<"arr_size = "<<arr_size<<endl;
	printarr(arr,arr_size);
	//sort the array by mergesort
	partition(arr,0,arr_size-1);
	//printitng the array
	//printarr(arr, arr_size);
	int i;
	double target = 10;
	int count = 0;
	for (i=0;i<arr_size/2;i++){
		count += findtargetsum(target, arr[i],arr, arr_size);
	}
	cout<<"count = "<<count<<endl;

}