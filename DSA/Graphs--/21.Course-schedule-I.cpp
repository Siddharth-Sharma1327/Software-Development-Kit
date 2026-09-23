#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// DFS Approach----1 (leetcode)
class Solution {
public:
    
    
    bool dfs(int node, int n, vector<int> adj[], vector<int> &vis, vector<int> &pathVis){
        vis[node]=1;
        pathVis[node]=1;
        
        for(auto it: adj[node]){
            
            if(!vis[it]){
                if(dfs(it, n, adj, vis, pathVis)){
                    return true;
                }
            }else if(pathVis[it]){
               return true; 
            } 
        }
        
        pathVis[node]=0;
        return false;
    }
    
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> adj[numCourses];
        for(int i=0;i<prerequisites.size();i++){
            adj[prerequisites[i][1]].push_back(prerequisites[i][0]);
        }
        
        vector<int> vis(numCourses, 0);
        vector<int> pathVis(numCourses, 0);
        
        for(int i=0;i<numCourses;i++){ 
            if(!vis[i]){
                if(dfs(i, numCourses, adj, vis, pathVis)){
                return false;
                }
            }   
        }
        
        return true;
    }
};




// BFS Approach----2 (GFG)
class Solution
{
  public:
    vector<int> findOrder(int n, int m, vector<vector<int>> prerequisites) 
    {
        //code here
        int p = prerequisites.size();
	    vector<int> adj[n];
	    
	    for(int i=0;i<p;i++){
	        adj[prerequisites[i][1]].push_back(prerequisites[i][0]);
	    }
	   
	   int indegree[n]={0};
	   for(int i=0;i<p;i++){
	       indegree[prerequisites[i][0]]++;
	   }
	   
	   queue<int> q;
	   for(int i=0;i<n;i++){
	       if(indegree[i]==0){
	           q.push(i);
	       }
	   }
	   
	   int cnt=0;
	   vector<int> topo;
	   while(!q.empty()){
	       int node = q.front();
	       q.pop();
	       topo.push_back(node);
	       cnt++;
	       
	       for(auto it:adj[node]){
	           indegree[it]--;
	           
	           if(indegree[it]==0){
	               q.push(it);
	           }
	       }
	   }
	   
	   if(cnt==n){
	       return topo;
	   }else {
	       vector<int> ans;
	       return ans;
	   }
    }
};

