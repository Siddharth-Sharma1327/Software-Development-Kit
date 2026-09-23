#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Second Largest/Smallest element in array-----------------------------------(OPTIMAL SOLUTION)

int sLargestElement(vector<int> &a, int n){
    int largest=a[0];
    int sLargest = INT_MIN;

    for(int i=0;i<n;i++){
        if(a[i] > largest){
            sLargest = largest;
            largest = a[i];
        }else if(a[i]<largest && a[i]>sLargest){
            sLargest = a[i];
        }
    }
    return sLargest;

}

int sSmallestElement(vector<int> &a, int n){
    int smallest=a[0];
    int sSmallest = INT_MAX;

    for(int i=0;i<n;i++){
        if(a[i] < smallest){
            sSmallest = smallest;
            smallest = a[i];
        }else if(a[i]!=smallest && a[i]<sSmallest){
            sSmallest = a[i];
        }
    }
    return sSmallest;

}
vector<int> getSecondOrderElements(int n, vector<int> a) {
    // Write your code here.
    vector<int> ans;
    int temp = sLargestElement(a, n);
    ans.push_back(temp);
    temp = sSmallestElement(a, n);
    ans.push_back(temp);
    return ans;
    
}

int main(){
    return 0;
}





// Remove duplicates in-place from array and find no. of unique elements-------------
int removeDuplicates(vector<int> &arr, int n) {
	// Write your code here.
	int i=0;
	for(int j=1;j<n;j++){
		if(arr[j]!=arr[i]){
			arr[i+1]=arr[j];
			i++;
		}
	}
	return i+1;
}








