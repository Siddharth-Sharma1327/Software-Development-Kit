#include<iostream>
#include<bits/stdc++.h> 
using namespace std;



// -------------IDEA---------  
// Idea is that we have compared this problem with longest increasing subseqeunce but with condition that next string with length +1 that prev length have difference of only 1 character..and if so then we willtake it into the sequence
// But we have to sort the given array w.r.t length so that we don't miss the sequence which can be taken but present after, in the sequence whose length is lower that others taken
// eg-- " xbc, pcxbcf, xb, cxbc, pcxbc"----> in this eg "xb" got missed if we don't sort the array w.r.t length 

// CODE--
bool comp(string &s1, string &s2){
    return s1.size()<s2.size();
}
bool checkPossible(string &s1, string &s2){

    if(s1.size()!= s2.size()+1) return false;
    int first=0;
    int second =0;
    while(first<s1.size()){          // s1 = bcda   s2 = bcd refer this for first<s1.size()

        if(second<s2.size() && s1[first]==s2[second]){   //if second one gets exhaust earlier than 1st then we will do only first++
            first++;
            second++;
        }else {
            first++;          //condition of s1[first]!=s2[second] and second one gets exhaust earlier than 1st
        }

        if(first==s1.size() && second==s2.size()) return true;     // return true when both strings gets exhaust 
    }
    return false;
}

int longestStrChain(vector<string> &arr)
{
    // Write your code here.
    int n = arr.size();
    sort(arr.begin(), arr.end(), comp);    //sorting the array w.r.t lengths of the strings
    vector<int> dp(n, 1);
    int maxi=1;
    for(int i=0;i<n;i++){
        for(int prev=0;prev<i;prev++){
            if(checkPossible(arr[i], arr[prev]) && dp[prev]+1>dp[i]){
                dp[i] = dp[prev]+1;
            }
        }
        if(dp[i]>maxi){
            maxi=dp[i];
        }
    }

    return maxi;
}




// Time Complexity---------> O(N^2xL) L->max possible length of string + O(logn){sort function}
//  Space Complexity--------> O(N)
int main(){
    return 0;
}