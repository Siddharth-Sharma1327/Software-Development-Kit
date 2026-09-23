#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Solution {
  public:
    /*  Function to implement Bellman Ford
    *   edges: vector of vectors which represents the graph
    *   S: source vertex to start traversing graph with
    *   V: number of vertices
    */
    vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S) {  //given 2d vector of edges between nodes and their weights--(order of the edges given doesn't matter)
        // Code here
        vector<int> dist(V, 1e8);        // distance vector of each node from source node
        dist[S]=0;        //source dist made 0
        for(int i=0;i<V-1;i++){           //for loop for N-1 iterations
            for(auto it: edges){          //ietration of all given edges
                int u = it[0];
                int v = it[1];
                int wt = it[2];
                
                if(dist[u]!=1e8 && dist[u]+wt<dist[v]){        //realxing of the edges
                    dist[v]=dist[u]+wt;
                }
                
            }
        }
        
        for(auto it: edges){          //Now if there is a neagative cycle in the graph the following iteration would be done and will go inside the if condition--which states that there is a -ve cycle as in Nth ietrationa slo the doistance  array is reducing/updating which is not possible for the normal graph as per the Bellman
            int u = it[0];
            int v = it[1];
            int wt = it[2];
            
            if(dist[u]!=1e8 && dist[u]+wt<dist[v]){
                return {-1};                              //return -1 if -ve cycle
            }
        }
        
        return dist;                ///esle return the dist array
    }
};
//Time Complexity--> O(VxE);
//Space Complexity--> o(V)