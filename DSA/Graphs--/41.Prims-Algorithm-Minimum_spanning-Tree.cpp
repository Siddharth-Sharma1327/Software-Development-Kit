#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// 
//{ Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution
{
	public:
	//Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[])   //-----<< This is adjacency list only.....
    {
        // code here
        int sum=0;
        vector<int> vis(V, 0);
        // O(E)
        priority_queue<pair<pair<int,int>, int> , vector<pair<pair<int,int>, int>>, greater<pair<pair<int,int>, int>> > pq;
        pq.push({{0,0}, -1});
        // O(E)
        while(!pq.empty()){
            // O(logE)
            int wt = pq.top().first.first;
            int node = pq.top().first.second;
            int parent = pq.top().second;
            pq.pop();

            if(vis[node]==1) continue;
            vis[node]=1;
            sum+=wt;

        //    O(ElogE)
            for(auto it: adj[node]){
                // O(logE)
                if(!vis[it[0]]) pq.push({{it[1], it[0]}, node});
            }
        }
        
        return sum;
    }
};

// T.C -> E(O(1)*logE) + O(d1 + d2 + d3+.....+dn)*logE
//        = ElogE + E*logE
        //=  ElogE

// Here parent is stored so if asked to construct the Minimum Spanning Tree then we can store the pairs of {node, parent} in MST array of pairs.

// T.C = 1 iteration = O(logE) + d1 * logE
//       all ieterations = O(logE * E + (d1 + d2 + d3 +.....+dn)*logE) = O(ElogE + ElogE) = O(ElogE) -> for while loop ther can be 'E' values into queue


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