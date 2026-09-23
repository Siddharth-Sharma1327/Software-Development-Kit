#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Using stack-----------
class Solution
{
    public:
    //Function to reverse words in a given string.
    string reverseWords(string S) 
    { 
        // code here 
        int n = S.length();
        stack<string> st;
        string s="";
        for(int i=0;i<n;i++){
            
            if(S[i]!='.'){
                s+=S[i];
                if(i==n-1) st.push(s), st.push(".");
            }else st.push(s), st.push("."),  s="";
        }
        st.pop();
        string ans="";
        while(!st.empty()){
            ans+=st.top();
            st.pop();
        }
        return ans;
    } 
};

int main(){
    return 0;
}