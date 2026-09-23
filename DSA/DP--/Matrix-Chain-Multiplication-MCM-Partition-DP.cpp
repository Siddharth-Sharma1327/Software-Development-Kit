#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Through Recursion------------------------------
int f(int i, int j, vector<int> &arr){

    if(i==j) return 0;

    int mini=1e9;
    for(int k=i;k<j;k++){

        int step = arr[i-1]*arr[k]*arr[j] + f(i, k, arr) + f(k+1, j, arr);
        mini = min(mini, step);
    }

    return  mini;

}

int matrixMultiplication(vector<int> &arr, int N)
{
    // Write your code here.
    return f(1, N-1, arr);
}






// Through Memoisation---------------------------
int f(int i, int j, vector<int> &arr, vector<vector<int>> &dp){

    if(i==j) return 0;
    if(dp[i][j]!=-1) return dp[i][j];
    int mini=1e9;
    for(int k=i;k<j;k++){

        int step = arr[i-1]*arr[k]*arr[j] + f(i, k, arr, dp) + f(k+1, j, arr, dp);
        mini = min(mini, step);
    }

    return dp[i][j] = mini;

}

int matrixMultiplication(vector<int> &arr, int N)
{
    // Write your code here.
    vector<vector<int>> dp(N, vector<int>(N, -1));
    return f(1, N-1, arr, dp);
}






// Through Tabulation-------------------------------------
int matrixMultiplication(vector<int> &arr, int N)
{
    // Write your code here.
    vector<vector<int>> dp(N+1, vector<int>(N, 0));
    // return f(1, N-1, arr, dp);
    for(int i=0;i<N;i++) dp[i][i]=0;

    for(int i=N-1;i>=1;i--){
        for(int j=i+1;j<=N-1;j++){
            int mini=1e9;
            for(int k=i;k<j;k++){
                int step = arr[i-1]*arr[k]*arr[j] + dp[i][k] + dp[k+1][j];
                mini = min(mini, step);
                dp[i][j] = mini;
            }
            
        }
    }

    return dp[1][N-1];
}




int main(){
    return 0;
}