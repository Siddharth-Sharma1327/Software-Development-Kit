#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// Through Recursion-------------
int f(int i, int buy, vector<int> &prices, int n, int cnt){

    if(cnt==0 || i==n) return 0;

    if(buy){
        return max((-prices[i]+f(i+1, 0, prices, n, cnt)), f(i+1, 1,prices, n, cnt));
    }else {
        return max((prices[i]+f(i+1, 1,prices, n, cnt-1)), f(i+1, 0, prices, n, cnt));
    }
}

int maxProfit(vector<int>& prices, int n)
{
    // Write your code here.
    return f(0, 1, prices, n, 2);
}




// Through Memoisation----------------

int f(int i, int buy, vector<int> &prices, int n, int cnt, vector<vector<vector<int>>> &dp){

    if(cnt==0 || i==n) return 0;

    if(dp[i][buy][cnt-1]!=-1) return dp[i][buy][cnt-1];
    if(buy){
        return dp[i][buy][cnt-1] = max((-prices[i]+f(i+1, 0, prices, n, cnt, dp)), f(i+1, 1,prices, n, cnt, dp));
    }else {
        return dp[i][buy][cnt-1] = max((prices[i]+f(i+1, 1,prices, n, cnt-1, dp)), f(i+1, 0, prices, n, cnt, dp));
    }
}

int maxProfit(vector<int>& prices, int n)
{
    // Write your code here.
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(2, -1)));
    return f(0, 1, prices, n, 2, dp);
}





// Through Tabulation----------------------
int maxProfit(vector<int>& prices, int n)
{
    // Write your code here.
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(2, vector<int>(3, 0)));
    // return f(0, 1, prices, n, 2, dp);

    dp[n][0][1]=dp[n][1][1]=dp[n][0][2]=dp[n][1][2]=0;

    for(int i=n-1;i>=0;i--){
        for(int j=0;j<2;j++){
            for(int cnt=1;cnt<=2;cnt++){
               
                if(j){
                    dp[i][j][cnt] = max((-prices[i]+dp[i+1][0][cnt]), dp[i+1][1][cnt]);
                }else {
                    dp[i][j][cnt] = max((prices[i]+dp[i+1][1][cnt-1]), dp[i+1][0][cnt]);
                }
            }
        }
    }

    return dp[0][1][2];
}



// Through Space Optimisation------------------------
int maxProfit(vector<int>& prices, int n)
{
    // Write your code here.
    // vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(2, vector<int>(3, 0)));
    vector<vector<int>> next(2, vector<int>(3, 0)), cur(2, vector<int>(3, 0));
    // return f(0, 1, prices, n, 2, dp);

    next[0][1]=next[1][1]=next[0][2]=next[1][2]=0;

    for(int i=n-1;i>=0;i--){
        for(int j=0;j<2;j++){
            for(int cnt=1;cnt<=2;cnt++){
               
                if(j){
                    cur[j][cnt] = max((-prices[i]+next[0][cnt]), next[1][cnt]);
                }else {
                    cur[j][cnt] = max((prices[i]+next[1][cnt-1]), next[0][cnt]);
                }
            }
        }
        next=cur;
    }

    return next[1][2];
}
int main(){
    return 0;
}