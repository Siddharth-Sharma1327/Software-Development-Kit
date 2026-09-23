#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    // Function to return a list containing the DFS traversal of the graph.
    
    void dfs(int node, vector<int> adj[], int vis[], vector<int> &ls){
        vis[node]=1;
        ls.push_back(node);
        
        //traverse all its nodes
        for(auto it : adj[node]){
            if(!vis[node]){
                dfs(node, adj, vis,ls);
            }
        }
    }
    vector<int> dfsOfGraph(int V, vector<int> adj[]) {
        // Code here
        int vis[V]={0};
        int start=0;
        vector<int> ls;
        dfs(start, adj, vis, ls);
        return ls;
    }
    
    
    //Space complexity is O(n)+O(n)+O(n)(this O(n is because of the worse case of the recursion stack space))--->i.e O(n)
    //Time Complexity is --
        /*  
        for one loop--> O(1)+O(degree of node)
        for n loops--> n*O(1)+O(d1+d2+d3...dn)
                   --> O(n)+O(2E)
                   --> O(n+2E)
                   -->O(n+E)
        
        
        */

    //    T.C -> O(n+E) ---for directed graph
};