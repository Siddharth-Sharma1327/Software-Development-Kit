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
    int maxRemove(vector<vector<int>>& stones, int n) {
        // Code here
        int maxRow = 0;
        int maxCol = 0;
        
        for(auto it: stones){
            maxRow = max(maxRow, it[0]);
            maxCol = max(maxCol, it[1]);
        }
        
        DisjointSet ds(maxRow + maxCol +1);  //NOT +2 because size array has size(n+1)
         
        unordered_map<int,int> stoneNodes;  
        for(auto it: stones){
            
            int nodeRow = it[0];
            int nodeCol = it[1] + maxRow + 1;
            
            ds.unionBySize(nodeRow, nodeCol);
            
            stoneNodes[nodeRow] = 1;    //---->> VERY IMP--> map stores only values which are called and not like array or vectors..eg- here it stores only those values which are called as stoneNodes[nodeRow] and stoneNode[nodeCol] i.e only pairs having keys as nodeRow and nodeCol
            stoneNodes[nodeCol] = 1;
        }
        
        /*
        We just need the nodes in DisjointSet which are involved in having a stone.
        So we store the rows and columns in map as they will have stones.
        And we just need to count them once for ultimate parents.
        */
        
        int cnt=0;
        for(auto it: stoneNodes){           // the nodes which don't have stones(i.e rows and columns that don't have stones are not present in map)
            if(ds.findUPar(it.first) == it.first){
                cnt++;
            }
        }
        
        return n- cnt;
    }
};
int main(){
    return 0;
}