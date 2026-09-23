#include<iostream>
#include<bits/stdc++.h>
using namespace std;


//Q1
// Find the missing number-----------
// (i) Brute force----------loops
int missingNumber(vector<int>&a, int N) {
    // Write your code here.

    int n = N-1;
    for(int i=1;i<=N;i++){
        bool flag=0;
        for(int j=0;j<n;j++){
            if(a[j]==i){
                flag=1;
            }
        }
        if(flag==0) return i;
    }
    
}
// T.C -> O(N^2)
// S.C -> O(1)



// (ii) Better Soln-------hashing
// can use sorting for 'nlogn' solution-O(nlogn)

//O(N)
int missingNumber(vector<int>&a, int N) {
    // Write your code here.

    int n = N-1;
    vector<int> v(N+1, 0);

    for(int i=0;i<n;i++){
        v[a[i]]++;
    }
    for(int i=1;i<=N;i++){
        if(v[i]==0) return i;
    }
    
}
// T.C -> O(N)
// S.C -> O(N)



// (iii) Optimal Soln--------Pref Sum
int missingNumber(vector<int>&a, int N) {
    // Write your code here.

    int n = N-1;
    int totSum=N*(N+1)/2;

    int sum=0;
    for(int i=0;i<n;i++){
        sum+=a[i];
    }
    
    return totSum-sum;
    
}
// T.C -> O(N)
// S.C -> O(1) ------ HERE CHANCE OF OVERFLOW FOR LARGER VALUES OF 'totSum' so not most optimal one


//(iv) Most Optimal Solution----------- XOR -> (Theory:- 0^0=0 , 0^x = x, x^x = 0)
int missingNumber(vector<int>&a, int N) {
    // Write your code here.

    int n = N-1;
    int xor1=0, xor2=0;

    for(int i=0;i<n;i++){
        xor2 = xor2^a[i];
        xor1 = xor1^(i+1);
    }
    xor1 = xor1^N;

    return xor1^xor2;
    
}

// T.C -> O(N)
// S.C -> O(1)----------- BETTER THAN PREVIOUS ONE AS NO OVERFLOW & XOR LARGE NUMBERS WON;T AS LARGE AS THEIR SUM SO LESS SPACE IS USED




// Q2
// Maximum number of consecutive ones----------
// Normal solution strainght forward
int consecutiveOnes(vector<int>& arr){
    //Write your code here.
    int cnt=0;
    int n = arr.size();
    int ans=0;

    for(int i=0;i<n;i++){
        if(arr[i]==1){
            cnt++;
            ans=max(ans, cnt);
        }else{
            cnt=0;
        }
    }
    return ans;
}
// T.C -> O(n)
// S.C -> O(1)

int main(){
    return 0;
}




// Q3
// Find the number that appears once, and the other numbers twice  (i) UnSorted array (ii) Sorted array
// (i) Brute force---------
#include<vector>

int getSingleElement(vector<int> &arr){
	// Write your code here.
	int n = arr.size();
	for(int i=0;i<n;i++){
		int cnt=0;
		for(int j=0;j<n;j++){
			if(arr[i]==arr[j]) cnt++;
		}
		if(cnt==1) return arr[i];
	}	
}
// T.C -> O(n^2)
// S.C -> O(1)


// (ii) Better Solution---------- Hashing
#include<vector>
#include<bits/stdc++.h>

int getSingleElement(vector<int> &arr){
	// Write your code here.
	int n = arr.size();
	map<int,int> mp;

	for(int i=0;i<n;i++){
		mp[arr[i]]++;
	}	

	for(auto it: mp){
		if(it.second==1) return it.first;
	}
}
// T.C -> O(NlogM){map, M-size of map} or O(N*N){unordered map worst case}
// S.C -> O(n)

// (iii) Optimal Solution------------- XOR

int getSingleElement(vector<int> &arr){
	// Write your code here.
	int n = arr.size();
	int xor1=0;
	for(int i=0;i<n;i++){
		xor1 = xor1^arr[i];
	}

	return xor1;
}
// T.C -> O(N)
// S.C -> O(1)



// (iV) Most Optimal Solution-----------Binary Search only if array is sorted

int getSingleElement(vector<int> &arr){
	// Write your code here.
	int n = arr.size();
	int s=0;
	int e=n-1;

	while(s<=e){
		int mid = s + (e-s)/2;

		if(mid==0){
			if(arr[mid]!=arr[mid+1]) return arr[mid];
			else{
				//No such case
			}
		}else if(mid==n-1){
			if(arr[mid]!=arr[mid-1]) return arr[mid];
			else{
				//No such case
			}
		}else if(arr[mid]!=arr[mid-1] && arr[mid]!=arr[mid+1]){
			return arr[mid];
		}else if(arr[mid]==arr[mid-1]){
			if((mid-s+1)%2!=0){
				e=mid;
			}else if((e-mid)%2!=0){
				s=mid+1;
			}
		}else if(arr[mid]==arr[mid+1]){
			if((e-mid+1)%2!=0){
				s=mid;
			}else if((mid-s)%2!=0){
				e=mid-1;
			}
		}
	}
}

// T.C -> O(logN)    ----only when array is sorted o/w previous is optimal
// S.C -> O(1)





