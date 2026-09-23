#include<iostream>
#include<bits/stdc++.h> 
using namespace std;


// Through Recursion------------

int f(int ind, vector<int> &heights){
    if(ind==0) return 0;
    int left = f(ind-1, heights) + abs(heights[ind]-heights[ind-1]);
    int right = INT_MAX;
    if(ind>1) right = f(ind-2, heights) + abs(heights[ind]-heights[ind-2]);
    return min(left, right);
}
int frogJump(int n, vector<int> &heights)
{    return f(n-1, heights);
    // Write your code here.
}


//Through Memoization-------------
#include <bits/stdc++.h> 
int f(int ind, vector<int> &heights, vector<int> &dp){
    if(ind==0) return 0;
    if(dp[ind]!=-1) return dp[ind];
    int left = f(ind-1, heights, dp) + abs(heights[ind]-heights[ind-1]);
    int right = INT_MAX;
    if(ind>1) right = f(ind-2, heights, dp) + abs(heights[ind]-heights[ind-2]);
    return dp[ind] = min(left, right);
}
int frogJump(int n, vector<int> &heights)
{   vector<int> dp(n+1, -1); 
    return f(n-1, heights, dp);
    // Write your code here.
}



//Through Tabulation----------------(stack space of recursion is reduced)
int frogJump(int n, vector<int> &heights)
{   vector<int> dp(n+1, 0); 
//     return f(n-1, heights, dp);
     dp[0]=0;
     for(int i=1;i<n;i++){
         int fs = dp[i-1] + abs(heights[i]-heights[i-1]);
         int ss = INT_MAX;
         if(i>1) ss = dp[i-2] + abs(heights[i]-heights[i-2]);
             dp[i] = min(fs, ss);
     }
     return dp[n-1];
    // Write your code here.
}



//Can we reduce Space??---------------("Yes always when we have dp[ind-1] and dp[ind-2] terms--")
int frogJump(int n, vector<int> &heights)
{   
    int prev = 0;
    int prev2 = 0;
     
     for(int i=1;i<n;i++){
         int fs = prev + abs(heights[i]-heights[i-1]);
         int ss = INT_MAX;
         if(i>1) ss = prev2 + abs(heights[i]-heights[i-2]);
             int curi = min(fs, ss);
         prev2 = prev;
         prev = curi;
     }
     return prev;
    // Write your code here.
}

// for(int i=1;i,n;i++){
//     int minstp=INT_MAX;
//     for(int j=i+K;j>=i+1;j--){
//         int xs = prev + abs(heights[i]-heights[j]);
//         minstp = min(minstp, xs);
//     }
    
// }