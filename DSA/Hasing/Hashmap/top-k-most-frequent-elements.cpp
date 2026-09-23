#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){

    int n,k;
    cin>>n>>k;
    vector<int> m;
    for(int i=0; i<n;i++){
        int temp;
        cin>>temp;
        m.push_back(temp);     //input of array its size and k ois taken

    }
    map<int,int> mp;
    int count=0;
    for(int i=0;i<n;i++){
        if(mp[m[i]]==0){
            count++;             //size of the map is stored
        }
        mp[m[i]]++;             //frequency of ech elment is mapped using hashmap
    }
    vector<pair<int,int>> p;
    map<int,int> :: iterator it;
    for(it=mp.begin();it!=mp.end();it++){           //vector of pairs is created for sorting the elments on the basis of their frequencies
        pair<int,int> x;
        x.first=(it->second);                        //for sorting on frequencies mappings are reversed and then stored
        x.second=(it->first);
        p.push_back(x);
        // cout<<x.first<<"->"<<x.second<<endl;
        // count++;
    }

    sort(p.begin(), p.end(), greater<pair<int,int>>());             //sorted in decreasing order of the frequencies
    // for(int i=0;i<count;i++){
    //     cout<<p[i].first<<"->"<<p[i].second<<endl;
    // }
    int i=0;
    while(i<count){
        cout<<p[i].second<<endl;                              //elments are printed stored as 2nd element in the pairs with their frequencies
        if(i==k){                                             //break after printing k+l most frequent elments.
            break;
        }
        i++;
    }
    return 0;

}