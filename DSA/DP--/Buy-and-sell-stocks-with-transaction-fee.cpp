#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Through Recurison-----------------------------
int f(int i, vector<int> &prices, int buy, int n, int fee){

    if(i>=n) return 0;

    if(buy){
        return max(-prices[i]+f(i+1,prices,0, n, fee), f(i+1, prices, 1, n, fee));
    }else {
        return max(prices[i] + f(i+1, prices, 1, n, fee)-fee, f(i+1, prices, 0, n, fee));
    }
}
int maximumProfit(int n, int fee, vector<int> &prices) {
    // Write your code here.
    return f(0, prices, 1, n, fee);
}



// Through Memoisation-----------------------------------
int f(int i, vector<int> &prices, int buy, int n, int fee, vector<vector<int>> &dp){

    if(i>=n) return 0;
    if(dp[i][buy]!=-1) return dp[i][buy];
    if(buy){ 
        return dp[i][buy] = max(-prices[i]+f(i+1,prices,0, n, fee, dp), f(i+1, prices, 1, n, fee, dp));
    }else {
        return dp[i][buy] = max(prices[i] + f(i+1, prices, 1, n, fee, dp)-fee, f(i+1, prices, 0, n, fee, dp));
    }
}
int maximumProfit(int n, int fee, vector<int> &prices) {
    // Write your code here.
    vector<vector<int>> dp(n,vector<int>(2, -1));
    return f(0, prices, 1, n, fee, dp);
}




// Through Tabulation----------------------------------
int maximumProfit(int n, int fee, vector<int> &prices) {
    // Write your code here.
    vector<vector<int>> dp(n+1,vector<int>(2, 0));
    // return f(0, prices, 1, n, fee, dp);

    dp[n][0]=dp[n][1]=0;

    for(int i=n-1;i>=0;i--){
        for(int j=0;j<2;j++){
            if(j){ 
                dp[i][j] = max(-prices[i]+dp[i+1][0], dp[i+1][1]);
            }else {
                dp[i][j] = max(prices[i] + dp[i+1][1]-fee, dp[i+1][0]);
            }

        }
    }

    return dp[0][1];
}





// Through Space Optimisation--------------------------------
int maximumProfit(int n, int fee, vector<int> &prices) {
    // Write your code here.
    // vector<vector<int>> dp(n+1,vector<int>(2, 0));
    // return f(0, prices, 1, n, fee, dp);
    vector<int> next(2, 0), cur(2, 0);
    next[0]=next[1]=0;

    for(int i=n-1;i>=0;i--){
        for(int j=0;j<2;j++){
            if(j){ 
                cur[j] = max(-prices[i]+next[0], next[1]);
            }else {
                cur[j] = max(prices[i] + next[1]-fee, next[0]);
            }

        }
        next = cur;
    }

    return next[1];
}



int main(){
    return 0;
}