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
    int Solve(int n, vector<vector<int>>& edge) {
        // code here
        int extra=0;
        DisjointSet ds(n);
        for(int i=0;i<edge.size();i++){
            if(ds.findUPar(edge[i][0])==ds.findUPar(edge[i][1])){
                extra++;
            }
            else ds.unionBySize(edge[i][0], edge[i][1]);
        }
        int compo=0;
        for(int i=0;i<n;i++){
            if(ds.parent[i]==i) compo++;
        }
        if(extra>=compo-1) return compo-1;
        else return -1;
    }
};


int  main(){
    return 0;
}