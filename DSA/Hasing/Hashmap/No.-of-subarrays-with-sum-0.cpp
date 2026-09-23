#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){

    int n;
    cin>>n;
    vector<int> m(n);

    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        m.push_back(x);
    }

    map<int,int> mp;
    int prefsum=0;
    int ans=0;
    // mp[0]++;
    // mp[prefsum]++;
    for(int i=0;i<n;i++){
        prefsum+=m[i];
        mp[prefsum]++;
    }

    map<int,int> :: iterator it;
   
    for(it=mp.begin(); it!=mp.end(); it++){
        int c=(it->second);
         ans+= ((c*(c-1))/2);
        if(it->first ==0){
           ans+=(it->second);
        }
    }
    cout<<ans<<endl;

    return 0;
}