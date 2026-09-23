#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int m = (int)(1e9+7);
// Through Recursion-----------------------------(consider testcase given in the video--will understand)
int f(int i, int j, string &t, string &s){

    if(j<0) return 1;
    if(i<0) return 0;

    if(t[i]==s[j]) return f(i-1,j-1,t,s) + f(i-1,j,t,s);
    else return f(i-1,j,t,s);
}

int subsequenceCounting(string &t, string &s, int lt, int ls) {
    // Write your code here.
    return f(lt-1, ls-1, t, s);
}



// Through Memoisation------------------------------
int f(int i, int j, string &t, string &s, vector<vector<int>> &dp){

    if(j<0) return 1;
    if(i<0) return 0;

    if(dp[i][j]!=-1) return dp[i][j];
    if(t[i]==s[j]) return dp[i][j] = (f(i-1,j-1,t,s, dp) + f(i-1,j,t,s, dp))%m;
    else return dp[i][j] = f(i-1,j,t,s, dp)%m;
}

int subsequenceCounting(string &t, string &s, int lt, int ls) {
    // Write your code here.
    vector<vector<int>> dp(lt, vector<int>(ls, -1));
    return f(lt-1, ls-1, t, s, dp);
} 




// Through Tabulatin-------------------------------
int subsequenceCounting(string &t, string &s, int lt, int ls) {
    // Write your code here.
    vector<vector<int>> dp(lt+1, vector<int>(ls+1, 0));
    // return f(lt-1, ls-1, t, s, dp)%m;

    for(int i=0;i<=lt;i++) dp[i][0]=1;

    for(int i=1;i<=lt;i++){
        for(int j=1;j<=ls;j++){

            if(t[i-1]==s[j-1]) dp[i][j] = (dp[i-1][j-1] + dp[i-1][j])%m;
            else dp[i][j] = dp[i-1][j]%m;
        }
    }
    return dp[lt][ls];
} 





// Through Space Optimisation---------------------------
int subsequenceCounting(string &t, string &s, int lt, int ls) {
    // Write your code here.
    // vector<vector<int>> dp(lt+1, vector<int>(ls+1, 0));
    // return f(lt-1, ls-1, t, s, dp)%m;
    vector<int> prev(ls+1, 0), cur(ls+1, 0);
    prev[0]=cur[0]=1;

    for(int i=1;i<=lt;i++){
        for(int j=1;j<=ls;j++){

            if(t[i-1]==s[j-1]) cur[j] = (prev[j-1] + prev[j])%m;
            else cur[j] = prev[j]%m;
        }
        prev=cur;
    }
    return prev[ls];
} 



// Through Sapce Optimisation-----------(USING SINGLE ROW)-----------
int subsequenceCounting(string &t, string &s, int lt, int ls) {
    // Write your code here.
    // vector<vector<int>> dp(lt+1, vector<int>(ls+1, 0));
    // return f(lt-1, ls-1, t, s, dp)%m;
    vector<int> prev(ls+1, 0), cur(ls+1, 0);
    prev[0]=cur[0]=1;

    for(int i=1;i<=lt;i++){
        for(int j=ls;j>=1;j--){

            if(t[i-1]==s[j-1]) prev[j] = (prev[j-1] + prev[j])%m;
            else pr ev[j] = prev[j]%m;
        }
        // prev=cur;
    }
    return prev[ls];
} 


//---------------------//
int subsequenceCounting(string &t, string &s, int lt, int ls) {
    // Write your code here.
    // vector<vector<int>> dp(lt+1, vector<int>(ls+1, 0));
    // return f(lt-1, ls-1, t, s, dp)%m;
    vector<int> prev(ls+1, 0), cur(ls+1, 0);
    prev[0]=cur[0]=1;

    for(int i=1;i<=lt;i++){
        for(int j=ls;j>=1;j--){

            if(t[i-1]==s[j-1]) prev[j] = (prev[j-1] + prev[j])%m;
            // else prev[j] = prev[j]%m;                             ----I CAN ALSO COMMENT THIS LINE AS IT IS OF NO USE--------
        }
        // prev=cur;
    }
    return prev[ls];
} 
int main(){
    return 0;
}