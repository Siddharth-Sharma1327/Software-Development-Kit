#include<iostream>
#include<bits/stdc++.h>
using namespace std;


int lcs(string s, string t, vector<vector<int>> &dp)
{
	//Write your code here
	int n = s.length();
	int m = t.length();
	// vector<vector<int>> dp(n, vector<int>(m, 0));
	// return f(n-1, m-1, s, t, dp);
	vector<int> prev(m, 0), cur(m, 0);

	if(s[0]==t[0]) dp[0][0]=1;
	for(int i=1;i<n;i++){
		if(s[i]==t[0]) dp[i][0]=1;
		else dp[i][0]=dp[i-1][0];
	}

	for(int j=1;j<m;j++){
		if(s[0]==t[j]) dp[0][j]=1;
		else dp[0][j]=dp[0][j-1];
	}

	for(int i=1;i<n;i++){
		for(int j=1;j<m;j++){

			if(s[i]==t[j]) dp[i][j] = 1 + dp[i-1][j-1];
			else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
				
		}
	}

	return dp[n-1][m-1];
}


int main(){
    string s = "bleed";       //backtracking the dp table from last right column, the longest sequence and storing the values in string from back ----
    string t = "blue";
    int n = s.length();
    int m = t.length();
    vector<vector<int>> dp(n, vector<int>(m, 0));
    
    string s1 = "";
    int l = lcs(s,t,dp);
    for(int i=0;i<l;i++) s1+='$';


// For not shifting of index of tabulation---------
    int i = n-1;
    int j = m-1;
    int index = l-1;
    while(i>=0 && j>=0){

        if(s[i]==t[j]){
            s1[index]=s[i];
            index--;
            i--;
            j--;
        }else if(dp[i-1][j]>dp[i][j-1]  || j==0){
            i--;
        }else {
            j--;
        }
    }

// For the shifted index of tabulation---------------------
 	int i = n;
    int j = m;
    int index = l-1;
    while(i>0 && j>0){

        if(s[i-1]==t[j-1]){
            s1[index]=s[i];
            index--;
            i--;
            j--;
        }else if(dp[i-1][j]>dp[i][j-1]){
            i--;
        }else {
            j--;
        }
    }








    cout<<s1;

    return 0;
}