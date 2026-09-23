#include<iostream>
#include<bits/stdc++.h>
using namespace std;


//-------------------------DFS APPROCH-----------------------------
class Solution {
    private:
    void dfs(int row, int col, vector<vector<int>> &ans, vector<vector<int>> &image, int newColor, int delrow[], int delcol[], int iniColor){
        ans[row][col]=newColor;        //color of current node is changed 
        int n = image.size();
        int m = image[0].size();

        for(int i=0;i<4;i++){
            int nrow = row + delrow[i];
            int ncol = col + delcol[i];

            if(nrow>=0 && nrow<n && ncol>=0 && ncol<m && image[nrow][ncol]==iniColor, ans[nrow][ncol]!=newColor){
                dfs(nrow, ncol, ans, image, newColor, delrow, delcol, iniColor);          //dfs for the neighbour of current node is called
            }
        }
    }
    public:
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor){
        int iniColor = image[sr][sc];
        vector<vector<int>> ans = image;         //new replica matrix of image for not altring the data

        int delrow[] = {-1, 0, +1, 0};
        int delcol[] = {0, +1, 0, -1};

        dfs(sr, sc, ans, image, newColor, delrow, delcol, iniColor);
        return ans;
    }
};



//-------------------------BFS APPROCH-----------------------------
class Solution {
private:
    void bfs(int sr, int sc, vector<vector<int>>& image, vector<vector<int>> &vis ,int newColor){
        
        int x = image[sr][sc];            //color of starting node
        if(x==newColor){                  // if start node color is same as that of the new color
            return;
        }
        
        vis[sr][sc]=1;                    //sn marked as visited
        queue<pair<int,int>> q; 
        q.push({sr, sc});                 //sn pushed into the queue
        image[sr][sc]=newColor;           //sn's color is changed
        int n = image.size();
        int m = image[0].size();
        
        while(!q.empty()){
            int row = q.front().first;     //location of the starting node is stored 
            int col = q.front().second;
            q.pop();                       //sn is poped
            
            
            int delrow[] = {-1, 0, 1, 0};     // IMP--TECHNIQUE for 4-Neighbours of the current node
            int delcol[] = {0, -1, 0, 1};
            
            
            for(int i=0;i<4;i++){              //neighbours of the starting node are iterated
                int nrow = row + delrow[i];
                int ncol = col + delcol[i];
                
                if(nrow<n && nrow>=0 && ncol>=0 && ncol<m && image[nrow][ncol]==x && !vis[nrow][ncol]){   //conditions
                    vis[nrow][ncol]=1;
                    image[nrow][ncol]=newColor;      //neighbour is marked visited and its color is changed and pushed into the queue
                    q.push({nrow, ncol});
                }
                
            }
        }
    }
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {   //image matrix with a group of single colors is given..have to convert them to new colr
        // Code here 
        
        int n = image.size();
        int m = image[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));                    //visted matrix
        bfs(sr, sc, image,vis, newColor);
        vector<vector<int>> ans = image;                                  //ans matrix
        return ans;
    }
};
//  here you can eliminate visited array and can also eliminate ans array but not good practice for ans array. 

// BFS APPROACH---------
// T.C -> O(NxM)x4
// S.C -> O(NxM)


// DFS APPROACH-----
//Time Complexity--> NxM=X: --> X + Xx4 (first X is of when dfs is called for all the nodes in floodFill function and other one is Xx4 is for the dfs is called for all the nodes)
                            //--> X=O(n^2)..approx.===> (O(1)+4)*(NxM)
// Space Complexity--> O(n^2)+O(n^2)...(first one due to ans matrix and second one due to worse case of the recursion stack)