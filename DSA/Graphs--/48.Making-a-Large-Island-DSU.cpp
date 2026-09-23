#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// 
class DisjointSet{

public:
    vector<int> rank, parent, size;
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

class Solution {
  public:
  
  bool isValid(int adjr, int adjc, int n, int m){
      return (adjr>=0 && adjr<n && adjc>=0 && adjc<m);
  }
  
    int MaxConnection(vector<vector<int>>& grid) {
        // code here
        int ans=0;
        
        int n = grid.size();
        int m = grid[0].size();
        
        DisjointSet ds(n*m);
        
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]==1){
                    
                    int delrow[] = {-1, 0, 1, 0};
                    int delcol[] = {0, 1, 0, -1};
                    
                    // set<int> neighbors;
                    for(int ind=0;ind<4;ind++){
                        int adjr = i + delrow[ind];
                        int adjc = j + delcol[ind];
                        
                        if(isValid(adjr, adjc, n, m)){
                            if(grid[adjr][adjc]==1){
                                int nodeNo = i*m + j;
                                int adjNodeNo = adjr*m + adjc;
                                
                                if(ds.findUPar(nodeNo) != ds.findUPar(adjNodeNo)){
                                    ds.unionBySize(nodeNo, adjNodeNo);
                                }
                                
                            }
                        }
                    }
                }
            }
        }               // initial connected graphs is created...
        
        for(int i=0;i<n*m;i++){                 // intial max-sized group of 1's is stored---i.e not changing of 0 to 1 of any cell
            ans = max(ans, ds.size[i]);
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]==0){
                    
                    set<int> neighbors;                 // here set is used to store all the unique  adjacent groups of 1's adjacent to the current cell so that not counting same group 1 twice i.e adjacemt 1's having same ultimate parent
                    int delrow[] = {-1, 0, 1, 0};
                    int delcol[] = {0, 1, 0, -1};
                    
                    for(int ind=0;ind<4;ind++){
                        int adjr = i + delrow[ind];
                        int adjc = j + delcol[ind];
                        
                        if(isValid(adjr, adjc, n, m)){
                            if(grid[adjr][adjc]==1){
                                int nodeNo = i*m + j;
                                int adjNodeNo = adjr*m + adjc;
                                
                                neighbors.insert(ds.findUPar(adjNodeNo));
                                
                            }
                        }
                    }
                    
                    int temp=1;                         // finlly for current cell total size of 1's is sum of (1 + size of all adjcent groups) and max of all iterations is stored
                    for(auto it: neighbors){
                        temp+=ds.size[it];
                    }
                    
                    ans = max(ans, temp);
                }
            }
        }
        
        return ans;
    }
};


int main(){
    return 0;
}