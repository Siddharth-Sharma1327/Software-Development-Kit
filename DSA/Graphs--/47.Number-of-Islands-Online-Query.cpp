#include<iostream>
#include<bits/stdc++.h>

using namespace std;

// Online Query means---storing answer for every input query--dynamic graph
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


class Solution {
  private:
     bool isValid(int adjr, int adjc, int n, int m){        //function for validity of adjacent cell
        return (adjr>=0 && adjr<n && adjc>=0 && adjc<m);
    }
  public:
    vector<int> numOfIslands(int n, int m, vector<vector<int>> &operators) {
        // code here
        DisjointSet ds(n*m);      // disjointset for n*m nos.
        int vis[n][m];          // visited array to check for repeated operations
        memset(vis, 0, sizeof(vis));   //function to set values 0 or -1 only as it moves byte-by-byte...rfer GFG
        int cnt=0;                   //cnt of islands
        vector<int> ans;
        
        for(auto it: operators){
            int row = it[0];            //current row and col of operation
            int col = it[1];
            
            if(vis[row][col]==1){       //if visted earlier then simply push current islands no in ans and continue
                ans.push_back(cnt);
                continue;
            }
            
            vis[row][col]=1;            // if not visited earlier then mark it now visited
            cnt++;                      // IMP--Here we assume every new cell as a new island and then reduce it if it belongs to any group
            // row-1, col
            // row, col-1
            // row, col+1
            // row+1,col
            
            int delrow[] = {-1, 0, 1, 0};   // neighbors
            int delcol[] = {0, 1, 0, -1};
            
            for(int ind=0;ind<4;ind++){
                int adjr = row + delrow[ind];    //adjacent cell
                int adjc = col + delcol[ind];
                if(isValid(adjr, adjc, n, m)){
                    if(vis[adjr][adjc]==1){         //checked if adjacent cell is 1 for making group
                        int nodeNo = row*m + col;       //current cell's value ie NO is calculated--(hypothetically every cell is assumed as a node in Disjoint set)
                        int adjNodeNo = adjr*m + adjc;  // adjacent cell's vale ie No
                        
                        if(ds.findUPar(nodeNo) != ds.findUPar(adjNodeNo)){          // current cell is grouped with adjacent cell group only if they both contains different ultimate parents---eg  1 '1'  <-- this one is checked with both ones below and left ones
                            cnt--;                                           //if grouped then cnt is reduced by 1                                                                                                               //      1  1
                            ds.unionBySize(nodeNo, adjNodeNo);
                        }
                    }
                }
            }
            
            ans.push_back(cnt);             // current operators no. of islands are pushed into the ans
            
        }
        
        
        return ans;
        
    }
};

// one more similar solution------
class Solution {
  public:
    vector<int> numOfIslands(int n, int m, vector<vector<int>> &operators) {
        // code here
        vector<int> ans;
        vector<vector<int>> mat(n, vector<int>(m, 0));
        vector<vector<int>> nodes(n, vector<int>(m, 0));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                nodes[i][j] = i*(m) + j;
            }
        }
        DisjointSet ds(n*m);
        int cnt=0;
        for(int i=0;i<operators.size();i++){
            int row = operators[i][0];
            int col = operators[i][1];
            if(mat[row][col]==1){
                ans.push_back(cnt);
                continue;
            } 
            
            mat[row][col]=1;
            int delrow[] = {-1, 0, 1, 0};
            int delcol[] = {0, 1, 0, -1};
            
            cnt++;
            for(int k=0;k<4;k++){
                int nrow = row + delrow[k];
                int ncol = col + delcol[k];
                
                if(nrow>=0 && nrow<n && ncol>=0 && ncol<m && mat[nrow][ncol]==1){
                    if(ds.findUPar(nodes[row][col])!=ds.findUPar(nodes[nrow][ncol])){
                       ds.unionBySize(nodes[row][col], nodes[nrow][ncol]);
                        cnt--; 
                    }
                    
                }
            }
            
            // int cnt=0;
            // for(int k=0;k<n;k++){
            //     for(int j=0;j<m;j++){
            //         if(ds.findUPar(k*m-1+j) == k*m-1+j && mat[k][j]!=0){
            //             cnt++;
            //         }
            //     }
            // }
            
            ans.push_back(cnt);
        }
        
        return ans;
        
    }
};
int main(){
    return 0;
}