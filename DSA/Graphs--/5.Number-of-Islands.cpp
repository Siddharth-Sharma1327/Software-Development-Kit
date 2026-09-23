#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Solution {
  private:
  void bfs(int row, int col, vector<vector<int>> &vis, vector<vector<char>> &grid){
      vis[row][col]=1;

      queue<pair<int,int>> q;                                     // queue for storing the locations of the visited nodes in the group
      q.push({row, col});

      int n = grid.size();
      int m = grid[0].size();

      while(!q.empty()){
          int row = q.front().first;                        // row and col of the inserted element are saved 
          int col = q.front().second;
          q.pop();                                          //elment is poped
          
          //traverse in the neighbours and mark them if its a land
          for(int delrow=-1;delrow<=1;delrow++){               //--------------->>>>IMP TECHNIQUE FOR TRAVERSING THE NEIGHBOURS
              for(int delcol=-1;delcol<=1;delcol++){           //neighbbours of the current node are visited 
                  int nrow = row + delrow;                     
                  int ncol = col + delcol;                     //row and col of the current neighbour of the element is stored 
                  if(nrow>=0 && nrow<n && ncol<m && ncol>=0 && grid[nrow][ncol]=='1' && !vis[nrow][ncol]){      //conditions are checked
                      vis[nrow][ncol]=1;
                      q.push({nrow, ncol});                    //marked visited and its location is pushed into the queue so that further its neighbours can be visited
                  }
              }
          }
      }
  }
  public:
    // Function to find the number of islands.
    int numIslands(vector<vector<char>>& grid) {           //here the matrix of 0's and 1's is given which denotes the islands in water..every group of 1's is considered an island and every group is taken as a connected nodes and each group is traversed using BFS/DFS..and computed the no. of such groups(i.e no. of islands  )
        // Code here
        int n = grid.size();                              //size of the matrix are cal.
        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m,0));     //2-d visited array is created for marking the positions visited in the matrix
        int cnt=0;                                        // no. of islands
        for(int row=0;row<n;row++){                       //now whole matrix is tarversed and the starting nodes of each group of 1's or ISLAND is found and the bfs on that node is called for marking its neighbours
            for(int col=0;col<m;col++){
                if(!vis[row][col] && grid[row][col]=='1'){
                    cnt++;                                  
                    bfs(row, col, vis, grid);             //bfs is called for the starting node 
                }
            }
        }
        return cnt;                                      // no. of islands
    }

    // Space Complexity: O(n^2)(of visited matrix..hereb we can also use the given matrix for visted markings but then also space would be O(n^2))+O(n^2)(worse case of queue)
    // Time Complexity: O(n^2)+O(n^2)x9--->first O(n^2) -----for the dual for loop in the main function and other one for the bfs function as O(n^2) for while loop and its further 9 operations 
    //                      ^-- here both are not multiplied as bfs is not called for every node
    
//  lets 'li' be the size of queue every time the bfs is called
    // O(N^2)X9 = 9(l1) + 9(l2) + 9(l3) +...+ 9(lz)
    //                                  ------------->(l1+l2+l3+...lz) = size of grid i.e N^2
};