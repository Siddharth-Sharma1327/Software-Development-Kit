#include<iostream>
#include<bits/stdc++.h>
using namespace std;




//through recursion-------
int mod = int(1e9+7);
int f(int i, int j, vector< vector< int> > &mat){
    
    if(i==0 && j==0) return 1;
    
    if(i<0 || j<0) return 0;
    
    int up=0;
    int left=0;
    if(mat[i][j]!=-1) up = f(i-1, j, mat);
    if(mat[i][j]!=-1) left = f(i, j-1, mat);
    
    return (up + left)%mod;
}

int mazeObstacles(int n, int m, vector< vector< int> > &mat) {
    // Write your code here
    return f(n-1, m-1, mat);
}

//Through memoisation----------
int mod = int(1e9+7);
int f(int i, int j, vector< vector< int> > &mat, vector<vector<int>> &dp){
    
    if(i==0 && j==0) return 1;
    
    if(i<0 || j<0) return 0;
    if(dp[i][j]!=-1) return dp[i][j];
    int up=0;
    int left=0;
    if(mat[i][j]!=-1) up = f(i-1, j, mat, dp);
    if(mat[i][j]!=-1) left = f(i, j-1, mat, dp);
    
    return dp[i][j] = (up + left)%mod;
}

int mazeObstacles(int n, int m, vector< vector< int> > &mat) {
    // Write your code here
    vector<vector<int>> dp(n, vector<int>(m,-1));
    return f(n-1, m-1, mat, dp);
}

//Through tabulation-------
int mod = int(1e9+7);
int mazeObstacles(int n, int m, vector< vector< int> > &mat) {
    // Write your code here
    vector<vector<int>> dp(n, vector<int>(m, 0));
    dp[0][0] =0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(i==0 && j==0) dp[i][j]=1;
            else {
                int up=0;
                int left=0;
                if(mat[i][j]!=-1 && i>0) up = dp[i-1][j];
                if(mat[i][j]!=-1 && j>0) left = dp[i][j-1];
                
                dp[i][j] = (up+left)%mod;
            }
        }
    }
    return dp[n-1][m-1];
//     return f(n-1, m-1, mat, dp);
    
    
}



//Through space optimisation---------
int mod = int(1e9+7);
int mazeObstacles(int n, int m, vector< vector< int> > &mat) {    
    vector<int> prev(m, 0);
    for(int i=0;i<n;i++){
        vector<int> curr(m, 0);
        for(int j=0;j<m;j++){
            
            if(i==0 && j==0) curr[j]=1;
            else {

                int up=0;
                int left=0;
                if(mat[i][j]!=-1){
                    up = prev[j];
                    left = curr[j-1];
                }
                curr[j] = (up + left)%mod;
            }
        }
        prev = curr;
    }
    
   return prev[m-1];
}

