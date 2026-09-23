#include<iostream>
#include<bits/stdc++.h>
using namespace std;


class Solution {
  private:
    void dfs(int row, int col, vector<vector<int>> &vis, vector<vector<int>>& grid, vector<pair<int, int>> &vec, int row0, int col0){
        vis[row][col]=1;
        vec.push_back({row-row0, col-col0});
        int n = grid.size();
        int m = grid[0].size();
        
        int delrow[] = {-1, 0, 1, 0};
        int delcol[] = {0, -1, 0, 1};
        
        for(int i=0;i<4;i++){
            int nrow = row + delrow[i];
            int ncol = col + delcol[i];
            if(nrow>=0 && nrow<n && ncol>=0 && ncol<m && !vis[nrow][ncol] && grid[nrow][ncol]==1){
                dfs(nrow, ncol, vis, grid, vec, row0, col0);
                
            }
        }
                                                          //PROPERTY OF SETS--> It bydefault stores the distinct elments and don't stores the idenetical elements when we insert
    }
  public:
    int countDistinctIslands(vector<vector<int>>& grid) {   //given 1/0 matrix, we have to give no. of distinct islands(group of 1's) in different shapes
        // code here
        int n = grid.size();                                // Here basically for a particular group of 1's dfs is called and then we are storing the vector for each dfs/group in which the pair of current node's positions minus starting/base node's positions of the dfs are stored..and then this vector is returned to the set.
        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));      //visited matrix
        set<vector<pair<int,int>>> st;                      // set of vectors of pairs is defined
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(!vis[i][j] && grid[i][j]==1){
                    vector<pair<int, int>> vec;            //vector of pairs of subtraction of positions for each group of 1's
                    dfs(i, j,vis, grid, vec, i, j);        // second i,j are passed as the positions of the base node for each dfs call
                    st.insert(vec);                        // vector of each dfs is inserted in set..which checks for distinct before inserting
                }
            }
        }
        
        return st.size();                                  //finally the size of the set would be equal to the no. of distinct(in shape) group of 1's/islands
    }
};
//Space Complexity--> NxM + NxM (for visited matrix + for the set)
//Time Complexity--> NxMxlog(set.length()== nxm) + (NxM)X4
//                           |--> for the insert func() of set.