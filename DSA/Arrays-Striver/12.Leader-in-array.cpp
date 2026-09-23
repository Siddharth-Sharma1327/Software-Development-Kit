#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// (i) Brute force--------
// Using two loops
// T.C -> O(N^2)
// S.C -> O(1)


// (ii) Optimised approach-----
vector<int> superiorElements(vector<int>&a) {
    // Write your code here.
    vector<int> ans;
    int n = a.size();
    int maxi=INT_MIN;
    for(int i=n-1;i>=0;i--){
        if(a[i]>maxi){
            ans.push_back(a[i]);
            maxi=a[i];
        }
    }
    return ans;
}
// Answer will be stored in sorted order only as we storing leaders from back of array---just think
// T.C -> O(N)
// S.C -> O(1)

int main(){
    return 0;
}