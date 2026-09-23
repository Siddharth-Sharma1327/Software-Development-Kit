#include<iostream>
#include<bits/stdc++.h>
using namespace std;

//Through Recursion---------
int f(int ind, vector<int> &weight, vector<int> &value, int maxWeight){
    
    if(ind==0 && weight[0]<=maxWeight) return value[0];
    else if(ind==0) return 0;
    
    int notTake =  f(ind-1, weight, value, maxWeight);
    int take = INT_MIN;
    if(weight[ind]<=maxWeight) take = value[ind] + f(ind-1, weight, value, (maxWeight-weight[ind]));
    
    return max(notTake, take);
}
int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	// Write your code here
    
    return f(n-1, weight, value, maxWeight);
}


//Through Memoisation--------------

int f(int ind, vector<int> &weight, vector<int> &value, int maxWeight, vector<vector<int>> &dp){
    
    if(ind==0 && weight[0]<=maxWeight) return value[0];
    else if(ind==0) return 0;
    if(dp[ind][maxWeight]!=-1) return dp[ind][maxWeight];
    int notTake =  f(ind-1, weight, value, maxWeight, dp);
    int take = INT_MIN;
    if(weight[ind]<=maxWeight) take = value[ind] + f(ind-1, weight, value, (maxWeight-weight[ind]), dp);
    
    return dp[ind][maxWeight] = max(notTake, take);
}
int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	// Write your code here
    vector<vector<int>> dp(n, vector<int>(maxWeight+1, -1));
    return f(n-1, weight, value, maxWeight, dp);
}

//Through Tabulation-------------------
int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	// Write your code here
    vector<vector<int>> dp(n, vector<int>(maxWeight+1, 0));
//     return f(n-1, weight, value, maxWeight, dp);
    
    if(weight[0]<=maxWeight) for(int i=weight[0];i<=maxWeight;i++) dp[0][i]=value[0];
    
    for(int ind=1;ind<n;ind++){
        for(int j=1;j<=maxWeight;j++){
            int notTake =  dp[ind-1][j];
            int take = INT_MIN;
            if(weight[ind]<=j) take = value[ind] + dp[ind-1][j-weight[ind]];

            dp[ind][j] = max(notTake, take);
        }
    }
    
    return dp[n-1][maxWeight];
}


//Through Space Optimisation  (USING TWO ROWS)-----------
int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	// Write your code here

    vector<int> prev(maxWeight+1, 0), cur(maxWeight+1, 0);

    if(weight[0]<=maxWeight) for(int i=weight[0];i<=maxWeight;i++) prev[i]=value[0]; 
    
    for(int ind=1;ind<n;ind++){
        for(int j=1;j<=maxWeight;j++){
            int notTake =  prev[j];
            int take = INT_MIN;
            if(weight[ind]<=j) take = value[ind] + prev[j-weight[ind]];

            cur[j] = max(notTake, take);
        }
        prev=cur;
    }
    
    return prev[maxWeight];
}


//Space Optimisation   (USING SINGLE ROW)------------
int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight) 
{
	// Write your code here
//     vector<vector<int>> dp(n, vector<int>(maxWeight+1, 0));
//     return f(n-1, weight, value, maxWeight, dp);
    vector<int> prev(maxWeight+1, 0), cur(maxWeight+1, 0);
    
//     if(weight[0]<=maxWeight) for(int i=weight[0];i<=maxWeight;i++) dp[0][i]=value[0];
    if(weight[0]<=maxWeight) for(int i=weight[0];i<=maxWeight;i++) prev[i]=value[0]; 
    
    for(int ind=1;ind<n;ind++){
        for(int j=maxWeight;j>=1;j--){        //IDEA---is that we can't do cur[j]=prev[j] as thevalue just above the cur[j] in dp table is used to form the next element in prev row(if cur[j]=prev[j]) so we iterate from right side to left as the values changed in the prev[j] row are not used again for all iterations instead all left elments of prev row are used and these new row is curr row 
            int notTake =  prev[j];
            int take = INT_MIN;
            if(weight[ind]<=j) take = value[ind] + prev[j-weight[ind]];

            prev[j] = max(notTake, take);
        }
//         prev=cur;
    }
    
    return prev[maxWeight];
}
int main(){
    return 0;
}