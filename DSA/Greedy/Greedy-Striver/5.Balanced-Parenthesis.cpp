#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Brute force ---- Using DP
class Solution {
public:
    vector<vector<vector<int>>>dp;
    bool checkValidString(string s) {
        
        int n=s.length();
        dp.resize(n,vector<vector<int>>(n,vector<int>(n,-1)));
        int open=0;
        int close=0;
        int idx=0;
        return fun(s,idx,open,close);
    }
    bool fun(string &s,int idx,int open,int close)
    {
         if(idx>=s.length())
         {
             if(open==close)
                 return true;
             else
                 return false;
         }
         if(close>open)
             return false;
         if(dp[idx][open][close]!=-1)
             return dp[idx][open][close];
        
         if(s[idx]=='(')
         {
              return dp[idx][open][close]=fun(s,idx+1,open+1,close);
         }
         if(s[idx]==')')
         {
              return dp[idx][open][close]=fun(s,idx+1,open,close+1);
         }
         else if(s[idx]=='*')
         {
             bool a =  fun(s,idx+1,open,close);   //just empty 
             bool b =  fun(s,idx+1,open+1,close);
             bool c =  fun(s,idx+1,open,close+1);
             
             return dp[idx][open][close]=a or b or c;
         }
         return false;
    }
};
// '*' has 3-options '(', ')' or ' '
// T.C -> O(3^n){recursion}, O(n^3){optimal}
// S.C -> O(n^3)


// Better Soln ------ Using stack
class Solution {
public:
    bool checkValidString(string s) {
        stack<int> starIndex;
        stack<int> stackIndex;

        for(int i = 0; i < s.length(); i++)
        {
            if(s[i] == '(')
            {
                stackIndex.push(i);
            }
            else if(s[i] == '*')
            {
                starIndex.push(i);
            }
            else if(s[i] == ')')
            {
                if(stackIndex.empty() && starIndex.empty()) 
                    return false;
                else if(!stackIndex.empty()) 
                    stackIndex.pop();
                else    
                    starIndex.pop();;
            }
        }

        while(!stackIndex.empty())
        {
            if(starIndex.empty()) return false;
            if(stackIndex.top() > starIndex.top()) return false;
            stackIndex.pop();
            starIndex.pop();
        }

        return true;
    }
};
// T.C -> O(N)
// S.C -> O(N)







// Optimal Soln ------ Using Greedy
class Solution {
public:
    bool checkValidString(string s) {
        int star=0;
        int open=0;
        int usedStar=0;
        
        for(int i=0;i<s.length();i++){
            if(s[i]=='*'){
               star++;
                if(open>=1){
                    usedStar++;
                    open--;
                } 
            } 
            else if(s[i]=='('){
                open++;
            }else{
                if(open>=1) open--;
                else if(usedStar > 0){  
                    usedStar--;
                }else if(star>=1){
                    star--;
                }
                else return false;
            }
        }
        if(open) return false;
        else return true;
        
    }
};

// using star to cancel out '(' if there and if we encounter ')' we will backtrack and to use that '*' here to cancel ')' keep that '*' as space or can be used in future

// T.C -> O(N)
// S.C -> O(1)
int main(){
    return 0;
}
