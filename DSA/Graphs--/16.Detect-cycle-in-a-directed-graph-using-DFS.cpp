#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Solution {
  private: 
    bool dfsCheck(int node, vector<int> adj[], int vis[], int pathVis[]){
        vis[node]=1;                             //node is marked visted
        pathVis[node]=1;                         // node is also marked visted in the path for which dfs has been called
        
        //traverse for the adjacent nodes
        for(auto it: adj[node]){ 
            
            //when the node is not visited
            if(!vis[it]){                        //if the node not visited before
                if(dfsCheck(it, adj, vis, pathVis)==true)        //dfs is called for the adjacent node
                return true;                           // return true for this path if any dfs is returned true
            }
            
            //if the node has been previously visited
            //but it has to be visited on the same path
            else if(pathVis[it]){                         //here we don't consider the parent node as in directed graph it is absent in the adjancy list of its adjacent node
                return true;                     //if both are 1 i.e visted and pathVisited for the current node
            }
        }
        
        pathVis[node]=0;                     // if no cycle for the particular node then omit the pathVis of that node again to '0' so that can consider it in another path 
        return false;                        // return false if there is no cycle
    }                                         
                                               //APPROACH--> Here for the cycle to be there the node has to be visted before "and in the same path"
  public:                                     // For the tracking the path we have created and pathVis array..for a particular path we mark them with 1's and omit them again with 0's if we don't get true for cycle in recursion untill we get different path 
    // Function to detect cycle in a directed graph.
    bool isCyclic(int V, vector<int> adj[]) {                //we have to detect for a cycle in a directed graph
        // code here
        int vis[V] = {0};                     // visited array
        int pathVis[V] = {0};                 // path visted array-->basically keeps the count of all nodes in a partricular path
        
        for(int i=0; i<V;i++){                //for different compoenents of the graph
            if(!vis[i]){                      // not visited 
                if(dfsCheck(i, adj, vis, pathVis)==true) return true;      //if dfs called for the particular path finds true means there is a cycle
            }
        }
        
        return false;                    // if all the paths don't return true means no cycle so return false
    }
};

// Space Complexity--> O(V) + O(V) (for the vis and pathVis arrays)
// Time Complexity--> O(V) + O(V+E) (for for loop and since directed graph..no. of edges is E so O(V+E) for dfs)




//----------------Using single array for less sapce complexity-------------------

class Solution {
  private: 
    bool dfsCheck(int node, vector<int> adj[], int vis[]){
        vis[node]=1;
        // pathVis[node]=1;
        
        //traverse for the adjacent nodes
        for(auto it: adj[node]){
            
            //when the node is not visited
            if(vis[it]==0){
                if(dfsCheck(it, adj, vis)==true)
                return true;
            }
            
            //if the node has been previously visited
            //but it has to be visited on the same path
            else if(vis[it]==1){
                return true;
            }
            // else if(vis[it]==2){
            //     return false;
            // }
        }
        
        vis[node]=2;
        return false;
    }
  public:                                                    // here i've considered--> '0' for not visited
    // Function to detect cycle in a directed graph.         //                     --> '1' for visited
    bool isCyclic(int V, vector<int> adj[]) {                //                     --> '2' for visited but didn't get a cycle
        // code here
        int vis[V] = {0};
        // int pathVis[V] = {0};
        
        for(int i=0; i<V;i++){
            if(vis[i]==0){
                if(dfsCheck(i, adj, vis)==true) return true;
            }
        }
        
        return false;
    }
};
