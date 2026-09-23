#include<iostream>
#include<bits/stdc++.h>
using namespace std;


//----------IDEA--------The longest pallindromic subsequence of a string is the longest common subsequnce of the given string and the reverse string of the given string--
int longestPalindromeSubsequence(string s)
{
    // Write your code here.
	int n = s.length();
	int m = n;
    string t = s;
    reverse(t.begin(), t.end());
	vector<int> prev(m+1, 0), cur(m+1, 0);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){

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