#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// Using Directly Tabulation technique without recursion-----------------------------

// M1--
int countSquares(int n, int m, vector<vector<int>> &arr) {
    // Write your code here.
    vector<vector<int>> dp(n, vector<int>(m, 0));
    int sum=0;
    for(int j=0;j<m;j++) dp[0][j]=arr[0][j], sum+=dp[0][j];
    for(int i=1;i<n;i++) dp[i][0]=arr[i][0], sum+=dp[i][0];

    for(int i=1;i<n;i++){
        for(int j=1;j<m;j++){
            if(arr[i][j]==0) dp[i][j]=0;
            else {
                dp[i][j] = 1 + min(dp[i-1][j], min(dp[i-1][j-1], dp[i][j-1]));
                sum+=dp[i][j];             
            }
        }
    }
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<m;j++){
    //         sum+=dp[i][j];
    //     }
    // }
    return sum;
}



// M2--
int countSquares(int n, int m, vector<vector<int>> &arr) {
    // Write your code here.
    vector<vector<int>> dp(n, vector<int>(m, 0));
    int sum=0;
    for(int j=0;j<m;j++) dp[0][j]=arr[0][j];
    for(int i=0;i<n;i++) dp[i][0]=arr[i][0];

    for(int i=1;i<n;i++){
        for(int j=1;j<m;j++){
            if(arr[i][j]==0) dp[i][j]=0;
            else {
                dp[i][j] = 1 + min(dp[i-1][j], min(dp[i-1][j-1], dp[i][j-1]));      
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            sum+=dp[i][j];
        }
    }
    return sum;
}



//  T.C --> O(N*M)
//  S.C --> O(N*M)

int main(){
    return 0;
}