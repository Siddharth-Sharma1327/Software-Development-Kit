#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Q.2 Check whether kth bit set from right in n----------------

bool isKthBitSet(int n, int k)
{
    // Write your code here.
    return (n & (1<<(k-1)));
}
// T.C -> O(1)
// S.C -> O(1)




// Q.3 Check whether N is odd or even ----------------

string oddEven(int N){
    // Write your code here.
    if((N&1)==1) return "odd";
    else return "even";
}
// T.C -> O(1)
// S.C -> O(1)




// Q.4 Check whether number is power of 2---------------

class Solution {
public:
    bool isPowerOfTwo(int n) {
        // if(n<=0) return false;
        // double d = log2(n);
        // if(d == floor(d)) return true;
        // else return false;
        
        // if(n!=0 && (n & (n-1))==0) return true;
        // return false;
        if(n<=0) return  false;
        return ((n&(n-1))==0);
    }
};
// T.C -> O(1)
// S.C -> O(1)







int main(){
    return 0;
}