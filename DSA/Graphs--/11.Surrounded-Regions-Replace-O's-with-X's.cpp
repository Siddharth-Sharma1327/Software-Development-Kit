#include<iostream>
#include<bits/stdc++.h>
using namespace std;



class Solution{
private:
   void dfs(int row, int col,  vector<vector<int>> &vis, vector<vector<char>> &mat){
       vis[row][col]=1;        //marked visted
       int n = mat.size();
       int m = mat[0].size();
       
       int delrow[] = {-1, 0, 1, 0};
       int delcol[] = {0, -1, 0, 1};
       
       for(int i=0;i<4;i++){             //neighbours are iterated
           int nrow = row + delrow[i];
           int ncol = col + delcol[i];
           
           if(nrow>=0 && nrow<n && ncol>=0 && ncol<m && !vis[nrow][ncol] && mat[nrow][ncol]=='O'){
               dfs(nrow, ncol, vis, mat);           //dfs is called for further neighbour O's
           }
       }
   }
public:
    vector<vector<char>> fill(int n, int m, vector<vector<char>> mat){          //APPROACH--> First iterate first and last rows and columns and find O's connected with the boundary O's which cannot be replaced with X and mark them all visited. After that tarverse whole matrix and O's which are not marked visited replace them with X as they all will be surrounded by the X    
      vector<vector<int>> vis(n, vector<int>(m, 0));                         //visited matrix
      
      //traverse first row and last row;
      for(int j=0;j<m;j++){
          
          //first row
          if(!vis[0][j] && mat[0][j]=='O'){
              dfs(0, j, vis, mat);                //dfs called for the neighbour O's of the boundary O
          }
          
         //last row
         if(!vis[n-1][j] && mat[n-1][j]=='O'){
             dfs(n-1, j, vis, mat);
         }
      }
      
      //traverse first and last column;
      for(int i=0;i<n;i++){
          
          //first column;
          if(!vis[i][0] && mat[i][0]=='O'){
              dfs(i, 0, vis, mat);
          }
          
          //last column
          if(!vis[i][m-1] && mat[i][m-1]=='O'){
              dfs(i, m-1, vis, mat);
          }
      }
      
      for(int i=0;i<n;i++){                        //whole matrix is traversed and O's replaced with X
          for(int j=0;j<m;j++){
              if(!vis[i][j] && mat[i][j]=='O'){
                  vis[i][j]=1;
                  mat[i][j]='X';
              }
          }
      }
      
      return mat;                 //modofied mat is returned
    }
};

//Space Complexity--> O(nXm) + O(nXm) (visited matrix + recursion stack)
//Time Complexity--> O(nXm) + O(nXm)X4 + O(n) + O(m) (for loops and dfs worse case )