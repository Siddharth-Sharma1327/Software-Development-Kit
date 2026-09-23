#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Solution
{   private:
    void dfs(int node, int vis[], stack<int> &st, vector<int> adj[]){
        vis[node]=1;              // node is marked visited
        
        for(auto it: adj[node]){               //adjacent nodes are called
            if(!vis[it])  dfs(it, vis, st, adj);    //if adjacent node is note visted then call dfs for it 
            
        }
        
        st.push(node);                       // after the dfs of the current node push the current node value into the stack
    }
    //APPROACH-->visit a non visited node..call dfs for it then call dfs for its adjacent nodes and then before returning push the current node value into the stack...After all this print stack elments and that order will be one of valid linear ordering

	public:
	//Function to return list containing vertices in Topological order. 
	vector<int> topoSort(int V, vector<int> adj[])        //adjancy list is given..have to return valid linear ordering of the topological sort
	{
	    // code here
	    int vis[V] = {0};             //visited array for the nodes
	    stack<int> st;                // stack is created
	    
	    for(int i=0;i<V;i++){         // for all nodes
	        if(!vis[i]){              // not visited cal dfs for it
	            dfs(i, vis, st, adj);
	        }
	    }
	    
	    vector<int> ans;                // store all the elments of stack into the vector one-by-one
	    while(!st.empty()){
	        ans.push_back(st.top());
	        st.pop();
	    }
	    
	    return ans;                     //return the vector
	}
};

// Space Complexity--> O(V) + O(V) (for the vis array and for the stack)
// Time Complexity--> O(V) + O(V+E) (for the for loop and dfs of the directed graph)