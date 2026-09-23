#include<iostream>
#include<bits/stdc++.h>
using namespace std;


//Through Recursion-----------
// #include <bits/stdc++.h> 
int f(int ind, int target, vector<int> &num){
        
        if(ind==-1 && target==0) return 1;         //These are base case for the cases where element can also be considered in the sequence of it is 0 so not returning as target==0...eg(num = {1, 0, 2, 0, 3} , tar==3)
        else if(ind==-1) return 0;
    // if(target==0) return 1;                    //These base conditions given int the video solution
    // if(ind==0) return (num[0]==target);

    int notTake = f(ind-1, target, num);
    int take = 0;
    if(target>=num[ind]) take=f(ind-1, target-num[ind], num);
    
    return take+notTake;
}

int findWays(vector<int> &num, int tar)
{
    // Write your code here.
    int n=num.size();
    return f(n-1, tar, num);
    
}

//Through Memoisation---------
int f(int ind, int target, vector<int> &num, vector<vector<int>> &dp){
        
        if(ind==-1 && target==0) return 1;
        else if(ind==-1) return 0;
//     if(target==0) return 1;
//     if(ind==0) return (num[0]==target);
    if(dp[ind][target]!=-1) return dp[ind][target];
    int notTake = f(ind-1, target, num, dp);
    int take = 0;
    if(target>=num[ind]) take=f(ind-1, target-num[ind], num, dp);
    
    return dp[ind][target] = take+notTake;
}

int findWays(vector<int> &num, int tar)
{
    // Write your code here.
    int n=num.size();
    vector<vector<int>> dp(n, vector<int>(tar+1, -1));
    return f(n-1, tar, num, dp);
    
}


//Through Tabulation----------
int findWays(vector<int> &num, int tar)
{
    // Write your code here.
    int n=num.size();
    vector<vector<int>> dp(n, vector<int>(tar+1, 0));

    for(int ind=0;ind<n;ind++){
            for(int target=0;target<=tar;target++){
                
                if(ind==0 && target!=0){
                    dp[ind][target] = (num[0]==target);
                    continue;
                } 
                else if(ind==0 && target==0){
                    if(num[0]==0) dp[ind][target] = 2;
                    else dp[ind][target]=1;
                    continue;
                }
                int notTake = dp[ind-1][target];
                int take = 0;
                if(target>=num[ind]) take=dp[ind-1][target-num[ind]];

                dp[ind][target] = take+notTake;
            }
        }
    
    return dp[n-1][tar];
    
}

//Through Space Optimisation-----
int findWays(vector<int> &num, int tar)
{
    // Write your code here.
    int n=num.size();
    vector<int> prev(tar+1, 0), cur(tar+1, 0);

    if(num[0]==0) prev[0]=2;
    else prev[0]=1;
    if(num[0]<=tar && num[0]!=0) prev[num[0]]=1;

    for(int ind=1;ind<n;ind++){
            for(int target=0;target<=tar;target++){
                int notTake = prev[target];
                int take = 0;
                if(target>=num[ind]) take=prev[target-num[ind]];

                cur[target] = take+notTake;
            }
        prev=cur;
        }
    
    return prev[tar];
    
}
int main(){
    return 0;
}