#include<iostream>
#include<bits/stdc++.h>
using namespace std;

  bool isPalindrome(int x){
        string s = to_string(x);
        int i=0,j=s.length()-1;
        
        while(j>i){
            
            if(s[i]==s[j]){
                i++;
                j--;
            }else{
                return 0;
            }
        }
        
        return 1;
    }

int main(){
    return 0;
}