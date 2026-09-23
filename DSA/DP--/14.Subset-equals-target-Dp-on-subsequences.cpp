#include<iostream>
#include<bits/stdc++.h>

using namespace std;


//Through Recursion---
bool f(int ind, int target, vector<int> &arr){
    
    if(target==0) return true;
    if(ind==0) return (arr[0]==target);
    
    bool notTake = f(ind-1, target, arr);
    bool take = false;
    if(target>=arr[ind]) take=f(ind-1, target-arr[ind], arr);
    
    return take | notTake;
}
bool subsetSumToK(int n, int k, vector<int> &arr) {
    // Write your code here.
  return f(n-1, k, arr);
}


//Through Memoisation-----
bool f(int ind, int target, vector<int> &arr, vector<vector<int>> &dp){
    
    if(target==0) return true;
    if(ind==0) return (arr[0]==target);
    if(dp[ind][target]!=-1) return dp[ind][target];
    bool notTake = f(ind-1, target, arr, dp);
    bool take = false;
    if(target>=arr[ind]) take=f(ind-1, target-arr[ind], arr, dp);
    
    return dp[ind][target] = take | notTake;
}
bool subsetSumToK(int n, int k, vector<int> &arr) {
    // Write your code here.
    vector<vector<int>> dp(n, vector<int>(k+1, -1));
  return f(n-1, k, arr, dp);
}

//Through Tabulation----------
bool subsetSumToK(int n, int k, vector<int> &arr) {
    // Write your code here.
    vector<vector<bool>> dp(n, vector<bool>(k+1, 0));
    
    for(int i=0;i<n;i++) dp[i][0]=true;
    if(arr[0] < k+1) dp[0][arr[0]] = true;
    
    for(int ind=1;ind<n;ind++){
        for(int target=1;target<=k;target++){
            bool notTake = dp[ind-1][target];
            bool take = false;
            if(target>=arr[ind]) take=dp[ind-1][target-arr[ind]];

            dp[ind][target] = take | notTake;
            
        }
    }
    
    return dp[n-1][k];
}


//Through Space Optimisation----------
bool subsetSumToK(int n, int k, vector<int> &arr) {
    
    vector<bool> prev(k+1, 0), curr(k+1, 0);
    prev[0]= curr[0] = true;
    prev[arr[0]] = true;
    
    for(int ind=1;ind<n;ind++){
        for(int target=1;target<=k;target++){
            bool notTake = prev[target];
            bool take = false;
            if(target>=arr[ind]) take=prev[target-arr[ind]];

            curr[target] = take | notTake;
            
        }
        prev=curr;
    }
    
    return prev[k];
}
int main(){
    return 0;
}