#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// Through Using Longest Increasing subseqeunce Tabulation(algorithmic) code:

vector<int> divisibleSet(vector<int> &arr){
    // Write your code here.
    int n = arr.size();
    vector<int> dp(n, 1), hash(n);
    int maxi=1;
    int lastIndex=0; 
    sort(arr.begin(), arr.end()); //
    for(int i=0;i<n;i++){
        hash[i]=i;
        for(int prev=0;prev<i;prev++){
            if(arr[i]%arr[prev]==0 && dp[prev]+1>dp[i]){  //
                dp[i] = dp[prev]+1;
                hash[i]=prev;
            }
        }
        if(dp[i]>maxi){
            maxi=dp[i];
            lastIndex=i;
        }
    }
    vector<int> temp;
    temp.push_back(arr[lastIndex]);
    while(hash[lastIndex]!=lastIndex){
        lastIndex = hash[lastIndex];
        temp.push_back(arr[lastIndex]);
    }

    reverse(temp.begin(), temp.end());

    return temp;
}


// Time Complexity----> O(N^2)(two for loops worst case) + O(N)(backtracking)
// Space Complexity---> O(N)

int main(){
     return 0;
}