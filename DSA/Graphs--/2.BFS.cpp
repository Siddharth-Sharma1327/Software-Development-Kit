#include<iostream>
#include<bits/stdc++.h>
using namespace std;

const int N= 1e5+2;
bool vis[N];               //flag if node is visited
vector<int> adjl[N];       // array of vectors

int main(){
    for(int i=0;i<N;i++){        //all flags intialised with O
        vis[i]=0;
    }

    int n,m;                      // nodes and edges present between the nodes
    cin>>n>>m;
    for(int i=0;i<m;i++){          //Adjancy list is created 
        int x,y;
        cin>>x>>y;
        adjl[x].push_back(y);        //here the indexing is not important as nowhere adjl[0] is encountered
        adjl[y].push_back(x);
    }

    queue<int> q;
    q.push(1);                   //first node(root node) is pushed into the queue
    vis[1]=true;

    while(!q.empty()){
        int node=q.front();
        q.pop();
        cout<<node<<endl;

    //Merhod 1--
        vector<int> :: iterator it;
        for(it=adjl[node].begin();it!=adjl[node].end(); it++){         //while the node is poped from the queue its children from the adjancy list are pushed into the queue
            if(!vis[*it]){              //nodes only which are not visited
                vis[*it]=true;                 //visited nodes flag is marked true
                q.push(*it);             //value to be pushed is dereferenced using iterator
            }
        }
    //Merhod 2--
        // for(auto it : adjl[node]){
        //         if(!vis[it]){
        //             vis[it]=1;
        //             q.push(it);
        //         }
        //     }
    }
    return 0;
}

// S.C -> O(n)(queue) + O(2E)(adjancy list)
//Time Complexity is --
        /*  
        for while loop--> O(1)+O(degree of node)
        for n loops--> n*O(1)+O(d1+d2+d3...dn)
                   --> O(n)+O(2E)
                   --> O(n+2E)
                   -->O(n+E)
        
        
        */

    //    T.C -> O(n + E)----for directed graph