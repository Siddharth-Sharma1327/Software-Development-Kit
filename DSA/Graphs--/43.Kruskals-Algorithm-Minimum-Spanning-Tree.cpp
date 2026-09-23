#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// 
class DisjointSet{
    vector<int> rank, parent, size;
public:
    DisjointSet(int n){
        rank.resize(n+1, 0);    //n+1----> for 1-based indexed arrays also
        parent.resize(n+1);
        size.resize(n+1);

        for(int i=0;i<=n;i++){
            parent[i]=i;
            size[i]=1;
        }
    }

    int findUPar(int node){     //function to find ultimate parent of the node
        if(node==parent[node]) return node;

        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v){      //  Union by rank function
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);

        if(ulp_u == ulp_v) return;  //connected nodes in the component of graph

        if(rank[ulp_u] < rank[ulp_v]){
            parent[ulp_u] = ulp_v;
        }else if(rank[ulp_v] < rank[ulp_u]){
            parent[ulp_v] = ulp_u;
        }else{
            parent[ulp_v] = ulp_u;    //can take anyone 
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v){      //  Union by size function
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);

        if(ulp_u == ulp_v) return;  //connected nodes in the component of graph

        if(size[ulp_u] < size[ulp_v]){
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }else{
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }

};




class Solution
{
	public:
	//Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        // code here
        
        // S.C----> O(M)----
        vector<pair<int,pair<int,int>>> edges;
        
        // 1->2 wt=5
        // 1->(2,5)
        // 2->(1,5)
        
        // (5, 2, 1)
        // (5, 1, 2)
        
        // O(N + E)   --> check T.C of DFS for clearification--
        for(int i=0;i<V;i++){
            for(auto it: adj[i]){
                int adjNode = it[0];
                int wt = it[1];
                int node = i;
                
                edges.push_back({wt, {node, adjNode}});  //since we are iterating all the adjacent nodes of every node so every edge is stored twice as above in comments is shown but not to worry as these multiple is not considered in DisjointSet() DS i.e it considers only one edge as it continues and do nothing if ultimate parents of nodes are same..so every edge is considered once only.
            }
        }
        
        
        DisjointSet ds(V);
        
        
        // M*logM   ---> if there are M edges (T.C of sort function)----
        sort(edges.begin(), edges.end());    //sorting according to the weights
        int mstWt=0;
        
        // M X 4*alpha-----> (for every edge we are using disjoint function)---------
        for(auto it: edges){
            int wt = it.first;
            int u = it.second.first;
            int v = it.second.second;
            
            
            if(ds.findUPar(u) != ds.findUPar(v)){                 // if they doesn't belongs to same component then add their wt to mstWt..else don't
                mstWt += wt;
                ds.unionBySize(u, v);
            }
        }
        
        return mstWt;
    }
};



// OVERALL TIME COMPLEXITY---->  O(N+E) + M*logM + M x 4*ALPHA---------------

//{ Driver Code Starts.


int main()
{
    int t;
    cin >> t;
    while (t--) {
        int V, E;
        cin >> V >> E;
        vector<vector<int>> adj[V];
        int i=0;
        while (i++<E) {
            int u, v, w;
            cin >> u >> v >> w;
            vector<int> t1,t2;
            t1.push_back(v);
            t1.push_back(w);
            adj[u].push_back(t1);
            t2.push_back(u);
            t2.push_back(w);
            adj[v].push_back(t2);
        }
        
        Solution obj;
    	cout << obj.spanningTree(V, adj) << "\n";
    }

    return 0;
}


// } Driver Code Ends
int main(){
    return 0;
}