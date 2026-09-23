#include<istream>
#include<bits/stdc++.h>
using namespace std;
// 


class Solution
{   
    private:
    void dfs(int node, vector<int> &vis, vector<vector<int>> &adj, stack<int> &st){
        vis[node]=1;
        for(auto it: adj[node]){
            if(!vis[it]){
                dfs(it, vis, adj, st);
            }
        }
        
        st.push(node);
    }
    
    
    void dfs3(int node, vector<int> &vis, vector<int> adjT[]){
        vis[node]=1;
        for(auto it: adjT[node]){
            if(!vis[it]){
                dfs3(it, vis, adjT);
            }
        }
    }
    
	public:
	//Function to find number of strongly connected components in the graph.
    int kosaraju(int V, vector<vector<int>>& adj)
    {
        //code here
        vector<int> vis(V, 0);
        
        //to store the sorting order
        stack<int> st;
        //sorting according to finishing time
        for(int i=0;i<V;i++){           // O(V+E)
            if(!vis[i]){
                dfs(i, vis, adj, st);
            }
        }
        
        //Reversing the graph
        vector<int> adjT[V];  //Transpose Graph----
        
        // O(V+E)----IMP  TRICK is that for every iteration of first for-loop no of iterations called in second for-loop are not same
        for(int i=0;i<V;i++){
            vis[i]=0;               //reseting visited array
            for(auto it: adj[i]){
                // i->it
                // reverse- it->i
                adjT[it].push_back(i);
            }
        }
        
        int scc=0;
        //O(V+E)-----same logic
        while(!st.empty()){
            int node = st.top();
            st.pop();
            if(!vis[node]){
                scc++;
                dfs3(node, vis, adjT);
            }
        }
        
        return scc;
    }
};
int main(){
    // cout<<min(INT_MAX, INT_MAX);
    return 0;
}