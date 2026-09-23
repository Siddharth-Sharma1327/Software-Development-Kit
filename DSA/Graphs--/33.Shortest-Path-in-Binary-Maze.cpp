#include<iostream>
#include<bits/stdc++.h>
using namespace std;


class Solution {
  public:
    int shortestPath(vector<vector<int>> &grid, pair<int, int> source, pair<int, int> destination) {
        // code here
        int n = grid.size();
        int m = grid[0].size();
        // vector<pair<int,int>> adj[n*m];
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        queue<pair<int,int>> q;
        q.push({source.first, source.second});
        dist[source.first][source.second]=0;
        
        while(!q.empty()){
            int row = q.front().first;
            int col = q.front().second;
            q.pop();
            
            int delrow[] {-1, 0, 1, 0};
            int delcol[] = {0, -1, 0, 1};
            
            for(int i=0;i<4;i++){
                int nrow = row + delrow[i];
                int ncol = col + delcol[i];
                
                if(nrow<n && nrow>=0 && ncol<m && ncol >=0 && grid[nrow][ncol]==1){
                    if(dist[row][col] +1< dist[nrow][ncol]){

                        if(nrow == destination.first && ncol == destination.second) return dist[row][col]+1;   //for this see below statements--

                        dist[nrow][ncol]= dist[row][col]+1;
                        q.push({nrow, ncol});
                    }
                }
            }
        }
        
        if(dist[destination.first][destination.second]==INT_MAX) return -1;
        else {
            int x = dist[destination.first][destination.second];
        return x;
        }
        
        
    }
};


// Below statements--
// we are moving outwards from the src in a circle(4 directions) and hence the first path always guarantee the shortest path. practice some questions on BFS algorithms to get a better understanding.
// That would be the case when you have different distance in each move, here in each move you move constant distance that is 1 , and when the distance is constant and you traverse through bfs , you will always reach every node the fastest and in minimum distance possible...
// ...so you don't require priority queue and return value as soon as you reach destination



// Better written code----
class Solution {
  public:
    int shortestPath(vector<vector<int>> &grid, pair<int, int> source,
                     pair<int, int> destination) {
        // code here
        int n = grid.size();
        int m = grid[0].size();
        
        if(source.first==destination.first && source.second==destination.second) return 0;
        
        vector<vector<int>> dist(n, vector<int>(m, -1));
        queue<pair<int,int>> q;
        q.push(source);
        dist[source.first][source.second]=0;
        
        while(!q.empty()){
            int row = q.front().first;
            int col = q.front().second;
            q.pop();
            
            int delrow[] = {-1, 0, 1, 0};
            int delcol[] = {0, 1, 0, -1};
            
            for(int i=0;i<4;i++){
                int adjRow = row + delrow[i];
                int adjCol = col + delcol[i];
                
                if(adjRow>=0 && adjRow<n && adjCol >=0 && adjCol<m && grid[adjRow][adjCol]==1){
                    if(dist[adjRow][adjCol]==-1 || dist[row][col]+1 < dist[adjRow][adjCol]){
                        if(adjRow==destination.first && adjCol==destination.second) return dist[row][col]+1;
                        dist[adjRow][adjCol] = dist[row][col]+1;
                        q.push({adjRow, adjCol});
                    }
                }
            }
        }
        
        return -1;
    }
};