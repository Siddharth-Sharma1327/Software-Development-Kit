#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Approach---1 (Normal Dijkstras Algo(i.e using PQ with distance as the sorting factor) Failed here...considered the test case given by striver in video)
/*
5 6   -- n, edges
0 1 5 -- edges with prices
1 2 5
0 3 2
3 1 2
1 4 1
4 2 1
0       --src
2       --dest
2       --K

*/
// Approch---2 (Use Dijkstra Algo(i.e use PQ BUT WITH "cnt" as the sorting factor))...this works

// Approach---3 (BUt in above approach we don't require PQ as "cnt"(sorting factor) is incraesing level wise only..like BFS with unit weights)

class Solution {
  public:
  #define pp pair<int,pair<int,int>>
    int CheapestFLight(int n, vector<vector<int>>& flights, int src, int dst, int K)  {
        // Code here
        vector<pair<int,int>> adj[n];
        for(int i=0;i<flights.size();i++){
            adj[flights[i][0]].push_back({flights[i][1], flights[i][2]});
        }
        
        if(src==dst) return 0;
        
        queue<pp> pq;
        vector<int> dist(n, -1);
        dist[src]=0;
        pq.push({0, {src, 0}});
        
        while(!pq.empty()){
            auto it = pq.front();
            int cnt = it.first;
            int node = it.second.first;
            int price = it. second.second;
            pq.pop();
            
            if(cnt>K) continue;     //saving further more iterations of for loop
            
            for(auto it: adj[node]){
                int adjNode = it.first;
                int adjPrice = it.second;
                
                if((dist[adjNode]==-1 || price+adjPrice < dist[adjNode])){
                    if(cnt<=K){
                        dist[adjNode]  = price+adjPrice;
                        pq.push({cnt+1, {adjNode, dist[adjNode]}}); 
                    }
                    
                }
            }
        }
        
        return dist[dst];
    }
};

// T.C -> O(E+V)  simple as BFS



