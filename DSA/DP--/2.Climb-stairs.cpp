#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// recursion--
#include <bits/stdc++.h> 

int f(int i){
    if(i<=1) return 1;

    int prev1 = f(i-1);
    int prev2 = f(i-2);

    return prev1+prev2;
}

int countDistinctWays(int nStairs) {
    //  Write your code here.
    return f(nStairs);
}


// memoisation--
#include <bits/stdc++.h> 

int f(int i, vector<int> &dp){
    if(i<=1) return 1;
    if(dp[i]!=-1) return dp[i];
    int prev1 = f(i-1, dp);
    int prev2 = f(i-2, dp);

    return dp[i] = prev1+prev2;
}

int countDistinctWays(int nStairs) {
    //  Write your code here.
    long long mod=1e9+7;
    vector<long long> dp(nStairs+1, 0);
    return f(nStairs)%mod;
}

// tabulation--
int countDistinctWays(int nStairs) {
    //  Write your code here.
    long long mod=1e9+7;
    vector<long long> dp(nStairs+1, 0);
    dp[0]=1,dp[1]=1;
    // return f(nStairs, dp);
    for(int i=2;i<=nStairs;i++){
        long prev1 = dp[i-1];
        long prev2 = dp[i-2];

        dp[i] = (prev1+prev2)%mod;
    }
    return dp[nStairs]%mod;
}


// Space optimisation--
int countDistinctWays(int nStairs) {
    //  Write your code here.
    long long mod=1e9+7;
    // vector<long long> dp(nStairs+1, 0);
    long long prev2=1,prev1=1,curi;
    // return f(nStairs, dp);
    for(int i=2;i<=nStairs;i++){
        curi = (prev1+prev2)%mod;
        prev2=prev1;
        prev1=curi;
    }
    return prev1%mod;
}

int main(){
    return 0;
}