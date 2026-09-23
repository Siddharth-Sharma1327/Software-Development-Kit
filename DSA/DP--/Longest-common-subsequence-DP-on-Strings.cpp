#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Through Recursion-------------
int f(int i, int j, string &s, string &t){

	if(i<0 || j<0) return 0;

	if(s[i]==t[j]) return 1+f(i-1, j-1, s, t);

	else return max(f(i-1,j,s,t), f(i,j-1,s,t));
}


int lcs(string s, string t)
{
	//Write your code here
	int n = s.length();
	int m = t.length();

	return f(n-1, m-1, s, t);
}

// T.C = 2^(n) + 2^(m) & S.C = O(n+m) (Recursion Stack Space)

// Through Memoisation-----------
int f(int i, int j, string &s, string &t, vector<vector<int>> &dp){

	if(i<0 || j<0) return 0;
	if(dp[i][j]!=-1) return dp[i][j];
	if(s[i]==t[j]) return 1+f(i-1, j-1, s, t, dp);

	else return dp[i][j] = max(f(i-1,j,s,t, dp), f(i,j-1,s,t, dp));
}


int lcs(string s, string t)
{
	//Write your code here
	int n = s.length();
	int m = t.length();
	vector<vector<int>> dp(n, vector<int>(m, -1));
	return f(n-1, m-1, s, t, dp);
}
// T.C = O(n*m) & S.C = O(n*m) + O(n+m) (Recursion Stack Space)




// Through Tabulation--------------
int lcs(string s, string t)
{
	//Write your code here
	int n = s.length();
	int m = t.length();
	vector<vector<int>> dp(n, vector<int>(m, 0));
	// return f(n-1, m-1, s, t, dp);
	if(s[0]==t[0]) dp[0][0]=1;

	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){

				if(i==0 && j==0){
					if(s[0]==t[0]) dp[0][0]=1;
				}
				else if(i==0 && j!=0){
					if(s[i]==t[j]) dp[i][j]=1;
					else dp[i][j]=dp[i][j-1];
				}else if(i!=0 && j==0){
					if(s[i]==t[j]) dp[i][j]=1;
					else dp[i][j]=dp[i-1][j];
				}else {
					if(s[i]==t[j]) dp[i][j] = 1 + dp[i-1][j-1];
					else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
				}

		}
	}

	return dp[n-1][m-1];
}
// T.C = O(n*m) & S.C = O(n*m)


// Through Space Optimisation-------------
int lcs(string s, string t)
{
	//Write your code here
	int n = s.length();
	int m = t.length();
	// vector<vector<int>> dp(n, vector<int>(m, 0));
	// return f(n-1, m-1, s, t, dp);
	vector<int> prev(m, 0), cur(m, 0);

	if(s[0]==t[0]) prev[0]=1;
	// for(int i=1;i<n;i++){
	// 	if(s[i]==t[0]) dp[i][0]=1;
	// 	else dp[i][0]=dp[i-1][0];
	// }

	for(int j=1;j<m;j++){
		if(s[0]==t[j]) prev[j]=1;
		else prev[j]=prev[j-1];
	}

	for(int i=1;i<n;i++){
		for(int j=0;j<m;j++){

			if(j==0){
				if(s[i]==t[0]) cur[0]=1;
				else cur[0]=prev[0];
			}else{
				if(s[i]==t[j]) cur[j] = 1 + prev[j-1];
			    else cur[j] = max(prev[j], cur[j-1]);
			}	
		}
		prev=cur;
	}

	return prev[m-1];
}
// T.C = O(n*m) & S.C = O(m)


// Shifting of index------------------(trick to solve tabulation for the base cases having the negative indexes)
// Through Recursion-----

int f(int i, int j, string &s, string &t){

	if(i==0 || j==0) return 0;

	if(s[i-1]==t[j-1]) return 1+f(i-1, j-1, s, t);

	else return max(f(i-1,j,s,t), f(i,j-1,s,t));
}


int lcs(string s, string t)
{
	//Write your code here
	int n = s.length();
	int m = t.length();

	return f(n, m, s, t);
}

// Memoisation one is same with above changes........
int f(int i, int j, string &s, string &t, vector<vector<int>> &dp){

	if(i==0 || j==0) return 0;
	if(dp[i][j]!=-1) return dp[i][j];
	if(s[i-1]==t[j-1]) return 1+f(i-1, j-1, s, t, dp);

	else return dp[i][j] = max(f(i-1,j,s,t, dp), f(i,j-1,s,t, dp));
}


int lcs(string s, string t)
{
	//Write your code here
	int n = s.length();
	int m = t.length();
	vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
	return f(n, m, s, t, dp);
}

//Through Tabulation---------------------(USING SHIFTING OF INDEX)
int lcs(string s, string t)
{
	//Write your code here
	int n = s.length();
	int m = t.length();
	vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
	// return f(n-1, m-1, s, t, dp);
	// if(s[0]==t[0]) dp[0][0]=1;

	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){

				// if(i==0 && j==0){
				// 	if(s[0]==t[0]) dp[0][0]=1;
				// }
				// else if(i==0 && j!=0){
				// 	if(s[i]==t[j]) dp[i][j]=1;
				// 	else dp[i][j]=dp[i][j-1];
				// }else if(i!=0 && j==0){
				// 	if(s[i]==t[j]) dp[i][j]=1;
				// 	else dp[i][j]=dp[i-1][j];
				 
					if(s[i-1]==t[j-1]) dp[i][j] = 1 + dp[i-1][j-1];
					else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
				

		}
	}

	return dp[n][m];
}


// Through Space Optimisation------------
int lcs(string s, string t)
{
	//Write your code here
	int n = s.length();
	int m = t.length();
	// vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
	// return f(n-1, m-1, s, t, dp);
	// if(s[0]==t[0]) dp[0][0]=1;
	vector<int> prev(m+1, 0), cur(m+1, 0);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){

				// if(i==0 && j==0){
				// 	if(s[0]==t[0]) dp[0][0]=1;
				// }
				// else if(i==0 && j!=0){
				// 	if(s[i]==t[j]) dp[i][j]=1;
				// 	else dp[i][j]=dp[i][j-1];
				// }else if(i!=0 && j==0){
				// 	if(s[i]==t[j]) dp[i][j]=1;
				// 	else dp[i][j]=dp[i-1][j];
				 
					if(s[i-1]==t[j-1]) cur[j] = 1 + prev[j-1];
					else cur[j] = max(prev[j], cur[j-1]);
				
		}
		prev = cur;
	}

	return prev[m];
}
int main(){
    return 0;
}