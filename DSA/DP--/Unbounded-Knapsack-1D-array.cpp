#include<iostream>
#include<bits\stdc++.h>
using namespace std;

//Through Recursion--------------
#include <bits/stdc++.h> 

int f(int ind, int w, vector<int> &profit, vector<int> &weight){
    
    if(w==0 || ind<0) return 0;

    int notTake = f(ind-1, w, profit, weight);
    int take=0;
    if(w>=weight[ind]) take = profit[ind] + f(ind,w-weight[ind],profit,weight);

    return max(notTake,take);
}
int unboundedKnapsack(int n, int w, vector<int> &profit, vector<int> &weight)
{
    // Write Your Code Here.
    return f(n-1, w, profit, weight);
}

//Through Memoisation---------------
#include <bits/stdc++.h> 

int f(int ind, int w, vector<int> &profit, vector<int> &weight, vector<vector<int>> &dp){
    
    if(w==0 || ind<0) return 0;
    if(dp[ind][w]!=-1) return dp[ind][w];
    int notTake = f(ind-1, w, profit, weight, dp);
    int take=0;
    if(w>=weight[ind]) take = profit[ind] + f(ind,w-weight[ind],profit,weight,dp);

    return dp[ind][w] = max(notTake,take);
}
int unboundedKnapsack(int n, int w, vector<int> &profit, vector<int> &weight)
{
    // Write Your Code Here.
    // return f(n-1, w, profit, weight);
    vector<vector<int>> dp(n, vector<int>(w+1, -1));
    return f(n-1, w, profit, weight, dp);
}



//Through Tabulation------------------
int unboundedKnapsack(int n, int w, vector<int> &profit, vector<int> &weight)
{
    // Write Your Code Here.
    // return f(n-1, w, profit, weight);
    vector<vector<int>> dp(n, vector<int>(w+1, 0));
    // return f(n-1, w, profit, weight, dp);

    for(int i=0;i<n;i++) dp[i][0]=0;

    for(int ind=0;ind<n;ind++){
        for(int j=1;j<=w;j++){
            int notTake = 0;
            if(ind!=0) notTake = dp[ind-1][j];
            int take=0;
            if(j>=weight[ind]) take = profit[ind] + dp[ind][j-weight[ind]];

            dp[ind][j] = max(notTake,take);
        }
    }
    return dp[n-1][w];
}



//Through Space Optimisation-----------
int unboundedKnapsack(int n, int w, vector<int> &profit, vector<int> &weight)
{
    // Write Your Code Here.
    // return f(n-1, w, profit, weight);
    // vector<vector<int>> dp(n, vector<int>(w+1, 0));
    // return f(n-1, w, profit, weight, dp);
    vector<int> prev(w+1, 0),cur(w+1,0);

    // for(int i=0;i<n;i++) dp[i][0]=0;

    for(int ind=0;ind<n;ind++){
        for(int j=1;j<=w;j++){
            int notTake = 0;
            if(ind!=0) notTake = prev[j];
            int take=0;
            if(j>=weight[ind]) take = profit[ind] + cur[j-weight[ind]];

            cur[j] = max(notTake,take);
        }
        prev=cur;
    }
    return prev[w];
}



//Through Space Optimisation Using Single Row------------(Trick to convert two row space optimistaion to single row optimisation)
int unboundedKnapsack(int n, int w, vector<int> &profit, vector<int> &weight)
{
    // Write Your Code Here.
    // return f(n-1, w, profit, weight);
    // vector<vector<int>> dp(n, vector<int>(w+1, 0));
    // return f(n-1, w, profit, weight, dp);
    vector<int> prev(w+1, 0);
    // cur(w+1,0);

    // for(int i=0;i<n;i++) dp[i][0]=0;

    for(int ind=0;ind<n;ind++){
        for(int j=1;j<=w;j++){
            int notTake = 0;
            if(ind!=0) notTake = prev[j];
            int take=0;
            if(j>=weight[ind]) take = profit[ind] + prev[j-weight[ind]];

            prev[j] = max(notTake,take);
        }
        // prev=cur;
    }
    return prev[w];
}
int main(){
    return 0;
}