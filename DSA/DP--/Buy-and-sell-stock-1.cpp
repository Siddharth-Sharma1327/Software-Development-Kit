#include<iostream>
#include<bits/stdc++.h>
using namespace std;

//--------------------------------------------------
int maximumProfit(vector<int> &prices){
    // Write your code here.
    // int n = prices.size();
    int mn=INT_MAX;
    int ans=INT_MIN;
    for(int i=0;i<prices.size();i++){
        mn=min(mn, prices[i]);
        ans=max(ans, prices[i]-mn);
    }
    return ans;
}
int main(){
    return 0;
}