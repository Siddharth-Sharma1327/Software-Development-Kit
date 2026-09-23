#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// CODE:--------------------
#include <bits/stdc++.h> 
int findNumberOfLIS(vector<int> &arr)
{
    // Write your code here.
    int n = arr.size();
    vector<int> dp(n, 1), cnt(n, 1);
    int maxi=INT_MIN;
    int ans=0;
    for(int i=0;i<n;i++){
        for(int prev=0;prev<i;prev++){
            if(arr[prev]<arr[i] && dp[prev]+1>dp[i]){
                cnt[i]=cnt[prev];
                dp[i] = dp[prev]+1;
            }else if(arr[prev]<arr[i] && dp[prev]+1==dp[i]){
                cnt[i]+=cnt[prev];
            }
        }
        if(dp[i]>maxi){
            ans=cnt[i];
            maxi = max(maxi, dp[i]);
        }else if(dp[i]==maxi){
            ans+=cnt[i];
        }
        
    }

    return ans;
}
int main(){
    return 0;
}