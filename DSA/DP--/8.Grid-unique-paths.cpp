#include<iostream>
#include<bits/stdc++.h>
using namespace std;


//Through Recursion---------
int f(int i, int j){
    
    if(i==0 && j==0) return 1;
    
    if(i<0 || j<0) return 0;
    
    int up = f(i-1,j);
    int left = f(i,j-1);
    
    return up+left;
}
int uniquePaths(int m, int n) {
	// Write your code here.
    return f(m-1, n-1);
}
// T.C = 2^(m*n) 
// S.C = O(m+n)

//Through memoisation--------
int f(int i, int j, vector<vector<int>> &dp){
    
    if(i==0 && j==0) return 1;
    
    if(i<0 || j<0) return 0;
    if(dp[i][j]!=-1) return dp[i][j];
    int up = f(i-1,j, dp);
    int left = f(i,j-1, dp);
    
    return dp[i][j]=up+left;
}
int uniquePaths(int m, int n) {
	// Write your code here.
    vector<vector<int>> dp(m, vector<int>(n, -1));
    return f(m-1, n-1, dp);
}
// T.C = O(m*n) 
// S.C = O(m+n) + O(m*n)

//Through tabulation--------
int uniquePaths(int m, int n) {
	// Write your code here.
//     vector<vector<int>> dp(m, vector<int>(n, -1));
//     return f(m-1, n-1, dp);
    int dp[m][n];
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(i==0 && j==0) dp[i][j]=1;
            else{
                int up=0;
                int left=0;
                if(i>0) up = dp[i-1][j];
                if(j>0) left = dp[i][j-1];
                dp[i][j] = up+left;
            }
        }
    }
    return dp[m-1][n-1];
    
}
// T.C = O(m*n)
// S.C = O(m*n)


//Through space optimisation---------
int uniquePaths(int m, int n) {
	// Write your code here.
//     vector<vector<int>> dp(m, vector<int>(n, -1));
//     return f(m-1, n-1, dp);
    vector<int> prev(n, 0);
    for(int i=0;i<m;i++){
        vector<int> curr(n, 0);
        for(int j=0;j<n;j++){
            if(i==0 && j==0) curr[j]=1;
            else{
                int up=0;
                int left=0;
                if(i>0) up = prev[j];
                if(j>0) left = curr[j-1];
                curr[j] = up+left;
            }
        }
        prev=curr;
    }
    return prev[n-1];
    
}
// T.C = O(m*n) 
// S.C = O(n)