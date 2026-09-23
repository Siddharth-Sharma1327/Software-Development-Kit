#include<iostream>
#include<bits/stdc++.h>
using namespace std;


//Through Recursion---------
#include <bits/stdc++.h> 

int f(int ind, vector<int> &num, int tar){
    
    if(tar==0) return 0;
    if(ind==-1) return -1;;
    
    int notTake = f(ind-1, num, tar);
    int take = INT_MAX;
    if(tar>=num[ind]) take = 1 + f(ind, num, tar-num[ind]);
    
    if(notTake>=0 && take>0) return min(notTake, take);
    else if(notTake==-1 && (take==0 || take==INT_MAX)) return -1;
    else return max(notTake, take);
}
int minimumElements(vector<int> &num, int x)
{
    // Write your code here.
    int n = num.size();
    return f(n-1, num, x);
}


//Through Memoisation----------

int f(int ind, vector<int> &num, int tar, vector<vector<int>> &dp){
    
    if(tar==0) return 0;
    if(ind==-1) return -1;
    
    if(dp[ind][tar]!=-1) return dp[ind][tar];
    int notTake = f(ind-1, num, tar, dp);
    int take = INT_MAX;
    if(tar>=num[ind]) take = 1 + f(ind, num, tar-num[ind], dp);
    
    if(notTake>=0 && take>0) return dp[ind][tar] = min(notTake, take);
    else if(notTake==-1 && (take==0 || take==INT_MAX)) return dp[ind][tar] = -1;
    else return dp[ind][tar] = max(notTake, take) ;
}
int minimumElements(vector<int> &num, int x)
{
    // Write your code here.
    int n = num.size();
    vector<vector<int>> dp(n, vector<int>(x+1, -1));
    
    return f(n-1, num, x, dp);
}


//Through Tabulation---------------
int minimumElements(vector<int> &num, int x)
{
    // Write your code here.
    int n = num.size();
    vector<vector<int>> dp(n, vector<int>(x+1, 0));
    
//     return f(n-1, num, x, dp);
    
//     for(int i=0;i<n;i++) dp[i][0]=0;
        
        for(int ind=0;ind<n;ind++){
            for(int tar=1;tar<=x;tar++){
                int notTake=-1;
//                 if(ind==0) int notTake=-1;
                if(ind!=0) notTake = dp[ind-1][tar];
                int take = INT_MAX;
                if(tar>=num[ind]) take = 1 + dp[ind][tar-num[ind]];

                if(notTake>=0 && take>0) dp[ind][tar] = min(notTake, take);
                else if(notTake==-1 && (take==0 || take==INT_MAX)) dp[ind][tar] = -1;
                else dp[ind][tar] = max(notTake, take) ;
                
            }
        }
       return dp[n-1][x];
}



//Through Space Optimisation--------------(not possible for using single row--can verify)
int minimumElements(vector<int> &num, int x)
{
    // Write your code here.
    int n = num.size();
//     vector<vector<int>> dp(n, vector<int>(x+1, 0));
    vector<int> prev(x+1, 0), cur(x+1, 0);
  
        for(int ind=0;ind<n;ind++){
            for(int tar=1;tar<=x;tar++){
                int notTake=-1;
                if(ind!=0) notTake = prev[tar];
                int take = INT_MAX;
                if(tar>=num[ind]) take = 1 + cur[tar-num[ind]];

                if(notTake>=0 && take>0) cur[tar] = min(notTake, take);
                else if(notTake==-1 && (take==0 || take==INT_MAX)) cur[tar] = -1;
                else cur[tar] = max(notTake, take) ;
                
            }
            prev=cur;
        }
       return prev[x];
}
int main(){
    return 0;
}