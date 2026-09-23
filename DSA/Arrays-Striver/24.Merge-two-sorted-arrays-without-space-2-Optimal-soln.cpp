#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// (i) Brute force-------
void mergeTwoSortedArraysWithoutExtraSpace(vector<long long> &a, vector<long long> &b){
	// Write your code here.
	int n = a.size();
	int m = b.size();
	vector<long long> v;

	for(int i=0;i<n;i++){
		v.push_back(a[i]);
	}
	for(int i=0;i<m;i++){
		v.push_back(b[i]);
	}

	sort(v.begin(), v.end());
	int i;
	for(i=0;i<n;i++){
		a[i]=v[i];
	}
	for(i=n;i<n+m;i++){
		b[i-n] = v[i];
	}
	return ;
}
// T.C -> O(n+m)
// S.C -> O(n+m)







// (ii) 1st optimal soln------(Two Pointers--)
void mergeTwoSortedArraysWithoutExtraSpace(vector<long long> &a, vector<long long> &b){
	// Write your code here.
	int n = a.size();
	int m = b.size();
	int i = n-1;
	int j = 0;

	while(i>=0 && j<m){
		if(a[i]>b[j]){
			swap(a[i], b[j]);
			i--;
			j++;
		}else{
			break;
		}
	}
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	return;
}
// T.C -> O(nLogn + mLogm)
// S.C -> O(1)







// (ii) 2nd optimal soln------
void swapIfGreater(int left, int right, long long tempArray1[], long long tempArray2[]){
	//left pointer is always in tempArray1
	//right pointer is always in tempArray2

	if(tempArray2[right] < tempArray1[left]){
		swap(tempArray1[left], tempArray2[right]);
	}
	return;
}

class Solution{
    public:
        //Function to merge the arrays.
        void merge(long long arr1[], long long arr2[], int n, int m) 
        { 
            // code here 
            int len = (n+m);
        	//int gap = ceil(len/2);
        	int gap = (len/2) + (len%2);
        
        	while(gap > 0){
        		int left = 0;
        		int right = left + gap;
        
        		while(right < len){
        
        			// left in 'arr1' and right in 'arr2'
        			if(left<n && right>=n){
        				swapIfGreater(left, right-n, arr1, arr2);
        			}
        			// left and right both are in 'arr2'
        			else if(left>=n){
        				swapIfGreater(left-n, right-n, arr2, arr2);
        			}
        			// left and right both are in 'arr1'
        			else{
        				swapIfGreater(left, right, arr1, arr1);
        			}
        
        			left++;
        			right++;
        		}
        
        		if(gap==1) break;
        		gap = (gap/2) + gap%2; 
        		// gap = ceil(gap/2);
        	}
        } 
};
/// check notes for detailed explaination-----------
// T.C -> O(Log(n+m))*O(n+m)---------------log(n+m)=levels as len/2 everytime
// S.C -> O(1)










int main(){
    return 0;
}