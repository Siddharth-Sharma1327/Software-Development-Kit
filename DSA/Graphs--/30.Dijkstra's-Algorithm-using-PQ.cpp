#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Solution
{
	public:
	//Function to find the shortest distance of all the vertices
    //from the source vertex S.
    vector <int> dijkstra(int V, vector<vector<int>> adj[], int S)    //an array of vector of vectors(pairs) is given denoting 1st no as an edge with the node and 2nd no. as its weight with node in th pair
    {
        // Code here
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;          //as per algo min heap of pairs is created to store the pairs of node and its weight
        vector<int> dist(V, INT_MAX);          //vector of distance of each node from source node S
        dist[S]=0;
        pq.push({0, S});            //source with distance 0 pushed into the queue
        
        while(!pq.empty()){
            int node = pq.top().second;          //current node and weight to go there is stored
            int dis = pq.top().first;
            pq.pop();
            
            for(auto it: adj[node]){              //adajcent nodes of the node are iterated
                int edgeWeight = it[1];           //current nodes edgeweight & node value
                int adjNode = it[0];
                
                if(dis + edgeWeight <dist[adjNode]){          //now if we get the distance value of the node + edgeweight of the current node better than the distance value of current node then we will update it
                    dist[adjNode] = dis+edgeWeight;
                    pq.push({dist[adjNode], adjNode});        //current node with updated distance value is pushed into the queue
                }
            }
        }
        
        return dist;                                   //final distance array of distance of each node from the source node is returned
    } 
};