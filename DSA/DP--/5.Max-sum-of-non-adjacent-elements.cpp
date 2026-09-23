#include<iostream>
#include<bits/stdc++.h>
using namespace std;

//Through Recursion---------------
int f(int ind, vector<int> &nums){
    if(ind==0) return nums[ind];
    if(ind<0) return 0;
    
    int pick = nums[ind] + f(ind-2, nums);
    int notPick = 0 + f(ind-1, nums);
    
    return max(pick, notPick);
}
int maximumNonAdjacentSum(vector<int> &nums){
    // Write your code here.
    int n = nums.size();
    return f(n-1, nums);
}
// T.C = 2^N
// S.C = O(N) a.s.s


//Through Memoisation-------------
#include <bits/stdc++.h> 
int f(int ind, vector<int> &nums, vector<int> &dp){
    if(ind==0) return nums[ind];
    if(ind<0) return 0;
    if(dp[ind]!=-1) return dp[ind];
    int pick = nums[ind] + f(ind-2, nums, dp);
    int notPick = 0 + f(ind-1, nums, dp);
    
    return dp[ind] = max(pick, notPick);
}
int maximumNonAdjacentSum(vector<int> &nums){
    // Write your code here.
    int n = nums.size();
    vector<int> dp(n, -1);
    return f(n-1, nums, dp);
}

// T.C = O(N)*2
// S.C = O(N) + O(N) a.s.s


//Through Tabulation-----------------
int maximumNonAdjacentSum(vector<int> &nums){
    // Write your code here.
    int n = nums.size();
    vector<int> dp(n, -1);
    dp[0]=nums[0];
    for(int i=1;i<n;i++){
        
        int take = nums[i];
        if(i>1) take+=dp[i-2];
        
        int nontake = 0 + dp[i-1];
        dp[i] = max(take, nontake);
    }
    
    return dp[n-1];
}
// TC = O(N)
// S.C = O(N)


//Through Sapce Optimisation-------------
int maximumNonAdjacentSum(vector<int> &nums){
    // Write your code here.
    int n = nums.size();
    
    int prev = nums[0];
    int prev2 = 0;
    for(int i=1;i<n;i++){
        
        int take = nums[i];
        if(i>1) take+=prev2; 
        
        int nontake = 0 + prev;
        int curri = max(take, nontake);
        prev2 = prev;
        prev=curri;
    }
    
    return prev;
}
// TC = O(N)
// S.C = O(1)