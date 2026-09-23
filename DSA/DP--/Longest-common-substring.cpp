#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Through Tabulation------(refer tabulation of logest common subsequence)-------------
int lcs(string &str1, string &str2){
	//	Write your code here.

	

	//Write your code here
	int n = str1.length();
	int m = str2.length();
	vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){

					if(str1[i-1]==str2[j-1]) dp[i][j] = 1 + dp[i-1][j-1];
					else dp[i][j] = 0;
					ans=max(ans, dp[i][j]);
		}
	}

	return ans;


}
// Through Space Optimisation---------------
int lcs(string &str1, string &str2){
	//	Write your code here.

	

	//Write your code here
	int n = str1.length();
	int m = str2.length();
	// vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
	vector<int> prev(m+1, 0), cur(m+1, 0);
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){

					if(str1[i-1]==str2[j-1]) cur[j] = 1 + prev[j-1];
					else cur[j] = 0;
					ans=max(ans, cur[j]);
		}
		prev = cur;
	}

	return ans;


}
int main(){
    return 0;
}



// consider
class Solution {
    int maxLen;
    public int recursion(String s1, String s2, int n, int m, int[][] dp){
        // base case : either of string length becomes 0 => return 0 as no subtring possible
        if(n==0 || m==0){
            return 0;
        }
        
        if(dp[n][m]!=-1){ // check if this case is already evaluated?
            return dp[n][m]; // directly return it, if yes
        }
        
        if(s1.charAt(n-1)==s2.charAt(m-1)){ // if chars match increase the substring size by 1
            dp[n][m] = 1 + recursion(s1, s2, n-1, m-1, dp);
            maxLen = Math.max(dp[n][m], maxLen); // take max length of substring till now
        }else{
            dp[n][m] = 0; // if chars doesn't match reset the subtring length to 0 and cpmoute further
        }
        
        // explore other possibilities
        recursion(s1, s2, n - 1, m, dp);
        recursion(s1, s2, n, m - 1, dp);
        
        return dp[n][m];
    }
};