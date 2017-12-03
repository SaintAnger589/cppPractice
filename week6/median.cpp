#include <iostream>
#include <fstream>
#include<vector>

using namespace std;
#define node 10000
void printarr(int arr[]){
	int i;
	for (i=0;i<node;i++){
		cout<<arr[i]<<endl;
	}
}

void merge(int arr[], int l, int m, int r){
	int i = 0;
	int j = 0;
	int p = l;

	int temp;
	int n1 = m - l + 1;
	int n2 = r - m;
	int *arr1 = (int *)malloc(sizeof(int)*n1);
	int *arr2 = (int *)malloc(sizeof(int)*n2);

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

void partition(int arr[], int l, int r){
	if (l < r){
		int m = l + (r-l)/2;
		//cout<<"m = "<<m<<endl;
		partition(arr, l, m);
		partition(arr, m + 1, r);
		merge(arr,l,m,r);
	}
	
}
int getmedian(int arr[], int l, int r){
	//cout<<"r = "<<r<<endl;
	if ((r-l)%2 == 0){
		return arr[r/2 - 1];
	} else {
		return arr[(r+1)/2 - 1];
	}
}

int main(){
	int iter;
	int *arr;
	arr = (int *)malloc(sizeof(int)*(node+1));
	ifstream myfile;
	int num;
	int count = 0;
	long long sum = 0;
	myfile.open("week6data2.txt");
	//myfile.open("temp.txt");
	int k = 0;
	if (myfile.is_open()){
		while (myfile>>num){
			arr[k++] = num;
			partition(arr,0,k-1);
			int median = getmedian(arr,0,k);
			//cout<<"median = "<<median<<endl;
			sum = sum + median;
			/*
			//cout<<num<<endl;
			if (count <= 5000){
				sum = sum + num;
				count++;
			}
			*/
		}
	} //if open
	else {
		cout<<"Error openeing files"<<endl;
	}
	printarr(arr);
	cout<<"sum = "<<sum<<endl;
}