#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Tricky Question----------
class Solution{
public:
    int minimumDays(int S, int N, int M){
        // code here
        if(N<M) return -1;
        if(N==M){
            if(S>6) return -1;
            else return S;
        }else{
            if(S>6){
                if((N-M)*6>=M){
                if((S*M)%N==0) return (S*M)/N;
                else return (S*M)/N + 1;
                }else return -1;
            }else{
                 if((S*M)%N==0) return (S*M)/N;
                else return (S*M)/N + 1;
            }
        }
     
    }
};
int main(){
    return 0;
}