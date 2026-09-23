#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Solution {
  private:
    void dfs(int node, vector<int> adjl[], int vis[]){
        vis[node]=1;
        for(auto it: adjl[node]){
            if(!vis[it]){
                dfs(it, adjl, vis);
            }
        }
    }
  public:
    int numProvinces(vector<vector<int>> adj, int V) {
        // code here
        vector<int> adjl[V];
                                                                //here first the given adjacency matrix is used to create adjacency list
        //to change the adjacency matrix to adjency list
        for(int i=0;i<V;i++){
            for(int j=0;j<V;j++){
                if(adj[i][j]==1){
                    adjl[i].push_back(j);
                    adjl[j].push_back(i);
                }
            }
        }
        
        int vis[V]={0};
        int cnt=0;
        for(int i=0;i<V;i++){                    //for loop is used for the different provinces(components of graph)
            if(!vis[i]){
                cnt++;                           // cnt is the no. of provinces as it woulb be equal to the no. of times it comes inside the if condition
                dfs(i, adjl, vis);               //dfs is called for traversing the single province and marking them visited using recursion
            }
        }
        
        return cnt;
    }
};


// T.C -> O(N) + O(V+2E)....(n nodes & dfs is not called for all nodes inside for loop--->so overall it is O(V+2E))
// S.C -> O(N) + O(N)...excluding adjacency list and of visited array & recursion stack space;