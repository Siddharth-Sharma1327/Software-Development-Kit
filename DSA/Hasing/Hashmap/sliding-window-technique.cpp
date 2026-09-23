#include<iostream>
#include<bits/stdc++.h>

using namespace std;

int main(){
    int n;
    cin>>n;
    int k;
    cin>>k;
    vector<int> m;
    for(int i=0;i<n;i++){
        int temp;
        cin>>temp;
        m.push_back(temp);
    }

    int i=0;
    int ans=INT_MAX;
    int sum=0;
    for(int j=0;j<n;j++){
        sum+=m[j];
        if(j==k-1){
            ans=sum;
        }
        if(j>k-1){
                sum-=m[i];
            i++;
            ans=min(sum,ans);
        }
        
    }

    cout<<ans;
    return 0;
}