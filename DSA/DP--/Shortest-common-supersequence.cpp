#include<iostream>
#include<bits/stdc++.h>
using namespace std;

//-----IDEA-----(Shortest Subsequence is the shortest sequence containg both strings as its subsequences--Approach:-We are using dp-table of tabulation(lcs) iterating like printing lcs and if both same include it in s1, if we go i-- then add s[i] OR we go j-- then add t[j] in s1)--scene is that we have to maintain the individual order of both the strings in ans.
#include <bits/stdc++.h> 
string shortestSupersequence(string a, string b)
{

	//Write your code here
	string s=a,t=b;

	int n = s.length();
	int m = t.length();
	vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){


					if(s[i-1]==t[j-1]) dp[i][j] = 1 + dp[i-1][j-1];
					else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
				

		}
	}
	if(dp[n][m]==0) return s+t;
	else {
	
		string s1 = "";
		
		int i = n;
		int j = m;
	
		while(i>0 && j>0){

			if(s[i-1]==t[j-1]){
				s1+=s[i-1];
				i--;
				j--;
			}else if(dp[i-1][j]>dp[i][j-1]){
				s1+=s[i-1];
				i--;
			}else {
				s1+=t[j-1];
				j--;
			}
		}

        while(i>0){
			s1+=s[i-1];
			i--;
		}  
		while(j>0){
			s1+=t[j-1];
			j--;
		}

		reverse(s1.begin(), s1.end());
		return s1;
    }
}

int main(){
    return 0;
}