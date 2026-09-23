#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// Same solution as that of the subsequences with given difference----- (Same Q--OBSERVE THE PATTERN)
int countPartitions(int n, int d, vector<int> &arr) {
//     // Write your code here.
    int m = (int)(1e9+7);
    int tar=0;
    for(int i=0;i<n;i++) tar+=arr[i];
    int ans=0;
    vector<vector<int>> dp(n, vector<int>(tar+1, 0));

    for(int ind=0;ind<n;ind++){
            for(int target=0;target<=tar;target++){
                
                if(ind==0 && target!=0){
                    dp[ind][target] = (arr[0]==target);
                    continue;
                } 
                else if(ind==0 && target==0){
                    if(arr[0]==0) dp[ind][target] = 2;
                    else dp[ind][target]=1;
                    continue;
                }
                int notTake = dp[ind-1][target];
                int take = 0;
                if(target>=arr[ind]) take=dp[ind-1][target-arr[ind]];

                dp[ind][target] = (take+notTake)%m;
            }
        }
    if(((tar-d)%2) || (tar-d)<0) return 0;   //Imp conditions----------
    else return dp[n-1][(tar-d)/2];
    
}

int targetSum(int n, int target, vector<int>& arr) {

    return countPartitions(n, target, arr);
}


//can also be solved this way but here we will get negative target values...
#include <bits/stdc++.h> 
int f(int ind, int tar, vector<int> &arr){
    
    if(tar==0 && ind==-1) return 1;
    else if(ind==-1) return 0;
    
    int p = f(ind-1, tar-arr[ind], arr);
    int m = f(ind-1, tar+arr[ind], arr);
    
    return p+m;
    
}
int targetSum(int n, int target, vector<int>& arr) {
    // Write your code here.
//     vector<vector<int>> dp(n, vector<int>(target+1, -1));
    return f(n-1, target, arr);
}

int main(){
    return 0;
}