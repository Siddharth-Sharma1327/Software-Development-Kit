#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// Through MY Method-----(Partition-Dp)-------
// Through Recursion--
int f(int i, int j, string &str){

    if(i>j) return 0;
    string s1 = str.substr(i, j-i+1);
    reverse(s1.begin(), s1.end());
    if(str.substr(i, j-i+1)==s1) return 0;

    int mini=INT_MAX;
    for(int k=i;k<j;k++){
        int cuts = 1 + f(i, k, str) + f(k+1, j, str);
        mini = min(mini, cuts);
    }

    return mini;

}

int palindromePartitioning(string str) {
    // Write your code here
    int n = str.length();
    return f(0, n-1, str);
}

// Through Memoisatoion--
int f(int i, int j, string &str, vector<vector<int>> &dp){

    if(i>j) return 0;
    if(dp[i][j]!=-1) return dp[i][j];
    string s1 = str.substr(i, j-i+1);
    reverse(s1.begin(), s1.end());
    if(str.substr(i, j-i+1)==s1) return 0;

    
    int mini=INT_MAX;
    for(int k=i;k<j;k++){
        int cuts = 1 + f(i, k, str, dp) + f(k+1, j, str, dp);
        mini = min(mini, cuts);
    }

    return dp[i][j] = mini;

}

int palindromePartitioning(string str) {
    // Write your code here
    int n = str.length();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return f(0, n-1, str, dp);
}












// Through Striver Method------------------(Front Partition)------

// Through Recursion------------------------
bool isPalindrome(int i, int j, string &s){

    while(i<j){
        if(s [i]!=s[j]) return false;
        i++;
        j--;
    }
    return true;
}


int f(int i, int n, string &str){

    if(i==n) return 0;
    int minCost = INT_MAX;

    for(int j=i;j<n;j++){
        if(isPalindrome(i, j, str)){
            int cost = 1 + f(j+1, n, str);
            minCost = min(minCost, cost);
        }
    }

    return minCost;

}


int palindromePartitioning(string str) {
    // Write your code here
    int n = str.length();
    return f(0, n, str)-1;

}






// Through Memoisation---------------------------------
bool isPalindrome(int i, int j, string &s){

    while(i<j){
        if(s [i]!=s[j]) return false;
        i++;
        j--;
    }
    return true;
}


int f(int i, int n, string &str, vector<int> &dp){

    if(i==n) return 0;
    if(dp[i]!=-1) return dp[i];

    int minCost = INT_MAX;

    for(int j=i;j<n;j++){
        if(isPalindrome(i, j, str)){
            int cost = 1 + f(j+1, n, str, dp);
            minCost = min(minCost, cost);
        }
    }

    return dp[i] = minCost;

}


int palindromePartitioning(string str) {
    // Write your code here
    int n = str.length();
    vector<int> dp(n, -1);
    return f(0, n, str, dp)-1;

}






// Through Tabulation----------------------
bool isPalindrome(int i, int j, string &s){

    while(i<j){
        if(s [i]!=s[j]) return false;
        i++;
        j--;
    }
    return true;
}


int palindromePartitioning(string str) {
    // Write your code here
    int n = str.length();
    vector<int> dp(n+1, 0);
    // return f(0, n, str, dp)-1;

    for(int i=n-1; i>=0;i--){

        int minCost = INT_MAX;
        for(int j=i;j<n;j++){
            if(isPalindrome(i, j, str)){
                int cost = 1 + dp[j+1];
                minCost = min(minCost, cost);
            }
        }

        dp[i] = minCost;
    }

    return dp[0]-1;

}

int main(){
    return 0;
}