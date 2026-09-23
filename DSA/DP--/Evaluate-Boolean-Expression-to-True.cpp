#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Through Recursion--------------------------

#include <bits/stdc++.h>
// #define long long int ll
int mod = 1000000007;


long long f(int i, int j, int isTrue, string &exp){

    if(i>j) return 0;

    if(i==j){
        if(isTrue){
            return exp[i]=='T';
        }else {
            return exp[i]=='F';
        }
    }

    long long ways=0;
    for(int k = i+1; k<=j-1; k+=2){

        long long lT = f(i, k-1, 1, exp);
        long long lF = f(i, k-1, 0, exp);
        long long rT = f(k+1, j, 1, exp);
        long long rF = f(k+1, j, 0, exp);


        if(exp[k]=='|'){

            if(isTrue){
                ways = (ways + (lT*rF)%mod + (lF*rT)%mod + (lT*rT)%mod )%mod;
            }else{
                ways = (ways + (lF*rF)%mod)%mod;
            }


        }else if(exp[k]=='&'){

            if(isTrue){
                ways = (ways + (lT*rT)%mod )%mod;
            }else {
                ways = (ways + (lT*rF)%mod + (lF*rT)%mod + (lF*rF)%mod )%mod;
            }


        }else {
            
            if(isTrue){
                ways = (ways + (lT*rF)%mod + (lF*rT)%mod )%mod;
            }else {
                ways = (ways + (lT*rT)%mod + (lF*rF)%mod )%mod;
            }

        }

    }

    return ways;

}



int evaluateExp(string & exp) {
    // Write your code here.
    int n = exp.size();
    return f(0, n-1, 1, exp);

}











// Through Memoisation--------------------------------------

// #define long long int ll
int mod = 1000000007;


long long f(int i, int j, int isTrue, string &exp, vector<vector<vector<long long>>> &dp){

    if(i>j) return 0;

    if(i==j){
        if(isTrue){
            return exp[i]=='T';
        }else {
            return exp[i]=='F';
        }
    }

    if(dp[i][j][isTrue]!=-1) return dp[i][j][isTrue];

    long long ways=0;
    for(int k = i+1; k<=j-1; k+=2){

        long long lT = f(i, k-1, 1, exp, dp);
        long long lF = f(i, k-1, 0, exp, dp);
        long long rT = f(k+1, j, 1, exp, dp);
        long long rF = f(k+1, j, 0, exp, dp);


        if(exp[k]=='|'){

            if(isTrue){
                ways = (ways + (lT*rF)%mod + (lF*rT)%mod + (lT*rT)%mod )%mod;
            }else{
                ways = (ways + (lF*rF)%mod)%mod;
            }


        }else if(exp[k]=='&'){

            if(isTrue){
                ways = (ways + (lT*rT)%mod )%mod;
            }else {
                ways = (ways + (lT*rF)%mod + (lF*rT)%mod + (lF*rF)%mod )%mod;
            }


        }else {
            
            if(isTrue){
                ways = (ways + (lT*rF)%mod + (lF*rT)%mod )%mod;
            }else {
                ways = (ways + (lT*rT)%mod + (lF*rF)%mod )%mod;
            }

        }

    }

    return dp[i][j][isTrue] = ways;

}



int evaluateExp(string & exp) {
    // Write your code here.
    int n = exp.size();
    vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(n, vector<long long>(2, -1)));
    return f(0, n-1, 1, exp, dp);

}

















// Through Tabulation---------------------------------------------

// #define long long int ll
int mod = 1000000007;

int evaluateExp(string & exp) {
    // Write your code here.
    int n = exp.size();
    vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(n, vector<long long>(2, 0)));
    // return f(0, n-1, 1, exp, dp);

    for(int i=0;i<n;i++){
        if(exp[i]=='T') dp[i][i][1]=1;
        else dp[i][i][0]=1;
    }


    for(int i=n-1;i>=0;i--){
        for(int j=i+1;j<=n-1;j++){
            if(i>j) continue;
            for(int isTrue=0;isTrue<2;isTrue++){
                long long ways=0;
                for(int k = i+1; k<=j-1; k+=2){

                    long long lT = dp[i][k-1][1];
                    long long lF = dp[i][k-1][0];
                    long long rT = dp[k+1][j][1];
                    long long rF = dp[k+1][j][0];


                    if(exp[k]=='|'){

                        if(isTrue){
                            ways = (ways + (lT*rF)%mod + (lF*rT)%mod + (lT*rT)%mod )%mod;
                        }else{
                            ways = (ways + (lF*rF)%mod)%mod;
                        }


                    }else if(exp[k]=='&'){

                        if(isTrue){
                            ways = (ways + (lT*rT)%mod )%mod;
                        }else {
                            ways = (ways + (lT*rF)%mod + (lF*rT)%mod + (lF*rF)%mod )%mod;
                        }


                    }else {
                        
                        if(isTrue){
                            ways = (ways + (lT*rF)%mod + (lF*rT)%mod )%mod;
                        }else {
                            ways = (ways + (lT*rT)%mod + (lF*rF)%mod )%mod;
                        }

                    }

                }

                dp[i][j][isTrue] = ways;
            }
        }
    }

    return dp[0][n-1][1];

}

// Recursion
// T.C = O(4^N) 
// S.C = O(N)


// Memoisation
// T.C = O(N*N*N)*2
// S.C = O(N*N*2) + O(N)


// Tabulation
// T.C = O(N*N*N)*2
// S.C = O(N*N*2)

int main(){
    return 0;
}