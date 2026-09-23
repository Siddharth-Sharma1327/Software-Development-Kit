#include<iostream>
#include<bits/stdc++.h>
using namespace std;


                                          //------SAME Q. AS SURROUNDED-REGIONS-REPLACE-O's-WITH-X'S----------------
class Solution {
  private: 
    void dfs(int row, int col, vector<vector<int>> &vis, vector<vector<int>> &grid){
        vis[row][col]=1;
        int  n = grid.size();
        int m = grid[0].size();
        
        int delrow[] = {-1, 0, 1, 0};
        int delcol[] = {0, -1, 0, 1};
        
        for(int i=0;i<4;i++){
            int nrow = row + delrow[i];
            int ncol = col + delcol[i];
            
            if(nrow>=0 && nrow<n && ncol<m && ncol>=0 && !vis[nrow][ncol] && grid[nrow][ncol]==1){
                dfs(nrow, ncol, vis, grid);
            }
        }
        
    }
  public:
    int numberOfEnclaves(vector<vector<int>> &grid) {
        // Code here
        int x=0;
        int  n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));
        
        for(int j=0;j<m;j++){
            
            if(!vis[0][j] && grid[0][j]==1){
                dfs(0, j, vis, grid);
            }
            
            if(!vis[n-1][j] && grid[n-1][j]==1){
                dfs(n-1, j, vis, grid);
            }
        }
        
        for(int i=0;i<n;i++){
            
            if(!vis[i][0] && grid[i][0]==1){
                dfs(i, 0, vis, grid);
            }
            
            if(!vis[i][m-1] && grid[i][m-1]==1){
                dfs(i, m-1, vis, grid);
            }
        }
        
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(!vis[i][j] && grid[i][j]==1){
                    x++;
                }
            }
        }
        
        return x;
    }
};




// My Leetcode Approach-------
class Solution {
public:
    
    bool isValid(int adjr, int adjc, int n, int m){
        return (adjr>=0 && adjr<n && adjc>=0 && adjc<m);
    }
    
    int numEnclaves(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));
        int ans=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(!vis[i][j] && grid[i][j]==1){
                    bool flag=0;
                    int cnt=0;
                    queue<pair<int,int>> q;
                    q.push({i, j});
                    vis[i][j]=1;
                    while(!q.empty()){
                        int row = q.front().first;
                        int col = q.front().second;
                        q.pop();
                        
                        cnt++;
                        if(row==n-1 || row==0 || col==m-1 || col==0){
                            flag=1;
                        }
                        
                        int delrow[] = {-1, 0, 1, 0};
                        int delcol[] = {0, 1, 0, -1};
                        
                        for(int k=0;k<4;k++){
                           int adjr = row + delrow[k];
                            int adjc = col + delcol[k];
                            
                            if(isValid(adjr, adjc, n, m)){
                                if(grid[adjr][adjc]==1 && !vis[adjr][adjc]){
                                    vis[adjr][adjc]=1;
                                    q.push({adjr, adjc});
                                    
                                }
                            }
                        }
                        
                    }
                    
                    if(!flag){
                        // cout<<i<<" "<<j<<" "<<cnt<<endl;
                        ans+=cnt;
                    } 
                }
            }
        }
        
        return ans;
        
    }
};