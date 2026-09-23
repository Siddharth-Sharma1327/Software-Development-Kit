#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Solution {                         //shortest distance between 1 node and last node 'n'
  public:
    vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) {  //vector of nodes and their edge weights is given
        // Code here
        vector<pair<int,int>> adj[n+1];           //adjancy list of 1 based indexing is created
        for(int i=0;i<m;i++){
            adj[edges[i][0]].push_back({edges[i][1], edges[i][2]});
            adj[edges[i][1]].push_back({edges[i][0], edges[i][2]});
        }
        
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;    //priority queue of pairs is created
        vector<int> dist(n+1, INT_MAX), parent(n+1);    //distnace array of 1 based indexing of nodes
        for(int i=0;i<n;i++) parent[i]=i;            //IMP--i indexing based Parent array is created with its values equal to the indexes
        dist[1]=0;
        pq.push({0, 1});         //1 with distance 0 is pushed into the queue
        
        while(!pq.empty()){                  //same as dijkstras algorithm
            auto it = pq.top();
            int node = it.second;
            int dis = it.first;
            pq.pop();
            
            for(auto it: adj[node]){
                int adjNode = it.first;
                int edgeW = it.second;
                
                if(dis + edgeW < dist[adjNode]){
                    dist[adjNode] = dis + edgeW;
                    pq.push({dist[adjNode], adjNode});
                    parent[adjNode]=node;                 //here the parent of the current node is stored
                }
                
            }
        }
        
        if(dist[n]==INT_MAX) return {-1};    //if the last node wasn't visited return -1

                            //IMP---Trick to store the sequence of the path--------------------------------------

        vector<int> path;                   //path vector is created for storing the path
        int node = n;          //node = last node value 
        //----O(n)
        while(parent[node]!=node){          //parent of each node is saved into the path vector
            path.push_back(node);
            node = parent[node]; 
        }
        path.push_back(1);                //finally the starting node is pushed into the vector
        reverse(path.begin(), path.end());     //vcetor is reversed for correct sequence
        return path;                       //path array (sequence of the shortest path of the last node from the first node'1' is returned)
    }
};