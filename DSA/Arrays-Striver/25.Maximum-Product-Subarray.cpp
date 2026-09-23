#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// (i) Brute force------
// - Using three loops
// T.C -> O(N^3)
// S.C -> O(1)


// (ii) Better Soln------
// - Using two loops
// T.C -> O(N^2)
// S.C -> O(1)


// (iii) Optimal Soln------(Intuitive Approach)

// 1) All +ve -> return full array product
// 2) Even no. of -ve with some +ve -> return full array product
// 3) odd no. of -ve -> then max of all products of all elements except one negative element

// sp basically we have to check all prefix and suffix products and if element is '0' check for 0 also & then make it equal to '1'

int subarrayWithMaxProduct(vector<int> &arr){
	// Write your code here.
	int n = arr.size();

	int ans=INT_MIN;
	int prefProd=1;
	int suffProd=1;

	for(int i=0;i<n;i++){
		if(prefProd==0) prefProd=1;
		if(suffProd==0) suffProd=1;

		prefProd = prefProd*arr[i];
		suffProd = suffProd*arr[n-1-i];

		ans = max(ans, max(prefProd, suffProd));
	}

	return ans;
}
// T.C -> O(N)
// S.C -> O(1)



// (iii) Optimal Soln -2 ------(Kadanes Algorithm.....Not-Intuitive Approach)
int main(){
    return 0;
}