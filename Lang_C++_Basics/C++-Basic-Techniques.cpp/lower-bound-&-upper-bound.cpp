#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Lower bound points to ---- arr[ind] >= x
// if elment is notv present then returns the element just greater that 'x' if such elment is possible in array or hypothetical pointer pointing to nth position
int lowerBound(vector<int> arr, int n, int x) {
	// Write your code here
	int low=0;
	int high = n-1;
	int ans=n;
	while(low<=high){
		int mid = low + (high-low)/2;

		if(arr[mid]>=x){
			ans=mid;
			high=mid-1;
		}else{
			low=mid+1;
		}
	}

	return ans;
}


// Upper bound points to ---- arr[ind] > x
// if elment is notv present then returns the element just greater that 'x' if such elment is possible in array or hypothetical pointer pointing to nth position
int upperBound(vector<int> &arr, int x, int n){
	// Write your code here.	
	int low=0;
	int high = n-1;
	int ans=n;
	while(low<=high){
		int mid = low + (high-low)/2;

		if(arr[mid]>x){
			ans=mid;
			high=mid-1;
		}else{
			low=mid+1;
		}
	}

	return ans;
}




// T.C -> O(logn)
int main(){
    return 0;
}