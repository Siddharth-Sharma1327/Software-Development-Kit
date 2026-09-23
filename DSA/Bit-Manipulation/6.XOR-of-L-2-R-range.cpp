#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// (i) Brute force 
// Using for-loop


// (ii) Optimised 
  
    int func(int N){
        if(N%4==1) return 1;
        if(N%4==2) return (N+1);
        if(N%4==3) return 0;
        if(N%4==0) return N;
    }
    int findXOR(int l, int r) {
        // complete the function here
        return func(l-1)^func(r);
    }

// T.C -> O(1)
// S.C -> O(1)

int main(){
    return 0;
}