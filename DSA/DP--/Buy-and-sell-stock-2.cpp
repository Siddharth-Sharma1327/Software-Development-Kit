#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Through Recursion--------------
long f(int i, long *values, int buy, int n){        //going from down-to-top

    if(i==n) return 0;

    if(buy){
        long buy = -values[i]+f(i+1,values,0, n);
        long notBuy = f(i+1, values, 1, n);
        return max(buy, notBuy);
    }else {
        long sell = values[i] + f(i+1, values, 1, n);
        long notSell = f(i+1, values, 0, n);
        return max(sell, notSell);
    }

}

long getMaximumProfit(long *values, int n)
{
    //Write your code here

    return f(0, values, 1, n);
}




// Through Memoisation--------------------
long f(int i, long *values, int buy, int n, vector<vector<long>> &dp){

    if(i==n) return 0;

    if(dp[i][buy]!=-1) return dp[i][buy];
    if(buy){
        long Bought = -values[i]+f(i+1,values,0, n, dp);
        long notBuy = f(i+1, values, 1, n, dp);
        return dp[i][buy] = max(Bought, notBuy);
    }else {
        long sell = values[i] + f(i+1, values, 1, n, dp);
        long notSell = f(i+1, values, 0, n, dp);
        return dp[i][buy] = max(sell, notSell);
    }

}

long getMaximumProfit(long *values, int n)
{
    //Write your code here
    vector<vector<long>> dp(n, vector<long>(2, -1));
    return f(0, values, 1, n, dp);
}





// Through Tabulation------------------
long getMaximumProfit(long *values, int n)
{
    //Write your code here
    vector<vector<long>> dp(n+1, vector<long>(2, 0));
    // return f(0, values, 1, n, dp);

    dp[n][0]=dp[n][1]=0;

    for(int i=n-1;i>=0;i--){
        for(int j=0;j<=1;j++){
            if(j){
                long Bought = -values[i]+dp[i+1][0];
                long notBuy = dp[i+1][1];
                dp[i][j] = max(Bought, notBuy);
            }else {
                long sell = values[i] + dp[i+1][1];
                long notSell = dp[i+1][0];
                dp[i][j] = max(sell, notSell);
            }
        }
    }
    return dp[0][1];
}




// Through Space Optimisation------------------------
long getMaximumProfit(long *values, int n)
{
    //Write your code here
    // vector<vector<long>> dp(n+1, vector<long>(2, 0));
    // return f(0, values, 1, n, dp);
    vector<long> next(2, 0), cur(2, 0);

    next[0]=next[1]=0;

    for(int i=n-1;i>=0;i--){
        for(int j=0;j<=1;j++){
            if(j){
                long Bought = -values[i]+next[0];
                long notBuy = next[1];
                cur[j] = max(Bought, notBuy);
            }else {
                long sell = values[i] + next[1];
                long notSell = next[0];
                cur[j] = max(sell, notSell);
            }
        }
        next=cur;
    }
    return next[1];
}




int main(){
    return 0;
}