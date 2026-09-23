#include<iostream>
#include<bits/stdc++.h>
using namespace std;


class Solution {
private:
    bool check(int start, int V, vector<int>adj[], int color[]){
        queue<int> q;                           //queue of nodes
        color[start] = 0;                       // color of the starting node of the component is made '0'
        q.push(start);                          // starting node of the component is pushed into the queue.
        
        while(!q.empty()){
            int node = q.front();            //node value is stored
            q.pop();
            
            //traverse the adjacent nodes of the current node
            for(auto i : adj[node]){          
                if(color[i]==-1){           //if not colored in any path
                    color[i] = !color[node];     //color of the adjacent node is made opposite of the of the current nodes color
                    q.push(i);                   // adjacent node pushed into the queue
                }
                
                else if(color[i]==color[node]){    //if colored in any other path and with the same color as that of the current nodes color so false
                    return false;
                }
            }
        }
        
        return true;                              //for whole colponent of the graph we were able to color adjacent nodes with different color..so return true.
    }
public:
	bool isBipartite(int V, vector<int>adj[]){        //check for bipartite graph
	    // Code here
	    int color[V];                                 //color array is created
	    for(int i=0;i<V;i++){
	        color[i]=-1;                              //for each node intially -1 for no colored
	    }
	    
	    for(int i=0;i<V;i++){                        //for loop for the different components fo the graph
	        if(color[i]==-1){                        //if not colored
	            if(check(i, V, adj, color)==false) return false;          //check of bipartite is called for the particular component with i= node value
	        }
	    }
	    
	    return true;                                //if all the components retur true for the bipartite check then graph is bipartite
	}

};
//Space Complexity--> O(V) for color array
//Time Complexity--> O(V+E) (same explaination as that of the BFS)