#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Through Recursion-------------------------
int f(int i, int j, string &str1, string &str2, int l1, int l2){

    if(i<0) return j+1;       //if one string exahusts remaing of other string as they would be no. of insertions/deletions
    if(j<0) return i+1; 

    if(str1[i]==str2[j]) return f(i-1, j-1, str1, str2, l1, l2);
    else {
        // string x1=str1,x2=str1,x3=str1;
        // x1.erase(i, 1);
        int del = 1+f(i-1,j,str1,str2, l1, l2);

        // string z1="";
        // z1+=str2[j];
        // if(i==l1-1) x2.push_back(str2[j]);
        // else x2.insert(i+1, z1);
        int ins = 1+f(i, j-1, str1, str2, l1, l2);

        // x3[i]=str2[j];
        int rep  = 1+f(i-1, j-1, str1, str2, l1, l2);


        return min(del, min(ins, rep));
    }
}


int editDistance(string str1, string str2)
{
    //write you code here
    int l1 = str1.length();
    int l2 = str2.length();

    return f(l1-1, l2-1, str1, str2, l1, l2);
}





// Through Memoisation-----------------------------------------
int f(int i, int j, string &str1, string &str2, int l1, int l2, vector<vector<int>> &dp){

    if(i<0) return j+1;
    if(j<0) return i+1; 

    if(dp[i][j]!=-1) return dp[i][j];
    if(str1[i]==str2[j]) return dp[i][j] =  f(i-1, j-1, str1, str2, l1, l2, dp);
    else {
        // string x1=str1,x2=str1,x3=str1;
        // x1.erase(i, 1);
        int del = 1+f(i-1,j,str1,str2, l1, l2, dp);

        // string z1="";
        // z1+=str2[j];
        // if(i==l1-1) x2.push_back(str2[j]);
        // else x2.insert(i+1, z1);
        int ins = 1+f(i, j-1, str1, str2, l1, l2, dp);

        // x3[i]=str2[j];
        int rep  = 1+f(i-1, j-1, str1, str2, l1, l2, dp);


        return dp[i][j] = min(del, min(ins, rep));
    }
}

int editDistance(string str1, string str2) {
  // write you code here
  int l1 = str1.length();
  int l2 = str2.length();
  vector<vector<int>> dp(l1, vector<int>(l2, -1));

  return f(l1 - 1, l2 - 1, str1, str2, l1, l2, dp);
}





// Through Tabulation-------------------------------------------
int editDistance(string str1, string str2) {

  int l1 = str1.length();
  int l2 = str2.length();
  vector<vector<int>> dp(l1+1, vector<int>(l2+1, 0));

//   return f(l1 - 1, l2 - 1, str1, str2, l1, l2, dp);

    for(int j=0;j<=l2;j++) dp[0][j]=j;   //1-based indexing
    for(int i=0;i<=l1;i++) dp[i][0]=i;

    for(int i=1;i<=l1;i++){
        for(int j=1;j<=l2;j++){
            if(str1[i-1]==str2[j-1]) dp[i][j] =  dp[i-1][j-1];
            else {
            int del = 1 + dp[i-1][j];
            int ins = 1 + dp[i][j-1];
            int rep = 1 + dp[i-1][j-1];
            dp[i][j] = min(del, min(ins, rep));
           }
        }
    }
  return dp[l1][l2];
}







// Through Space OPtimisation----------------------------------------
int editDistance(string str1, string str2) {

  int l1 = str1.length();
  int l2 = str2.length();
  // vector<vector<int>> dp(l1+1, vector<int>(l2+1, 0));
  vector<int> prev(l2+1, 0), cur(l2+1, 0);

//   return f(l1 - 1, l2 - 1, str1, str2, l1, l2, dp);

    for(int j=0;j<=l2;j++) prev[j]=j;

    for(int i=1;i<=l1;i++){
          for(int j=0;j<=l2;j++){
            if(j==0) cur[0]=i;
            else if(str1[i-1]==str2[j-1]) cur[j] =  prev[j-1];
            else {
            int del = 1 + prev[j];
            int ins = 1 + cur[j-1];
            int rep = 1 + prev[j-1];
            cur[j] = min(del, min(ins, rep));
            }
          }
        prev=cur;
    }
  return prev[l2];
}


// Not possible for single array optimisation
int main(){
    return 0;
}