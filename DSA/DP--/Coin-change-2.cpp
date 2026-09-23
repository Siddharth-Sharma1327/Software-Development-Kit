#include<iostream>
#include<bits/stdc++.h>
using namespace std;


//Through recursion---------------
#include <bits/stdc++.h> 

long int f(int ind, int *num, int tar, vector<vector<long int>> &dp){
    
    if(tar==0) return 1;
    if(ind==-1) return 0;
    
    if(dp[ind][tar]!=-1) return dp[ind][tar];
    long int notTake = f(ind-1, num, tar, dp);
    long int take=0;
    if(tar>=num[ind]) take = f(ind, num, tar-num[ind], dp);
    
    return dp[ind][tar] =  take+notTake;
}
long int minimumElements(int *num, int x, int n)
{
    vector<vector<long int>> dp(n, vector<long int>(x+1, -1));
    return f(n-1, num, x, dp);
}


long countWaysToMakeChange(int *denominations, int n, int value)
{
    //Write your code here
    return minimumElements(denominations, value, n);
}

//Through Memoisation----------------------
long int f(int ind, int *num, int tar, vector<vector<long int>> &dp){
    
    if(tar==0) return 1;
    if(ind==-1) return 0;
    
    if(dp[ind][tar]!=-1) return dp[ind][tar];
    long int notTake = f(ind-1, num, tar, dp);
    long int take=0;
    if(tar>=num[ind]) take = f(ind, num, tar-num[ind], dp);
    
    return dp[ind][tar] =  take+notTake;
}
long int minimumElements(int *num, int x, int n)
{
    vector<vector<long int>> dp(n, vector<long int>(x+1, -1));
    return f(n-1, num, x, dp);
}


long countWaysToMakeChange(int *denominations, int n, int value)
{
    //Write your code here
    return minimumElements(denominations, value, n);
}


//Through Tabulation--------------
long int minimumElements(int *num, int x, int n)
{
    vector<vector<long int>> dp(n, vector<long int>(x+1, 0));
//     return f(n-1, num, x, dp);
    
    for(int i=0;i<n;i++) dp[i][0]=1;
    
    for(int ind=0;ind<n;ind++){
        for(int tar=1;tar<=x;tar++){
                long int notTake = 0;
                if(ind!=0) notTake = dp[ind-1][tar];
                long int take=0;
                if(tar>=num[ind]) take = dp[ind][tar-num[ind]];
                dp[ind][tar] =  take+notTake;
        }
    }
    return dp[n-1][x];
}


long countWaysToMakeChange(int *denominations, int n, int value)
{
    //Write your code here
    return minimumElements(denominations, value, n);
}


//Through Space Optimisation-------------------
long int minimumElements(int *num, int x, int n)
{
//     vector<vector<int>> dp(n, vector<int>(x+1, 0));
//     return f(n-1, num, x, dp);
    vector<long int> prev(x+1, 0), cur(x+1, 0);
    prev[0]=cur[0]=1;
//     for(int i=0;i<n;i++) dp[i][0]=1;
    
    for(int ind=0;ind<n;ind++){
        for(int tar=1;tar<=x;tar++){
                long int notTake = 0;
                if(ind!=0) notTake = prev[tar];
                long int take=0;
                if(tar>=num[ind]) take = cur[tar-num[ind]];
                cur[tar] =  take+notTake;
        }
        prev=cur;
    }
    return prev[x];
}


long countWaysToMakeChange(int *denominations, int n, int value)
{
    //Write your code here
    return minimumElements(denominations, value, n);
}
int main(){
    return 0;
}