    #include<iostream>
#include<bits/stdc++.h>
using namespace std;




// Check if 'n' is power of 2---------

class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n<=0) return false;
        double d = log2(n);
        if(d == floor(d)) return true;
        else return false;
    }
};



// Check if 'n' is power of 3---------
class Solution {
public:
    bool isPowerOfThree(int n) {
        if(n<=0) return false;
        double d = log10(n)/log10(3);
        // cout<<(int)d<<" "<<floor(d);
        if(d==(double)(int)d ) return true;
        else return false;
    }
};




// Check if 'n' is power of 4---------

class Solution {
public:
    bool isPowerOfFour(int n) {
        double d = log(n)/log(4);
        double temp = d - floor(d); 
        if(temp==0) return true;
        else return false;
    }
};

// Other ways to do above are-----
// 1) Recursion
// 2) Iteration(loops)
// 3) Bit manipulation---can be 2/3 methods of bit manipulation



// All time complexity is O(1) & space compllexity is also O(1)
int main(){
    return 0;
}



// C++ floor() Function-----
// The floor() function returns the largest integer that is smaller than or equal to the value passed as 
// the argument (i.e.: rounds down the nearest integer).

// floor() Syntax




// C++ ceil() Function
// ceil() function in C++ returns the smallest integer that is greater than or equal to the value passed as 
// the argument (i.e.: rounds up the nearest integer).

// Syntax of ceil()