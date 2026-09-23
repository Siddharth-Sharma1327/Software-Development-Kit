#include<iostream>
#include<bits/stdc++.h>
using namespace std;

//-------------------IDEA---------(Find the length of longest common subsequence..that portion will be same for both strings..so min deletions+insertions=n-lcs+m-lcs)-------
int canYouMake(string &str, string &ptr)
{
    // Write your code here.


	//Write your code here
    string s=str, t=ptr;
	int n = s.length();
	int m = t.length();

	vector<int> prev(m+1, 0), cur(m+1, 0);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){

					if(s[i-1]==t[j-1]) cur[j] = 1 + prev[j-1];
					else cur[j] = max(prev[j], cur[j-1]);
				
		}
		prev = cur;
	}

	return n+m-2*prev[m];

}
int main(){
    return 0;
}