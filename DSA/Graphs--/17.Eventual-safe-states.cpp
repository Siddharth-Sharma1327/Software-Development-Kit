#include<iostream>
#include<bits/stdc++.h>
using namespace std;


class Solution {
  private:
  bool dfs(int node, int vis[], vector<int> adj[], int pathvis[]){
    //   int vis[V]= {0};
      vis[node]=1;
      for(auto it: adj[node]){
          if(!vis[it]) {
              if(dfs(it, vis, adj, pathvis)==false){
                pathvis[it]=1;
                return false;
              }else {
                vis[it]=0;
              }
          }
          else {
              return false;
          }
      }
      
      return true;
      
  }
  public:
    vector<int> eventualSafeNodes(int V, vector<int> adj[]) {
        // code here
      int pathvis[V] = {0};
       vector<int> ans;
       
       for(int i=0;i<V;i++){
           if(!pathvis[i]){
                int vis[V]={0};
                if( dfs(i,vis, adj, pathvis) ){
                ans.push_back(i);
                }
           }
        //   int vis[V]={0};
        //   if( dfs(i,vis, adj, pathvis) ){
        //       ans.push_back(i);
        //   }
       }
       
       sort(ans.begin(), ans.end());
       return ans;
       
    }
    
};


