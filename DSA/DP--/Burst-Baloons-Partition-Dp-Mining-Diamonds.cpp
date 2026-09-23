#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// BURST BALOONS--------------------------------------------------
// Through Recursion------------
class Solution {
public:
    
    int f(int i, int j, vector<int> &nums){
        
        if(i>j) return 0;
        
        int mini = INT_MIN;
        for(int k=i;k<=j;k++){
            
            int cost = nums[i-1]*nums[k]*nums[j+1] + f(i, k-1, nums) + f(k+1, j, nums);
            mini = max(mini, cost);
        }
        
        return mini;
        
    }

    
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.push_back(1);
        nums.insert(nums.begin(), 1);
        
        return f(1, n, nums);
    }
};



// Through Memoisation---------------
class Solution {
public:
    
    int f(int i, int j, vector<int> &nums, vector<vector<int>> &dp){
        
        if(i>j) return 0;
        
        if(dp[i][j]!=-1) return dp[i][j];
        int mini = INT_MIN;
        for(int k=i;k<=j;k++){
            
            int cost = nums[i-1]*nums[k]*nums[j+1] + f(i, k-1, nums, dp) + f(k+1, j, nums, dp);
            mini = max(mini, cost);
        }
        
        return dp[i][j] = mini;
        
    }

    
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.push_back(1);
        nums.insert(nums.begin(), 1);
        vector<vector<int>> dp(n+1, vector<int>(n+1, -1));
        
        return f(1, n, nums, dp);
    }
};




// Through Tabulation------------------
class Solution {
public:
        
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.push_back(1);
        nums.insert(nums.begin(), 1);
        vector<vector<int>> dp(n+2, vector<int>(n+2, 0));
        
        // return f(1, n, nums, dp);
        
        for(int i=n;i>=1;i--){
            for(int j=1;j<=n;j++){
                if(i>j) continue;
                    int mini = INT_MIN;
                    for(int k=i;k<=j;k++){
                        
                        int cost = nums[i-1]*nums[k]*nums[j+1] + dp[i][k-1] + dp[k+1][j];
                        mini = max(mini, cost);
                    }

                    dp[i][j] = mini;
                
            }
        }
        
        return dp[1][n];
        
    }
};

// Recursion 
// T.C = O(4^N) 
// S.C = O(N)


// Memoisation
// T.C = O(N*N*N)
// S.C = O(N) + O(N*N)

// Tabulation
// T.C = O(N*N*N)
// S.C = O(N*N)





// MINING DIAMONDS-------------------------------------------------
// Through Recursion------
int f(int i, int j, vector<int> &a){

	if(i>j) return 0;

	int mini=INT_MIN;
	for(int k=i;k<=j;k++){
		int cost = a[i-1]*a[k]*a[j+1] + f(i, k-1, a) + f(k+1, j, a);
		mini = max(mini, cost);
	}

	return mini;
}


int maxCoins(vector<int>& a)
{
	// Write your code here.
	int n = a.size();
	a.push_back(1);
	a.insert(a.begin(), 1);
	return f(1, n, a);
}



// Through Memoisation----------
int f(int i, int j, vector<int> &a, vector<vector<int>> &dp){

	if(i>j) return 0;

	if(dp[i][j]!=-1) return dp[i][j];
	int mini=INT_MIN;
	for(int k=i;k<=j;k++){
		int cost = a[i-1]*a[k]*a[j+1] + f(i, k-1, a, dp) + f(k+1, j, a, dp);
		mini = max(mini, cost);
	}

	return dp[i][j] = mini;
}


int maxCoins(vector<int>& a)
{
	// Write your code here.
	int n = a.size();
	a.push_back(1);
	a.insert(a.begin(), 1);
	vector<vector<int>> dp(n+1, vector<int>(n+1, -1));
	return f(1, n, a, dp);
}




// Through Tabulation--------------
int maxCoins(vector<int>& a)
{
	// Write your code here.
	int n = a.size();
	a.push_back(1);
	a.insert(a.begin(), 1);
	vector<vector<int>> dp(n+2, vector<int>(n+2, 0));
	// return f(1, n, a, dp);

	for(int i=n;i>=1;i--){
		for(int j=1;j<=n;j++){
			if(i>j) continue;
				int mini=INT_MIN;
				for(int k=i;k<=j;k++){
					int cost = a[i-1]*a[k]*a[j+1] + dp[i][k-1] + dp[k+1][j];
					mini = max(mini, cost);
				}

				dp[i][j] = mini;
		}
	}

	return dp[1][n];
}




int main(){
    return 0;
}