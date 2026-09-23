#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Brute Soln------
class Solution {
  public:
    int MinimumEffort(vector<vector<int>>& heights) {   //given a 2d matrix of size nxm each cell denoting the height of that cell..have to find the route with minimum effort from (0,0) cell to the (n-1,m-1) cell;
        // Code here
        int n = heights.size();
        int m = heights[0].size();
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));        //as like dijkstraa Algorithm distance matrix of each cell is stored
        dist[0][0]=0;         //distance of source is made 0;
        queue<pair<int,int>> q;        //queue of the locations is stored
        q.push({0,0});       //source is pushed
        
        while(!q.empty()){
            int row = q.front().first;       //location of the front of the queue is stored
            int col = q.front().second;
            // int dis = q.front().second;
            q.pop();
            
            int delrow[] = {-1, 0, 1, 0};
            int delcol[] = {0, -1, 0, 1};
            
            for(int i=0;i<4;i++){              //iterating the neighbours of the current node
                int nrow = row + delrow[i];
                int ncol = col + delcol[i];
                
                if(nrow>=0 && nrow<n && ncol>=0 && ncol<m){
                    int disx = max(dist[row][col], abs(heights[nrow][ncol]-heights[row][col]));     //maximum of the distance of parent node and the difference of the neighbour node cell and parent node cell, is found
                    if(disx<dist[nrow][ncol]){      //if max found is lesser than the already distance valued stored of the cell then it is updated
                        dist[nrow][ncol]=disx;
                        q.push({nrow, ncol});           //and pushed into the queue
                    } 
                }
            }
        }
        int z = dist[n-1][m-1];     //finally the distance with min. effort of the path from (0,0) to (n-1, m-1) is returned
        return z;
        
    }
};


// Optimised Soln---------
class Solution {
  public:
  #define pp pair<int,pair<int,int>> 
    int MinimumEffort(vector<vector<int>>& heights) {
        // Code here
        int n = heights.size();
        int m  = heights[0].size();
        
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        
        priority_queue<pp, vector<pp>, greater<pp>> pq;
        dist[0][0]=0;
        pq.push({0, {0, 0}});
        
        while(!pq.empty()){
            int maxi = pq.top().first;
            int row = pq.top().second.first;
            int col = pq.top().second.second;
            pq.pop();
            
            if(row==n-1 && col==m-1) return maxi;  //IMP--> Since we are doing level wise traversal and source is at start and destination is at end...all traversals reaching 
                                                        //  destination will get into pq at same level(i.e at same level all possible traversal till destination will be in priority queue) after this level there won't come any possible soln for dest node as this level was the last level
                                                        //  then priority queue will first take traversal with min dist value..so no need to check further
                                                        // levels are like diagonals starting from source node, then node its below, and so on (from left bottom -> right top) 

            int delrow[] = {-1, 0, 1, 0};
            int delcol[] = {0, 1, 0, -1};
            
            for(int i=0;i<4;i++){
                int nrow = row + delrow[i];
                int ncol = col + delcol[i];
                
                if(nrow>=0 && nrow<n && ncol>=0 && ncol<m){
                    int diff = max(maxi, abs(heights[row][col]-heights[nrow][ncol]));
                    if(diff < dist[nrow][ncol]){
                       dist[nrow][ncol]=diff;
                       pq.push({diff, {nrow, ncol}});
                    }
                } 
            }
        }
        
        return 0;  //if not possible
    }
};

// T.C -> O(ElogV)----Totale edges here are E = nXm X 4 & V = nXm---> so O(nxmlog(nxm))
// S.C -> O(nXm)



