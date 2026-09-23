#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// Actual Approach----
#include<bits/stdc++.h>

using namespace std;

class Solution {
  private:
    void topoSort(int node, vector < pair < int, int >> adj[],
      int vis[], stack < int > & st) {
      //This is the function to implement Topological sort. 
      vis[node] = 1;
      for (auto it: adj[node]) {
        int v = it.first;
        if (!vis[v]) {
          topoSort(v, adj, vis, st);
        }
      }
      st.push(node);
    }
  public:
    vector < int > shortestPath(int N, int M, vector < vector < int >> & edges) {

      //We create a graph first in the form of an adjacency list.
      vector < pair < int, int >> adj[N];
      for (int i = 0; i < M; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int wt = edges[i][2];
        adj[u].push_back({v, wt}); 
      }
      // A visited array is created with initially 
      // all the nodes marked as unvisited (0).
      int vis[N] = {
        0
      };
      //Now, we perform topo sort using DFS technique 
      //and store the result in the stack st.
      stack < int > st;
      for (int i = 0; i < N; i++) {
        if (!vis[i]) {
          topoSort(i, adj, vis, st);
        }
      }
      //Further, we declare a vector ‘dist’ in which we update the value of the nodes’
      //distance from the source vertex after relaxation of a particular node.

      vector < int > dist(N);
      for (int i = 0; i < N; i++) {
        dist[i] = 1e9;
      }

      dist[0] = 0;
      while (!st.empty()) {
        int node = st.top();
        st.pop();

        for (auto it: adj[node]) {
          int v = it.first;
          int wt = it.second;

          if (dist[node] + wt < dist[v]) {
            dist[v] = wt + dist[node];
          }
        }
      }

      for (int i = 0; i < N; i++) {
        if (dist[i] == 1e9) dist[i] = -1;
      }
      return dist;
    }
};

int main() {

  int N = 6, M = 7;
  
  vector<vector<int>> edges= {{0,1,2},{0,4,1},{4,5,4},{4,2,2},{1,2,3},{2,3,6},{5,3,1}};
  Solution obj;
  vector < int > ans = obj.shortestPath(N, M, edges);

  for (int i = 0; i < ans.size(); i++) {

    cout << ans[i] << " ";
  }

  return 0;

}
// Algo-to-use-----> POP the elements from stack untill we found source node after that upadte distances....if a destination node is somehow connected to the src node its distance from source node will be upadated surley...check by dry run for some graph
// T.C -> O(N + M)------In this aproach we push a node only 1 time in queue 
//  S.C -> O(N)



// Better written code----
class Solution {
  public:
     vector<int> shortestPath(int N,int M, vector<vector<int>>& edges){
        // code here
        vector<pair<int,int>> adj[N];
        for(int i=0;i<M;i++){
            adj[edges[i][0]].push_back({edges[i][1], edges[i][2]});
        }
        
        // vector<int> ans(N, -1);
        vector<int> sum(N, -1);
        queue<pair<int,int>> q;
        sum[0]=0;
        q.push({0, 0});
        
        while(!q.empty()){
            int node = q.front().first;
            int wt = q.front().second;
            q.pop();
            
            for(auto it: adj[node]){
                int adjNode = it.first;
                int adjWt = it.second;
                
                if(sum[adjNode]==-1 || (wt + adjWt) < sum[adjNode]){
                    sum[adjNode]= wt+adjWt;
                    q.push({adjNode, sum[adjNode]});
                }
            }
        }
        return sum;
    }
};
// T.C -> O(N*M)------worst case---  here in this case same node is inserted multiple times in queue which increases time complexity
// S.C ->O(N)