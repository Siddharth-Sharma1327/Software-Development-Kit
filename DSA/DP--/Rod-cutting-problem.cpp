#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Through Recursion---------

int f(int ind, vector<int> &price, int n){
	
	if(n==0 || ind<0) return 0;

	int notTake = f(ind-1, price, n);
	int take = 0;
	if(n>=ind+1) take = price[ind] + f(ind, price, n-(ind+1));

	return max(notTake, take);
}

int cutRod(vector<int> &price, int n)
{
	// Write your code here.
	return f(n-1, price, n);
}

//Through Memoisation------------
int f(int ind, vector<int> &price, int n, vector<vector<int>> &dp){
	
	if(n==0 || ind<0) return 0;
	if(dp[ind][n]!=-1) return dp[ind][n];
	int notTake = f(ind-1, price, n, dp);
	int take = 0;
	if(n>=ind+1) take = price[ind] + f(ind, price, n-(ind+1), dp);

	return dp[ind][n] = max(notTake, take);
}

int cutRod(vector<int> &price, int n)
{
	// Write your code here.
	vector<vector<int>> dp(n, vector<int>(n+1, -1));
	return f(n-1, price, n, dp);
}

// Through Tabulation-------------
int cutRod(vector<int> &price, int n)
{
	// Write your code here.
	vector<vector<int>> dp(n, vector<int>(n+1, 0));
	// return f(n-1, price, n, dp);

	for(int ind=0;ind<n;ind++){
		for(int j=1;j<=n;j++){
				int notTake = 0;
				if(ind!=0) notTake = dp[ind-1][j];
				int take = 0;
				if(j>=ind+1) take = price[ind] + dp[ind][j-(ind+1)];

				dp[ind][j] = max(notTake, take);

		}
	}

	return dp[n-1][n];
}


// Through Space Optimisation----------
int cutRod(vector<int> &price, int n)
{
	// Write your code here.
	// vector<vector<int>> dp(n, vector<int>(n+1, 0));
	// return f(n-1, price, n, dp);

	vector<int> prev(n+1, 0), cur(n+1, 0);
	for(int ind=0;ind<n;ind++){
		for(int j=1;j<=n;j++){
				int notTake = 0;
				if(ind!=0) notTake = prev[j];
				int take = 0;
				if(j>=ind+1) take = price[ind] + cur[j-(ind+1)];

				cur[j] = max(notTake, take);

		}
		prev=cur;
	}

	return prev[n];
}




// Through Space Optimisation Using Single Row(Optimised to singe array)-------------------
int cutRod(vector<int> &price, int n)
{
	// Write your code here.
	// vector<vector<int>> dp(n, vector<int>(n+1, 0));
	// return f(n-1, price, n, dp);

	vector<int> prev(n+1, 0);
	//  cur(n+1, 0);
	for(int ind=0;ind<n;ind++){
		for(int j=1;j<=n;j++){
				int notTake = 0;
				if(ind!=0) notTake = prev[j];
				int take = 0;
				if(j>=ind+1) take = price[ind] + prev[j-(ind+1)];

				prev[j] = max(notTake, take);

		}
		// prev=cur;
	}

	return prev[n];
}

int main(){
    return 0;
}