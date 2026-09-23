#include<iostream>
#include<bits/stdc++.h>
using namespace std;


class Solution {
  private:
  bool detectbfs(int src, vector<int> adj[], int vis[]){
      vis[src]=1;
      queue<pair<int,int>> q;                  // queue of pair of current node and its parent node is pushed into the queue
      q.push({src, -1});                       // parent of the starting node of any component of the grapgh is set to -1
      
      while(!q.empty()){
          int node = q.front().first;            // current node
          int parent = q.front().second;         //parent of current  node
          q.pop();
          
          for(auto adjacentnode : adj[node]){      //adjacent nodes of the current node are iterated
              if(!vis[adjacentnode]){              //if adjacent node is not visted yet
                  vis[adjacentnode]=1;                                                                                                                                                   //  _2_3_4
                  q.push({adjacentnode, node});     //parent of adjacent node is current node                                                                                               |      \ 
              }else if(adjacentnode != parent){     //IMP--if the node is marked visited then there 2 cases                                                                                 1       8
                  return true;                      // (1) the node is parent node which was visited previously &                                                                           |      /
              }                                     // (2) the node is visited by the another node and not equal to the parent node and this happens means there is a cycle in the graph    |_5-6_7
          }                                         
      }
                                                                
      return false;                                         
  }
  public:
    // Function to detect cycle in an undirected graph.
    bool isCycle(int V, vector<int> adj[]) {                  //adjajency list is given
        // Code here
        int vis[V] ={0};
        for(int i=0;i<V;i++){                                // for loop is used since a graph cany have multiple components which may include cycle or not..if atlkeast one have cycle then whole grapgh is having cucle
            if(!vis[i]){
                if(detectbfs(i, adj, vis)) return true;      //for particular component if cycle is present then simply return true
            }
        }
        
        return false;                                        // if all the components are checked and if there is no cycle so return false as there is no cycle in graph
    } 
};

// Space complexity--> O(n)+O(n) (for the queue and visited array)
// Time Complexity--> O(n+2E) + O(n)  (here these two are not multiplied since the bfs is not called for every node so added...O(n)-for for loop and O(n+2E)-for the bfs(all nodes passed into the queue and each ones adjacent nodes are checked(=sumof(degrees))))