#include<iostream>
#include<bits/stdc++.h>
using namespace std;



// Through Recursion---------------------
class Solution {
public:
    
    int f(int i, int n, vector<int> &arr, int k){
        
        if(i==n) return 0;
        
        int l=0;
        int maxi=INT_MIN;
        int maxEle=INT_MIN;
        for(int j=0;j<k;j++){
            
            if(i+j < n){
                l++;
                maxEle = max(maxEle, arr[i+j]);
                int sum = (l)*maxEle + f(i+j+1, n, arr, k);
                maxi = max(maxi, sum);
                }else continue;
        }
        
        return maxi;
    }
    
    
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int n = arr.size();
        return f(0, n, arr, k);
    }
};
// T.C. : O(exponential)  S.C. : O(n)




// Through Memoisation---------------------
class Solution {
public:
    
    int f(int i, int n, vector<int> &arr, int k, vector<int> &dp){
        
        if(i==n) return 0;
        
        if(dp[i]!=-1) return dp[i];
        int l=0;
        int maxi=INT_MIN;
        int maxEle=INT_MIN;
        for(int j=0;j<k;j++){
            
            if(i+j < n){
                l++;
                maxEle = max(maxEle, arr[i+j]);
                int sum = (l)*maxEle + f(i+j+1, n, arr, k, dp);
                maxi = max(maxi, sum);
                }else continue;
        }
        
        return dp[i] = maxi;
    }
    
    
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int n = arr.size();
        vector<int> dp(n, -1);
        return f(0, n, arr, k, dp);
    }
};
// T.C. : O(n*k)  S.C. : O(n) for recursion stack + O(n) for dp array = O(n)





// Through Tabulation------------------------
class Solution {
public:
  
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int n = arr.size();
        vector<int> dp(n+1, 0);
        // return f(0, n, arr, k, dp);
        
        for(int i=n-1;i>=0;i--){
            int l=0;
            int maxi=INT_MIN;
            int maxEle=INT_MIN;
            for(int j=0;j<k;j++){
                if(i+j < n){
                    l++;
                    maxEle = max(maxEle, arr[i+j]);
                    int sum = (l)*maxEle + dp[i+j+1];
                    maxi = max(maxi, sum);
                    }else continue;
            }

            dp[i] = maxi;
        }
        
        return dp[0];
        
    }
};
// T.C. : O(n*k)  S.C. : O(n) for dp array = O(n)

int main(){
    return 0;
}