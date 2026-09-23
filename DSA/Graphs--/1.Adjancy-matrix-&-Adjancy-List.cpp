#include<iostream>
#include<bits/stdc++.h>

using namespace std;

int main(){


// ------------------ADJACENCY MATRIX------------------------------
    int n,m;
    cin>>n>>m;
    vector<vector<int>> adjm;
    for(int i=0;i<n;i++){
        vector<int> m;
        for(int j=0;j<n;j++){
            int temp=0;
            m.push_back(temp);
        }
        adjm.push_back(m);
    }
    
    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        adjm[x-1][y-1]=1;
        adjm[y-1][x-1]=1;
    }
    cout<<"Adjacency Matrix"<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<adjm[i][j]<<" ";
        }
        cout<<endl;
    }

    if(adjm[3][1]==1){                                                //O(1)
        cout<<"There is an edge between 4 and 2"<<endl;
    }else {
        cout<<"No edge between 4 and 2"<<endl;
    }



//----------------------------------ADJACENCY LIST--------------------------------------
    vector<int> adjl[n];                           //IMP--- here array of vectors is implemented and not vector of vectors...As here we don't push whole row once rather we put elments as per inputs in different arrays of the elements so here vector of vectors cannot be used.
    for(int i=0;i<m;i++){
        int x,y;
        cin>>x>>y;
        adjl[x-1].push_back(y);
        adjl[y-1].push_back(x);
    }
    cout<<"Adjacency list"<<endl;
    for(int i=0;i<n;i++){
        cout<<(i+1)<<"->";
        vector<int> :: iterator it;
        for(it=adjl[i].begin(); it!=adjl[i].end();it++){
            cout<< *it<<",";
        }
        cout<<endl;
    }
    return 0;
}