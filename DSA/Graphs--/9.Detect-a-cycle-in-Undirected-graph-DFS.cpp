#include<iostream>
#include<bits/stdc++.h>
using namespace std;


class Solution {
  private:
  bool detectdfs(int node, int parent, vector<int> adj[], int vis[] ){
      vis[node]=1;
      
      for(auto adjacentnode : adj[node]){                           //adjacent nodes of the current node are iterated
          if(!vis[adjacentnode]){
              vis[adjacentnode]=1;
              if(detectdfs(adjacentnode, node, adj, vis)==true)     //if dfs called for the adjacent node of the current node return true the return true
                return true;
          }else if(adjacentnode!=parent){                         //if adjacent node was visited and not equal to parent node means a cycle return true
              return true;
          }
      }
      
      return false;                                               // if all the adjacent nodes of current node don't return true--no cycle return false for the current component of the graph
  }
  public:
    // Function to detect cycle in an undirected graph.
    bool isCycle(int V, vector<int> adj[]) {
        // Code here
        int vis[V] ={0};
        for(int i=0;i<V;i++){                         //for the components of graph
            if(!vis[i]){
                if(detectdfs(i,-1, adj, vis)) return true;         //dfs is called for the starting node of the component with parent -1..if returns true means a cycle so return true
            }
        }
        
        return false;                            //if all the components are acyclic so return false
    }
};

// Space complexity--> O(n) + O(n)  (for the recursion stack space and the visted array)
// Time complexity--> O(n) + O(n+2E) (for the for loop and since dfs for every node is not called so added and equal to the O(n)+sumof(degrees=2E))