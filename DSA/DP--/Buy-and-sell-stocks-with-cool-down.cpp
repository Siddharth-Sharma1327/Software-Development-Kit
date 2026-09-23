#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// Through Recursion------------------
#include<iostream>
#include <bits/stdc++.h> 
using namespace std;
int f(int i, vector<int> &prices, int buy, int n){

    if(i>=n) return 0;

    if(buy){
        int buy = -prices[i]+f(i+1,prices,0, n);
        int notBuy = f(i+1, prices, 1, n);
        return max(buy, notBuy);
    }else {
        int sell = prices[i] + f(i+2, prices, 1, n);
        int notSell = f(i+1, prices, 0, n);
        return max(sell, notSell);
    }
}
int stockProfit(vector<int> &prices){
    // Write your code here.
    int n = prices.size();
    return f(0, prices, 1, n);
} 



// Through Memoisation---------------------------
int f(int i, vector<int> &prices, int buy, int n, vector<vector<int>> &dp){

    if(i>=n) return 0;

    if(dp[i][buy]!=-1) return dp[i][buy];
    if(buy){
        return dp[i][buy] = max(-prices[i]+f(i+1,prices,0, n, dp), f(i+1, prices, 1, n, dp));
    }else {

        return dp[i][buy] = max(prices[i] + f(i+2, prices, 1, n, dp), f(i+1, prices, 0, n, dp));
    }
}
int stockProfit(vector<int> &prices){
    // Write your code here.
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(2, -1));
    return f(0, prices, 1, n, dp);
} 





// Through Tabulation----------------------------------
int stockProfit(vector<int> &prices){
    // Write your code here.
    int n = prices.size();
    vector<vector<int>> dp(n+2, vector<int>(2, 0));
    // return f(0, prices, 1, n, dp);

    dp[n][0]=dp[n][1]=dp[n+1][0]=dp[n+1][1];

    for(int i=n-1;i>=0;i--){
        for(int j=0;j<2;j++){
            if(j){
                dp[i][j] = max(-prices[i]+dp[i+1][0], dp[i+1][1]);
            }else {

                dp[i][j] = max(prices[i] + dp[i+2][1], dp[i+1][0]);
            }

        }
    }

    return dp[0][1];
} 






// Through Space Optimisation-----------------------------------
int stockProfit(vector<int> &prices){
    // Write your code here.
    int n = prices.size();
    // vector<vector<int>> dp(n+2, vector<int>(2, 0));
    // return f(0, prices, 1, n, dp);
    vector<int> next1(2, 0), cur(2, 0), next2(2, 0);

    next1[0]=next1[1]=next2[0]=next2[1]=0;

    for(int i=n-1;i>=0;i--){
        for(int j=0;j<2;j++){
            if(j){
                cur[j] = max(-prices[i]+next1[0], next1[1]);
            }else {

                cur[j] = max(prices[i] + next2[1], next1[0]);
            }

        }
        next2=next1;
        next1=cur;
    }

    return next1[1];
} 

int main(){
    return 0;
}