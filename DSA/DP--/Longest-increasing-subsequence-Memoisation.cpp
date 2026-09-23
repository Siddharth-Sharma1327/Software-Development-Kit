#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Through Recursion------------------------

int f(int arr[],int n, int i, int prevInd){

    if(i>=n) return 0;

    int notTake = f(arr, n, i+1, prevInd);
    int take=0;
    if(prevInd==-1 || arr[i]>arr[prevInd]) take = 1 + f(arr, n, i+1, i);

    return  max(notTake, take);

}

int longestIncreasingSubsequence(int arr[], int n)
{
    // Write Your Code here
    return f(arr, n, 0, -1);
}



// Through Memoisation----------------------(IMP--Gives Runtime error because here we create 10^5 X 10^5 vector which is not possible so gives runtime error---> actual sol is in O(nlogn)
int f(int arr[],int n, int i, int prevInd, vector<vector<int>> &dp){

    if(i>=n) return 0;

    if(dp[i][prevInd+1]!=-1) return dp[i][prevInd+1];
    int notTake = f(arr, n, i+1, prevInd, dp);
    int take=0;
    if(prevInd==-1 || arr[i]>arr[prevInd]) take = 1 + f(arr, n, i+1, i, dp);

    return dp[i][prevInd+1] = max(notTake, take);

}

int longestIncreasingSubsequence(int arr[], int n)
{
    // Write Your Code here
   vector<vector<int>> dp(n, vector<int>(n+1, -1));         //did shifting of index for prevInd
    return f(arr, n, 0, -1, dp);
}





// Through Tabulation-------
int longestIncreasingSubsequence(int arr[], int n)
{
    // Write Your Code here
   vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
    // return f(arr, n, 0, -1, dp);
    for(int j=0;j<=n;j++) dp[n][j]=0;

    for(int i=n-1;i>=0;i--){
        for(int prevInd=-1;prevInd<i;prevInd++){
            int notTake = dp[i+1][prevInd+1];
            int take=0;
            if(prevInd==-1 || arr[i]>arr[prevInd]) take = 1 + dp[i+1][i+1];    //here i+1 is IMPORTANT---------

            dp[i][prevInd+1] = max(notTake, take);
        }
    }

    return dp[0][0];
}




// Through Space Optimisation-----------
int longestIncreasingSubsequence(int arr[], int n)
{
    // Write Your Code here
//    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
    // return f(arr, n, 0, -1, dp);
    vector<int> next(n+1, 0), cur(n+1, 0);
    for(int j=0;j<=n;j++) next[j]=0;

    for(int i=n-1;i>=0;i--){
        for(int prevInd=-1;prevInd<i;prevInd++){
            int notTake = next[prevInd+1];
            int take=0;
            if(prevInd==-1 || arr[i]>arr[prevInd]) take = 1 + next[i+1];

            cur[prevInd+1] = max(notTake, take);
        }
        next=cur;
    }

    return next[0];
}








// THROUGH TABULATION---------------------------------O(N)  Soln---------------
int longestIncreasingSubsequence(int arr[], int n)
{
    // Write Your Code here
    vector<int> dp(n, 1);
    int maxi=INT_MIN;
    for(int i=0;i<n;i++){
        for(int prev=0;prev<i;prev++){
            if(arr[prev]<arr[i]){
                dp[i] = max(dp[i], dp[prev]+1);
            }
        }
        maxi = max(maxi, dp[i]);
    }

    return maxi;
}



// Printing the LIS using tabulation method(--O(N)--)----------------------
int longestIncreasingSubsequence(int arr[], int n)
{
    // Write Your Code here
    vector<int> dp(n, 1), hash(n);
    int maxi=1;
    int lastIndex=0; 
    for(int i=0;i<n;i++){
        hash[i]=i;
        for(int prev=0;prev<i;prev++){
            if(arr[prev]<arr[i] && dp[prev]+1>dp[i]){
                dp[i] = dp[prev]+1;
                hash[i]=prev;
            }
        }
        if(dp[i]>maxi){
            maxi=dp[i];
            lastIndex=i;
        }
    }
    vector<int> temp;
    temp.push_back(arr[lastIndex]);
    while(hash[lastIndex]!=lastIndex){
        lastIndex = hash[lastIndex];
        temp.push_back(arr[lastIndex]);
    }

    reverse(temp.begin(), temp.end());
    for(auto it: temp) cout<<it<<" ";
    cout<<endl;
    return maxi;
}






int main(){
    return 0;
}