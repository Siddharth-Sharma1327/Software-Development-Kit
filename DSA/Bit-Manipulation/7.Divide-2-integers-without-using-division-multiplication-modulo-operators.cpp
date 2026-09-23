#include<iostream>
#include<bits/stdc++.h>

using namespace std;


// (i) Naive Solution-----
class Solution {
public:
    int divide(int dividend, int divisor) {
   
        int sum  = 0;
        int cnt = 0;
        
        while(sum + divisor <= dividend){
            
            cnt = cnt + 1;
            sum += divisor;
        }
        
        return sum;
        
    }
};

// T.C -> O(dividend) = O(2^31) at divisor=1
// S.C -> O(1)







// (ii) Optimises Approach-----(Bit Manipulation)
class Solution {
public:
    int divide(int dividend, int divisor) {
        
        if(dividend == divisor) 
            return 1;
        
        bool sign = true;   // +ve
        
        if(dividend >= 0 && divisor < 0) sign = false;   // -ve
        else if(dividend <= 0 && divisor > 0) sign = false;     // -ve
        
        long n = abs(dividend);    // here 'long' because if dividend = -2^31(int can have it)..  
        long d = abs(divisor);     // ..the  abs(dividend) = 2^31 can't represent by int
        long ans = 0;
        
        while( n >= d){
            int cnt = 0;
             
            while( n>= (d<<(cnt +1)) ){
                cnt++;
            }
            
            ans += 1<<cnt;
            n -= (d<<cnt);
        }
        
        if(ans == 1<<31 && sign == true)
            return INT_MAX;
        
        if(ans == 1<<31 && sign == false)
            return INT_MIN;
        
        return sign ? ans : -ans;

    }

};


// T.C -> O(N*LogN)*O(N*LogN) = O(N*LogN)^2 
// S.C -> O(1)




int main(){
    return 0;
}