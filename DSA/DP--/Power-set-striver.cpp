#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Solution{
	public:
		vector<string> AllPossibleStrings(string s){
		    // Code here
		    vector<string> ans;
		    int n = s.length();
		    for(int i=0;i<(1<<n);i++){      //left shift of 1 by n is equal to 2^n
		        string s1="";
		        for(int j=0;j<n;j++){
		            if(i&(1<<(j))) s1+=s[j];     //to check if the bit is 1..then that element is added into the string...refer striver notes for this
		        }
		        if(!s1.empty()) ans.push_back(s1);
		    }
		    sort(ans.begin(), ans.end());
		    return ans;
		}
};
int main(){
    return 0;
}