#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Solution 
{
    private:
    int bfs(vector<vector<int>>& grid, vector<vector<int>> &vis, queue<pair<pair<int,int>,int>> &q){
        // int ans=0;
        int n = grid.size();
        int m = grid[0].size();
        int ans=INT_MIN;                              //ans of time is stored
        while(!q.empty()){
            int row = q.front().first.first;
            int col = q.front().first.second;
            int t = q.front().second;                //time of each orange pushed into the queue
            ans = max(ans, t);                       //maximum of all times is stored in the ans
            q.pop();
            
            int delrow[] = {-1, 0, 1, 0};
            int delcol[] = {0, -1, 0, 1};
        
            for(int i=0;i<4;i++){
                int nrow = row + delrow[i];
                int ncol = col + delcol[i];
                
                if(nrow>=0 && nrow<n && ncol<m && ncol>=0 && grid[nrow][ncol]!=2 && grid[nrow][ncol]!=0 && vis[nrow][ncol]!=2){
                    vis[nrow][ncol] = 2;         //marked visited 
                    int k=t+1;                   //every neighbour frsh orange is made rotten so time is increased by one and then pushed into the queue
                    q.push({{nrow, ncol}, k});
                    
                }
            }
            
        }
        return ans;                             //after all iterations we get the max time to rott all oranges
        
    }
    public:
    //Function to find minimum time required to rot all oranges. 
    int orangesRotting(vector<vector<int>>& grid) {
        // Code here
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));
        queue<pair<pair<int,int>,int>> q;                //queue of {{row, col}, time} is created 
        // int fans=INT_MIN;/
        // int ans=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]==2){
                  q.push({{i,j}, 0});                 //all the rotten oranges are first pushed into the queue and marked visited and intialised with time=0 for each
                  vis[i][j]==2;
                }
            }
        }
        int z = bfs(grid, vis, q);                    // bfs is called for the whole matrix
        // if(z==0){
        //     return -1;
        // }else {
        //     return z;
        // }
        
       for(int i=0;i<n;i++){                          //if all the fresh oranges are not rotten then -1(not possible)
            for(int j=0;j<m;j++){
                if(grid[i][j]==1 && vis[i][j]!=2){
                  return -1;
                }
            }
        }
        return z;                                     //else time to rott all oranges
        
    }
};


// Sapce Complexity--> NxM + NxM (for the queue + for the visited matrix)
// Time Complexity--> NxM + (NxM)x4 (for the for loop of grid matrix + no. of nodes in queueX4 each)









// Approach-2
class Solution {
public:
    
    int bfs(vector<vector<int>>& grid, vector<vector<int>> &vis, queue<pair<pair<int,int>,int>> &q, int &cnt){

        int n = grid.size();
        int m = grid[0].size();
        int ans=0;
        
        while(!q.empty()){
            int row = q.front().first.first;
            int col = q.front().first.second;
            int t = q.front().second;
            ans = max(ans, t);
            q.pop();
            
            int delrow[] = {-1, 0, 1, 0};
            int delcol[] = {0, -1, 0, 1};
        
            for(int i=0;i<4;i++){
                int nrow = row + delrow[i];
                int ncol = col + delcol[i];
                
                if(nrow>=0 && nrow<n && ncol<m && ncol>=0 && grid[nrow][ncol]==1 && vis[nrow][ncol]!=2){
                    cnt++;
                    vis[nrow][ncol] = 2;
                    int k=t+1;
                    q.push({{nrow, ncol}, k});
                    
                }
            }
            
        }
        return ans;
        
    }
    
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));
        queue<pair<pair<int,int>,int>> q;

        int cntFresh=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]==2){
                  q.push({{i,j}, 0});
                  vis[i][j]==2;
                }else if(grid[i][j]==1) cntFresh++;
            }
        }
        
        int cnt=0;
        int z = bfs(grid, vis, q, cnt);

        if(cnt==cntFresh) return z;
        else return -1;
    }
};
// T.C & S.C are same