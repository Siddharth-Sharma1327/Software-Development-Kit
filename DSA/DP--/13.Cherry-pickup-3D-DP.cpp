#include<iostream>
#include<bits/stdc++.h>
using namespace std;


//Recursion---------
#include <bits/stdc++.h> 
int path(int r, int c, vector<vector<int>> &grid, int r1, int c1, int c2){
//     if(r1==r2 && c1==c2) return grid[r1][c1];
    if(c1<0 || c2<0 || c1>=c || c2>=c) return 0;
    if((r1==r-1) && c1==c2) return grid[r1][c1];
    else if(r1==r-1) return grid[r1][c1]+grid[r1][c2];
    
    int maxi=INT_MIN;
    for(int i=-1;i<2;i++){
        for(int j=-1;j<2;j++){
            if(c1==c2){
                maxi=max(maxi, grid[r1][c1]+path(r,c,grid,r1+1,c1+i,c2+j));
            }else {
                maxi=max(maxi, grid[r1][c1]+grid[r1][c2]+path(r,c,grid,r1+1,c1+i,c2+j));
            }
            
        }
    }
    return maxi;
    
}
int maximumChocolates(int r, int c, vector<vector<int>> &grid) {
    // Write your code here.
    return path(r, c, grid, 0, 0, c-1);
}




//Memoization-----------------
#include <bits/stdc++.h> 
int path(int r, int c, vector<vector<int>> &grid, int r1, int c1, int c2, vector<vector<vector<int>>> &dp){
//     if(r1==r2 && c1==c2) return grid[r1][c1];
    if(c1<0 || c2<0 || c1>=c || c2>=c) return 0;
    
    if((r1==r-1) && c1==c2) return grid[r1][c1];
    else if(r1==r-1) return grid[r1][c1]+grid[r1][c2];
    
    
    if(dp[r1][c1][c2]!=-1) return dp[r1][c1][c2];
    int maxi=INT_MIN;
    for(int i=-1;i<2;i++){
        for(int j=-1;j<2;j++){
            if(c1==c2){
                maxi=max(maxi, grid[r1][c1]+path(r,c,grid,r1+1,c1+i,c2+j,dp));
            }else {
                maxi=max(maxi, grid[r1][c1]+grid[r1][c2]+path(r,c,grid,r1+1,c1+i,c2+j,dp));
            }
            
        }
    }
    return dp[r1][c1][c2]= maxi;
    
}
int maximumChocolates(int r, int c, vector<vector<int>> &grid) {
    // Write your code here.
    vector<vector<vector<int>>> dp(r, vector<vector<int>>(c, vector<int>(c, -1)));
    return path(r, c, grid, 0, 0, c-1, dp);
}









// Memoisation-----------------
class Solution {
public:
    int maxChocolatesHelper(int pos1, int pos2, int i, int n, int m, vector<vector<int>> &g,  vector<vector<vector<int>>> &dp){
        if(i >= n) return 0;
        
        if(dp[i][pos1][pos2] != -1) return dp[i][pos1][pos2];
        int sum = 0, curSum = g[i][pos1];
        if(pos1 != pos2) curSum += + g[i][pos2];

        for(int k=-1; k<=1; k++){
            for(int x=-1; x<=1; x++){
                if(pos1+k >=0 && pos1+k < m && pos2+x >= 0 && pos2+x < m){
                    sum = max(sum, curSum + maxChocolatesHelper(pos1+k, pos2+x, i+1, n, m, g, dp));
                } 
            }
        }

        return dp[i][pos1][pos2] = sum;

    }
    int cherryPickup(vector<vector<int>>& g) {
        int n = g.size();
        int m = g[0].size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, -1)));
        return maxChocolatesHelper(0, m-1, 0, n, m, g, dp);
    }
};
// T.C  = O(n*m*m)*9 & S.C = O(n*m*m) + O(n) (Recursion Stack Space)


//Tabulation-----------------
class Solution {
public:
    int cherryPickup(vector<vector<int>>& g) {
        int n = g.size();
        int m = g[0].size();
        vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(m, vector<int>(m, 0)));

        for(int i=n-1; i>=0; i--){
            for(int pos1=m-1; pos1>=0; pos1--){
                for(int pos2=m-1; pos2>=0; pos2--){
                    int sum = 0, curSum = g[i][pos1];
                    if(pos1 != pos2) curSum += + g[i][pos2];

                    for(int k=-1; k<=1; k++){
                        for(int x=-1; x<=1; x++){
                            if(pos1+k >=0 && pos1+k < m && pos2+x >= 0 && pos2+x < m){
                                sum = max(sum, curSum + dp[i+1][pos1+k][pos2+x]);
                            } 
                        }
                    }
                    dp[i][pos1][pos2] = sum;
                }
            }
        }

        return dp[0][0][m-1];
    }
};
// T.C  = O(n*m*m)*9 & S.C = O(n*m*m)


// Space Optimization-----------------
class Solution {
public:
    int cherryPickup(vector<vector<int>>& g) {
        int n = g.size();
        int m = g[0].size();
        vector<vector<int>> prev(m, vector<int>(m, 0));

        for(int i=n-1; i>=0; i--){
            vector<vector<int>> cur(m, vector<int>(m, 0));
            for(int pos1=m-1; pos1>=0; pos1--){
                for(int pos2=m-1; pos2>=0; pos2--){
                    int sum = 0, curSum = g[i][pos1];
                    if(pos1 != pos2) curSum += + g[i][pos2];

                    for(int k=-1; k<=1; k++){
                        for(int x=-1; x<=1; x++){
                            if(pos1+k >=0 && pos1+k < m && pos2+x >= 0 && pos2+x < m){
                                sum = max(sum, curSum + prev[pos1+k][pos2+x]);
                            } 
                        }
                    }
                    cur[pos1][pos2] = sum;
                }
            }
            prev = cur;
        }

        return prev[0][m-1];
    }
};
// T.C  = O(n*m*m)*9 & S.C = O(m*m)


//
int main(){
    return 0;
}