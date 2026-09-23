
#include<iostream>
#include <bits/stdc++.h> 
using namespace std;


//Through recursion-----------------
int f(int i, int j, vector<vector<int>> &grid){
    if(i==0 && j==0) return grid[0][0];
    
    if(i<0 || j<0) return INT_MAX;
    int up=INT_MAX;
    int left=INT_MAX;
    if(i>0) up = grid[i][j] + f(i-1, j, grid);
    if(j>0) left = grid[i][j] + f(i, j-1, grid);
    
    return min(up, left);
}
int minSumPath(vector<vector<int>> &grid) {
    // Write your code here.
    int n = grid.size();
    int m = grid[0].size();
    return f(n-1, m-1, grid);
}


//Through memoisation-----------------
#include <bits/stdc++.h> 
int f(int i, int j, vector<vector<int>> &grid, vector<vector<int>> dp){
    if(i==0 && j==0) return grid[0][0];
    
    if(i<0 || j<0) return INT_MAX;
    if(dp[i][j]!=-1) return dp[i][j];
    int up=INT_MAX;
    int left=INT_MAX;
    if(i>0) up = grid[i][j] + f(i-1, j, grid, dp);
    if(j>0) left = grid[i][j] + f(i, j-1, grid, dp);
    
    return dp[i][j] = min(up, left);
}
int minSumPath(vector<vector<int>> &grid) {
    // Write your code here.
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return f(n-1, m-1, grid, dp);
}


//Through tabulation-----------
int minSumPath(vector<vector<int>> &grid) {
    // Write your code here.
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> dp(n, vector<int>(m, 0));
//     return f(n-1, m-1, grid, dp);
    dp[0][0]=grid[0][0];
    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(i==0 && j==0) dp[0][0]=grid[0][0];
            else {
                int up=INT_MAX;
                int left=INT_MAX;
                if(i>0) up = grid[i][j] + dp[i-1][j];
                if(j>0) left = grid[i][j] + dp[i][j-1];

                dp[i][j] = min(up, left);
            }
            
        }
    }
    
    return dp[n-1][m-1];
}


//Through Space optimisation-------------
int minSumPath(vector<vector<int>> &grid) {
    // Write your code here.
    int n = grid.size();
    int m = grid[0].size();
//     vector<vector<int>> dp(n, vector<int>(m, 0));/
//     return f(n-1, m-1, grid, dp);
    
//     dp[0][0]=grid[0][0];
    vector<int> prev(m, 0);
    for(int i=0;i<n;i++){
        vector<int> curr(m, 0);
        for(int j=0;j<m;j++){
            if(i==0 && j==0) curr[0]=grid[0][0];
            else {
                int up=INT_MAX;
                int left=INT_MAX;
                if(i>0) up = grid[i][j] + prev[j];
                if(j>0) left = grid[i][j] + curr[j-1];

                curr[j] = min(up, left);
            }
            
        }
        prev = curr;
    }
    
    return prev[m-1];
}
