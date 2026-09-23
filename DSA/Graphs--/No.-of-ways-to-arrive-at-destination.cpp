#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Here idea is that We cannot use simple counter for the n-1 node as the no. of ways for reaching the any node is dependent on the no. of ways for reaching the previous node.
class Solution {
  public:
    int countPaths(int n, vector<vector<int>>& roads) {
        // code here
        int mod = 1e9 + 7;
        vector<pair<int,int>> adj[n];
        for(int i=0;i<roads.size();i++){
            adj[roads[i][0]].push_back({roads[i][1], roads[i][2]});
            adj[roads[i][1]].push_back({roads[i][0], roads[i][2]});
            
        }
        
        
        vector<int> price(n, 1e9);
        priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        // priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq
        pq.push({0, 0});
        vector<int> ways(n, 0);
        ways[0]=1;
        price[0]=0;
        while(!pq.empty()){
            int node = pq.top().second;
            int t = pq.top().first;
            pq.pop();
            
            for(auto it: adj[node]){
                int adjNode = it.first;
                int adjT = it.second;
                
                if(t + adjT < price[adjNode]){
                    price[adjNode]=t+adjT;
                    pq.push({t+adjT, adjNode});
                    ways[adjNode] = ways[node];
                }
                else if(t+adjT == price[adjNode]){
                    ways[adjNode] = (ways[adjNode] + ways[node])%mod;
                }
            }
            
        }
        
        return ways[n-1];
    }
};


// Wrong solution----------
class Solution {
  public:
    int countPaths(int n, vector<vector<int>>& roads) {
        // code here
        int mod = 1e9 + 7;
        vector<pair<int,int>> adj[n];
        for(int i=0;i<roads.size();i++){
            adj[roads[i][0]].push_back({roads[i][1], roads[i][2]});
            adj[roads[i][1]].push_back({roads[i][0], roads[i][2]});
            
        }
        
        
        vector<int> price(n, 1e9);
        priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        // priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq
        pq.push({0, 0});
        int cnt=0;
        price[0]=0;
        while(!pq.empty()){
            int node = pq.top().second;
            int t = pq.top().first;
            pq.pop();
            
            for(auto it: adj[node]){
                int adjNode = it.first;
                int adjT = it.second;
                
                if(t + adjT < price[adjNode]){
                    price[adjNode]=t+adjT;
                    pq.push({t+adjT, adjNode});
                    if(adjNode==n-1) cnt=1;
                }
                else if(t+adjT == price[adjNode] && adjNode==n-1){
                    cnt=(cnt+1)%mod;
                }
            }
            
        }
        
        return cnt;
    }
};




// That's why here we have used the ways array for storing the no. of ways for reaching any node so that it can be used for counting no. of ways of the next node and ultimately for the n-1 th node.
int main(){
    return 0;
}