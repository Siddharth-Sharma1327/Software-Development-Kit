#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Solution {                                  // shortest path of each node form the source node have to return
  public:
    vector<int> shortestPath(vector<vector<int>>& edges, int N,int M, int src){ //edges array,no. of nodes, no. of edges---given
        // code here
        vector<int> adj[N];              
        for(int i=0;i<M;i++){                            //creating adjancy list from the edges array for the undirected graph
           adj[edges[i][0]].push_back(edges[i][1]);  
           adj[edges[i][1]].push_back(edges[i][0]);
        }
        vector<int> prevsum(N, INT_MAX);      //prevsum is the array for each node to store the pathsum of its previous node
        vector<int> ans(N, INT_MAX);           //ans array
        int vis[N] = {0};                     //visited array
        prevsum[src]=0;                        //source is 0
        ans[src]=0;
        queue<int> q;
        q.push(src);           //pushed into the queue
        
        while(!q.empty()){
            int node = q.front();
            vis[node] = 1;                  //marked visited
            q.pop();
            
            for(auto it: adj[node]){                //adajacent nodes are iterated
                prevsum[it] = min(prevsum[it], prevsum[node]+1);      //prevsum of the current node is updated
                ans[it] = min(ans[it], prevsum[node]+1);              //ans of each node is updated in the ans array
                
                if(!vis[it]){           //pushed only when if not visited
                    q.push(it);
                }
            }
        }
        
        for(int i=0;i<N;i++){             //finally the nodes which were not visited(as different components of graph) are marked as -1 in ans array as per Q
            if(ans[i]==INT_MAX){
                ans[i]=-1;
            }
        }
        return ans;   //array of each node's shortest distnace from source node is returned
    }
};


// Better written code-----
class Solution {
  public:
    vector<int> shortestPath(vector<vector<int>>& edges, int N,int M, int src){
        // code here
        vector<int> adj[N];
        for(int i=0;i<M;i++){
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }
        
        vector<int> dist(N, -1);
        dist[src] = 0;
        queue<int> q;
        q.push(src);
        
        while(!q.empty()){
            int node = q.front();
            q.pop();
            
            for(auto it: adj[node]){
                
                if(dist[it]==-1 || dist[node]+1 < dist[it]){
                    dist[it]=dist[node]+1;
                    q.push(it);
                }
                
            }
        }
        
        return dist;
    }
};
// HERE ALL NO NODE IS PUSHED MORE THAN ONCE IN QUEUE SINCE EVERY NODE WITH DISTN IS STORED IN QUEUE IN SORTED(in terms of dist) ORDER ONLY 
// .....SO DATA STRUCTURE WITH SORTING THING IS NOT REQUIRED IF EDGE WEIGHT IS ONE IN FINDIND DISTANCE FROM SRC

// T.C -> O(N+M)
// S.C -> O(N*M) + O(N) +O(N)