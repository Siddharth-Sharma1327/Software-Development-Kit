#include<iostream>
#include<bits/stdc++.h>
using namespace std;


                //-------------SAME EXPLANATION AS THAT OF THE BIPARTITE-GRAPH-BFS----------------
class Solution {
private:
    bool checkdfs(int node, int col, vector<int>adj[], int color[]){
       color[node]=col;
       for(auto i: adj[node]){
           if(color[i]==-1){
               if(checkdfs(i, !col, adj, color)==false) return false;
           }else if(color[i] == color[node]){
               return false;
           }
       }
        return true;
    }
public:
	bool isBipartite(int V, vector<int>adj[]){
	    // Code here
	    int color[V];
	    for(int i=0;i<V;i++){
	        color[i]=-1;
	    }
	    
	    for(int i=0;i<V;i++){
	        if(color[i]==-1){
	            if(checkdfs(i, 0, adj, color)==false) return false;
	        }
	    }
	    
	    return true;
	}

};
//Space Complexity--> O(V) for color array
//Time Complexity--> O(V+E) (same explaination as that of the DFS)