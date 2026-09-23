#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Solution
{
	public:
	//Function to find the shortest distance of all the vertices
    //from the source vertex S.
    vector <int> dijkstra(int V, vector<vector<int>> adj[], int S)   //SETS-->Here we can delete the already existing paths from the queue/set
    {                                                                                      
        // Code here
        set<pair<int,int>> st;           //set of pairs is used instead of the PQ
        vector<int> dist(V, INT_MAX);   //distance array
        st.insert({0, S});            //source node is inserted and dist of source is 0
        dist[S]=0;
        
        while(!st.empty()){
            auto it = *(st.begin());        //first elemnet of the set
            int node = it.second;
            int dis = it.first;             //node and its distnace value stored
            st.erase({dis, node});          //pair of node and its distnace is poped from the set
            
            for(auto it: adj[node]){
                int edgeW = it[1];          //adjacent node and its weight from node is stored
                int adjNode = it[0];
                
                if(dis+edgeW < dist[adjNode]){          //if having better distance value than the previous
                   
                    if(dist[adjNode]!=INT_MAX){           //IMP--the which was visited previous with some distance that pair is poped from the set as it of no use to iterate it as we got the better one so we came inside the "if"
                    st.erase({dist[adjNode], adjNode});
                    }
                    dist[adjNode] = dis+edgeW;
                    st.insert({ dist[adjNode], adjNode });      //adjacent node with its updated distance value is pushed into the set
                }
            }
        }
        
        return dist;               //distance array is returned
    }
};


// HERE T.C is almost same comapare to the PQ...as even we are removing some nodes from queue which will reduce t.c but st.erase()..aslo takes logN t.c so we cannot say that it will take less t.c than pq...it will depend on many other factors