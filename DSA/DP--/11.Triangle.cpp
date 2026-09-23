#include<iostream>
#include<bits/stdc++.h>

using namespace std;

//Recursion
//T.C --> 2^(1+2+3..n) & S.C--->O(N)

//Memoization---------------
//T.C --> O(NxN) & S.C--->O(NxN)+O(N)(RECURSION STACK SPACE)
#include <bits/stdc++.h> 

int path(vector<vector<int>>& triangle, int n, int m, int i, int j, vector<vector<int>> &dp){
    if(i==n-1) return triangle[i][j];
    if(dp[i][j]!=-1) return dp[i][j];
    int d = triangle[i][j]+path(triangle, n, m, i+1, j, dp);
    int r = triangle[i][j]+path(triangle, n, m, i+1, j+1, dp);
    return dp[i][j] = min(d,r);
}
int minimumPathSum(vector<vector<int>>& triangle, int n){
	// Write your code here.
//     int n = nums.size();
    int m = triangle[n-1].size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return path(triangle, n, m,0,0, dp);
}


//Tabulation------------                                  Catch is that if memoization is top-down then tabulation will be bottom-up and if memoization is bottom-up then tabulation is top-down 
//T.C --> O(NxN) & S.C--->O(NxN)
int minimumPathSum(vector<vector<int>>& triangle, int n){
	// Write your code here.
//     int n = nums.size();
    int m = triangle[n-1].size();
    vector<vector<int>> dp(n, vector<int>(m, 0));
//     return path(triangle, n, m,0,0, dp);
//     int j=0;
    for(int j=0;j<n;j++) dp[n-1][j]=triangle[n-1][j];
    for(int i=n-2;i>=0;i--){
        for(int j=i+1;j>=0;j--){
            int d = triangle[i][j]+dp[i+1][j];
            int r = triangle[i][j]+dp[i+1][j+1];
            dp[i][j]=min(d,r);
        }
    }
    return dp[0][0];
}


//Sapce Optimisation-----------
//T.C --> O(NxN) & S.C--->O(N)
int minimumPathSum(vector<vector<int>>& triangle, int n){
    int m = triangle[n-1].size();
    vector<int> front(n, 0), curr(n, 0);                   //Concept of taking two rows front and curr instead of whole nxn matrix
    for(int j=0;j<n;j++) front[j]=triangle[n-1][j];

    for(int i=n-2;i>=0;i--){
        for(int j=i+1;j>=0;j--){
            int d = triangle[i][j]+front[j];
            int r = triangle[i][j]+front[j+1];
            curr[j]=min(d,r);
        }
        front=curr;
    }
    return front[0];
}
int main(){
    return 0;
}
