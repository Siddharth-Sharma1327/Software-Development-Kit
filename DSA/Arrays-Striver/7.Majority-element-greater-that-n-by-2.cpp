#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// (i) Brute force-------
int majorityElement(vector<int> v) {
	// Write your code here
	int n = v.size();
	for(int i=0;i<n;i++){
		int cnt=0;
		for(int j=i;j<n;j++){
			if(v[i]==v[j]) cnt++;
		}
		if(cnt> n/2) return v[i];
	}
	
}
// T.C -> O(N^2)
// S.C -> O(1)

// (ii) Better Soln--------
int majorityElement(vector<int> v) {
	// Write your code here
	int n = v.size();
	map<int,int> mp;
	for(int i=0;i<n;i++){
		mp[v[i]]++;
	}
	for(auto it: mp){
		if(it.second > n/2) return it.first;
	}
	
}
// T.C -> O(NlogN)
// S.C -> O(N)


// (iii) Optimal Soln---------(MOORE'S VOTING ALGORITHM)
int majorityElement(vector<int> v) {
	// Write your code here
	int n = v.size();
	int cnt=0;
	int ele;

	for(int i=0;i<n;i++){
		if(cnt==0){
			ele=v[i];
			cnt=1;
		}else if(v[i]==ele){
			cnt++;
		}else{
			cnt--;
		}
	}

	int cnt1=0;
	for(int i=0;i<n;i++){
		if(v[i]==ele) cnt1++;
	}
	if(cnt1>n/2) return ele;
}
// T.C -> O(N)
// S.C -> O(1)

int main(){
    return 0;
}