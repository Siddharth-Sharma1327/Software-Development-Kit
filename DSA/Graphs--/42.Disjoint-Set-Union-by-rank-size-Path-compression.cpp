#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// UNION BY RANK AND SIZE--------------------------------------



//       |----------------IT IS A DATA STRUCTURE_________    This code works for both 0-based indexed and 1-based indexed graphs---------
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


int main(){

// Union By Rank--------------
//     DisjointSet ds(7);
//     ds.unionByRank(1, 2);
//     ds.unionByRank(2, 3);
//     ds.unionByRank(4, 5);
//     ds.unionByRank(6, 7);
//     ds.unionByRank(5, 6);
// //  if 3 and 7 are in same component or not---

//     if(ds.findUPar(3) == ds.findUPar(7)){
//         cout<<"SAME\n";
//     }else cout<<"NOT SAME\n";

//     ds.unionByRank(3, 7);
//     if(ds.findUPar(3) == ds.findUPar(7)){
//         cout<<"SAME\n";
//     }else cout<<"NOT SAME\n";





// Union By Size----
    DisjointSet ds(7);
    ds.unionBySize(1, 2);
    ds.unionBySize(2, 3);
    ds.unionBySize(4, 5);
    ds.unionBySize(6, 7);
    ds.unionBySize(5, 6);
//  if 3 and 7 are in same component or not---

    if(ds.findUPar(3) == ds.findUPar(7)){
        cout<<"SAME\n";
    }else cout<<"NOT SAME\n";

    ds.unionBySize(3, 7);
    if(ds.findUPar(3) == ds.findUPar(7)){
        cout<<"SAME\n";
    }else cout<<"NOT SAME\n";
    return 0;
}





// BOTH UNION-BY-RANK AND UNION-BY-SIZE BOTH HAVE SAME COMPLEXITY OF O(4*ALPHA).....ALPHA~=1