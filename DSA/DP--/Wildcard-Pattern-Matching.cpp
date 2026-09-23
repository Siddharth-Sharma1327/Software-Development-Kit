#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// Through Recursion--------------------------------
#include<bits/stdc++.h>
bool f(int i, int j, string &pattern, string &text){

   if(i<0 && j<0) return true;                      //BAse cases most important part-----------------------------
   if(i<0 && j>=0) return false;
   if(i>=0 && j<0){
      if(pattern[i]!='*') return false;
      else return f(i-1,j,pattern, text);
   }

//    if(dp[i][j]!=-1) return dp[i][j];
   if(pattern[i]==text[j] || pattern[i]=='?'){
      return f(i-1, j-1, pattern, text);
   }else if(pattern[i]=='*') {

       return f(i-1,j,pattern,text)|f(i, j-1, pattern, text);
      
   }else return false;
}


 
bool wildcardMatching(string pattern, string text)
{
   // Write your code here.
   int n = pattern.length();
   int m = text.length();
//    vector<vector<int>> dp(n, vector<int>(m, -1));
   return f(n-1, m-1, pattern, text);
}


// Through Memoisation----------------------------
#include<bits/stdc++.h>
bool f(int i, int j, string &pattern, string &text, vector<vector<int>> &dp){

   if(i<0 && j<0) return true;
   if(i<0 && j>=0) return false;
   if(i>=0 && j<0){
      if(pattern[i]!='*') return false;
      else return f(i-1,j,pattern, text,dp);
   }

   if(dp[i][j]!=-1) return dp[i][j];
   if(pattern[i]==text[j] || pattern[i]=='?'){
      return dp[i][j]=f(i-1, j-1, pattern, text, dp);
   }else if(pattern[i]=='*') {

      return dp[i][j]= f(i-1,j,pattern,text,dp)|f(i, j-1, pattern, text,dp);
      
   }else return dp[i][j]=false;
}



bool wildcardMatching(string pattern, string text)
{
   // Write your code here.
   int n = pattern.length();
   int m = text.length();
   vector<vector<int>> dp(n, vector<int>(m, -1));
   return f(n-1, m-1, pattern, text,dp);
}



// Through Tabulation--------------------------------
bool wildcardMatching(string pattern, string text)
{
   // Write your code here.
   int n = pattern.length();
   int m = text.length();
   vector<vector<bool>> dp(n+1, vector<bool>(m+1, 0));
   // return f(n-1, m-1, pattern, text,dp);
   dp[0][0]=1;
   for(int j=1;j<=m;j++) dp[0][j]=0;

   for (int i = 1; i <= n; i++) {
      if(pattern[i-1]=='*') dp[i][0]= dp[i-1][0];
   }

   for(int i=1;i<=n;i++){
      for(int j=1;j<=m;j++){
         if(pattern[i-1]==text[j-1] || pattern[i-1]=='?'){
            dp[i][j]=dp[i-1][j-1];
         }else if(pattern[i-1]=='*') {

            dp[i][j]= dp[i-1][j] | dp[i][j-1];
            
         }else dp[i][j]=0;

      }
   }

   return dp[n][m];
}






// Through Space Optimisation--------------------
bool wildcardMatching(string pattern, string text)
{
   // Write your code here.
   int n = pattern.length();
   int m = text.length();

   vector<int> prev(n+1, 0), cur(m+1, 0);
   prev[0]=1;

   for(int i=1;i<=n;i++){
      for(int j=0;j<=m;j++){
         if(j==0){
            if(pattern[i-1]=='*') cur[0]= prev[0];
         } 
         else if(pattern[i-1]==text[j-1] || pattern[i-1]=='?'){
            cur[j]=prev[j-1];
         }else if(pattern[i-1]=='*') {

            cur[j]= prev[j] | cur[j-1];
            
         }else cur[j]=0;            //this is important in space optimisation while not in tabulation one-----------

      }
      prev=cur;
   }

   return prev[m];
}

int main(){
    return 0;
}




// Leetcode one-------------------------------------------------------

// Recursion
class Solution {
public:
    bool isMatchHelper(int i, int j, string s, string p){
        // base
        if(i < 0){
            if(j < 0) return true;
            if(p[j] == '*') return isMatchHelper(i, j-1, s, p);
            return false;
        }
        if(j < 0) return false;

        if(s[i] == p[j]){
            return isMatchHelper(i-1, j-1, s, p);
        }else{
            if(p[j] != '?' && p[j] != '*'){
                return 0;
            }else if(p[j] == '?'){
                return isMatchHelper(i-1, j-1, s, p);
            }else if(p[j] == '*'){
                return isMatchHelper(i-1, j, s, p) || isMatchHelper(i, j-1, s, p);
            }
        }
        return false;
    }
    bool isMatch(string s, string p) {
        int n = s.length();
        int m = p.length();
        return isMatchHelper(n-1, m-1, s, p);
    }
};


//Memoisation
class Solution {
public:
    bool isMatchHelper(int i, int j, string s, string p, vector<vector<int>> &dp){
        // base
        if(i < 0){
            if(j < 0) return true;
            if(p[j] == '*') return isMatchHelper(i, j-1, s, p, dp);
            return false;
        }
        if(j < 0) return false;

        if(dp[i][j] != -1) return dp[i][j];
        if(s[i] == p[j]){
            return dp[i][j] = isMatchHelper(i-1, j-1, s, p, dp);
        }else{
            if(p[j] != '?' && p[j] != '*'){
                return dp[i][j] = 0;
            }else if(p[j] == '?'){
                return dp[i][j] = isMatchHelper(i-1, j-1, s, p, dp);
            }else if(p[j] == '*'){
                return dp[i][j] = isMatchHelper(i-1, j, s, p, dp) || isMatchHelper(i, j-1, s, p, dp);
            }
        }
        return dp[i][j] = false;
    }
    bool isMatch(string s, string p) {
        int n = s.length();
        int m = p.length();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return isMatchHelper(n-1, m-1, s, p, dp);
    }
};


// Tabulation
class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.length();
        int m = p.length();
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
        // return isMatchHelper(n-1, m-1, s, p, dp);

        // base
        for(int i=0; i<=n; i++) dp[i][0] = 0;
        dp[0][0] = 1;
        for(int j=1; j<=m; j++){
            if(p[j-1] == '*') dp[0][j] = dp[0][j-1];
            else dp[0][j] = 0;
        }

        for(int i=1; i<=n ;i++){
            for(int j=1; j<=m; j++){
                if(s[i-1] == p[j-1]){
                    dp[i][j] = dp[i-1][j-1];
                }else{
                    if(p[j-1] != '?' && p[j-1] != '*'){
                        dp[i][j] = 0;
                    }else if(p[j-1] == '?'){
                        dp[i][j] = dp[i-1][j-1];
                    }else if(p[j-1] == '*'){
                        dp[i][j] = dp[i-1][j] || dp[i][j-1];
                    }
                }
            }
        }
        return dp[n][m];
    }
};


// Space Optimisation
class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.length();
        int m = p.length();
        vector<int> prev(m+1, 0), cur(m+1, 0);
        // return isMatchHelper(n-1, m-1, s, p, dp);

        // base
        prev[0] = cur[0] = 0;
        prev[0] = 1;

        for(int j=1; j<=m; j++){
            if(p[j-1] == '*') prev[j] = prev[j-1];
            else prev[j] = 0;
        }

        for(int i=1; i<=n ;i++){
            for(int j=1; j<=m; j++){
                if(s[i-1] == p[j-1]){
                    cur[j] = prev[j-1];
                }else{
                    if(p[j-1] != '?' && p[j-1] != '*'){
                        cur[j] = 0;
                    }else if(p[j-1] == '?'){
                        cur[j] = prev[j-1];
                    }else if(p[j-1] == '*'){
                        cur[j] = prev[j] || cur[j-1];
                    }
                }
            }
            prev = cur;
        }
        return prev[m];
    }
};