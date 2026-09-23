#include<iostream>
#include<bits/stdc++.h>
using namespace std;


//Memoization-------


int path(vector<vector<int>> &matrix, int n, int m, int row, int col, vector<vector<int>> &dp){
    if(row==n-1) return matrix[row][col];
    if(dp[row][col]!=-1) return dp[row][col];
    int l=INT_MIN, d=INT_MIN, r=INT_MIN;
    if(col>=1) l=matrix[row][col]+path(matrix, n, m, row+1, col-1, dp);
    if(col<m-1) r=matrix[row][col]+path(matrix, n, m, row+1, col+1, dp);
    d = matrix[row][col]+path(matrix, n, m, row+1, col,dp);
    
    return dp[row][col] = max(l,max(d,r));
}
int getMaxPathSum(vector<vector<int>> &matrix)
{
    //  Write your code here.
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    int ans=INT_MIN;
    for(int j=0;j<m;j++){
        ans = max(ans, path(matrix, n, m, 0, j, dp));
    }
}


//Tabulation----
int getMaxPathSum(vector<vector<int>> &matrix)
{
    //  Write your code here.
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    
    for(int j=0;j<m;j++) dp[n-1][j]=matrix[n-1][j];
    for(int i=n-2;i>=0;i--){
        for(int j=m-1;j>=0;j--){
            int l=INT_MIN, d=INT_MIN, r=INT_MIN;
            if(j>=1) l=matrix[i][j]+dp[i+1][j-1];
            if(j<m-1) r=matrix[i][j]+dp[i+1][j+1];
            d = matrix[i][j]+dp[i+1][j];
            dp[i][j]=max(l,max(d,r));
        }
    }
    
    int ans=INT_MIN;
    for(int j=0;j<m;j++){
        ans=max(ans,dp[0][j]);
    }
    return ans;
}


//Space Optimisation----------
int getMaxPathSum(vector<vector<int>> &matrix)
{
    //  Write your code here.
    int n = matrix.size();
    int m = matrix[0].size();
//     vector<vector<int>> dp(n, vector<int>(m, -1));
    vector<int> front(m,0), curr(m, 0);
    for(int j=0;j<m;j++) front[j]=matrix[n-1][j];
    for(int i=n-2;i>=0;i--){
        for(int j=m-1;j>=0;j--){
            int l=INT_MIN, d=INT_MIN, r=INT_MIN;
            if(j>=1) l=matrix[i][j]+front[j-1];
            if(j<m-1) r=matrix[i][j]+front[j+1];
            d = matrix[i][j]+front[j];
            curr[j]=max(l,max(d,r));
        }
        front=curr;
    }
    
    int ans=INT_MIN;
    for(int j=0;j<m;j++){
        ans=max(ans,front[j]);
    }
    return ans;
}
int main(){
    return 0;
}