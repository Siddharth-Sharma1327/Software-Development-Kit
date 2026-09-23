#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// (i) Brute force------Bit manipulation
    int getBits(int x) {
        int count = 0;
        while (x) {
            x &= x - 1;
            count++;
        }
        return count;
    }

    
    int countSetBits(int n)
    {
        // Your logic here
        int ans = 0;
        
        for( int i = 1; i <= n; i++){
            ans += getBits(i);
        }
        return ans;
         
    }

// T.C -> O(N*Log(N))
// S.C -> O(1)









// (iii) Better approach ------- Using DP

// Every even number (n) has the same amount of bits as (n/2).
// Every odd number (n) has the amount of bits as (n/2) + 1.
    
    int countSetBits(int n)
    {
        // Your logic here
        int ans = 0;
        vector<int> dp(n + 1, 0);
        
        for( int x = 1; x <= n; x++){
            dp[x] = dp[x / 2] + (x % 2);
            ans += dp[x];
        }
        
        return ans;
         
    }

// T.C -> O(N)
// S.C -> O(N)










// (iii) Optimal Approach----- (Video from Pep Coding)
    int maxPower2(int n){
        int x = 0;
        
        while( (1<<x) <= n){
            x++;
        }
        
        return x - 1;
    }
    
    
    int countSetBits(int n)
    {
        // Your logic here
        if( n == 0) return 0;
        
        int x = maxPower2(n);   // max power of 2 <= n
        
        int btill2x = x * (1 << (x - 1));     // sum of bits of numbers from 1 to 2^(x)-1
        int msb2xton = n - (1 << x) + 1;      // sum of all set bits from 2^x to n at leftMost bit position
        int rest = n - (1 << x);              // sum of remaining set bits from 2^x to n after LeftMost bit positions
        
        int ans = btill2x + msb2xton + countSetBits(rest);    // aggregate
        
        return ans;
         
    }


// T.C -> O(Log(N))    as at worst rest = n/2 everytime
// S.C -> O(Log(N))    recursion stack space












// (iV) MOst Optimal (GFG Edotorial)


// T.C -> O(Log(N))   
// S.C -> O(1)  





int main(){
    return 0;
}