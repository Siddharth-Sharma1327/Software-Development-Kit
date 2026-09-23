#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// BFS Approach--- (leetcode & GFG)---Only BFS is possible as here we have to detect for cycle as well so Kahn's algo is used
//                                    ..we can't use Toposort DFS as it only gives linear ordering and not detects cycle

// LEETCODE CODE---
class Solution {
public:
       
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        
        vector<int> indegree(numCourses, 0);
        vector<int> adj[numCourses];
        for(int i=0;i<prerequisites.size();i++){
            indegree[prerequisites[i][0]]++;
            adj[prerequisites[i][1]].push_back(prerequisites[i][0]);
        }
        queue<int> q;
        for(int i=0;i<numCourses;i++){
            if(indegree[i]==0) q.push(i);
        }
        
        vector<int> ans;
        
        while(!q.empty()){
            int node = q.front();
            ans.push_back(node);
            q.pop();
            
            for(auto it: adj[node]){
                indegree[it]--;
                if(indegree[it]==0) q.push(it);
            }
        }
        
        if(ans.size()==numCourses) return ans;
        else return {};
    }
};


// GFG CODE-------
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