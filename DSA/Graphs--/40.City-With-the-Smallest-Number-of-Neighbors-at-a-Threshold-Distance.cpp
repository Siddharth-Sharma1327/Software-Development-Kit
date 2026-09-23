#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Through Dijkstra's Algorithm--------------
class Solution {
  public:
    int findCity(int n, int m, vector<vector<int>>& edges, int distanceThreshold) {
        vector<pair<int,int>> adj[n];
        for(int i=0;i<edges.size();i++){
            adj[edges[i][0]].push_back({edges[i][1], edges[i][2]});
            adj[edges[i][1]].push_back({edges[i][0], edges[i][2]});
        }
        
        vector<vector<int>> dist(n, vector<int>(n, 1e9));
        for(int i=0;i<n;i++){
            priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
            dist[i][i]=0;
            pq.push({0, i});
            
            while(!pq.empty()){
                int node = pq.top().second;
                int dis = pq.top().first;
                pq.pop();
                
                for(auto it: adj[node]){
                    int edgeWeight = it.second;
                    int adjNode = it.first;
                    
                    if(dis + edgeWeight < dist[i][adjNode]){
                        dist[i][adjNode] = dis + edgeWeight;
                        pq.push({dist[i][adjNode], adjNode});
                    }
                }
            }
        }
        int city=1e9;
        int c=-1;
        for(int i=0;i<n;i++){
            int cnt=0;
            for(int j=0;j<n;j++){
                // cout<<dist[i][j]<<" ";
                if(dist[i][j]<=distanceThreshold ){
                    cnt++;
                }
            }
            if(cnt<=city && cnt!=0){
                city=cnt;
                c=max(c, i);
            }
            // cout<<endl;
        }
        return c;
    }
};

int main(){
    return 0;
}