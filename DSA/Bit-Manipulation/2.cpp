#include<iostream>
#include<bits/stdc++.h> 
using namespace std;


// Swap two numbers------
void  swapUsingBitwise(int &x, int &y){
    x = x^y;
    y = x^y;
    x = x^y;
    return;
}
// T.C -> O(1)
// S.C -> O(1)





// Set the kth bit 
void  setKthBit(int &x, int k){
    x = x | (1<<k);
    return;
}
// T.C -> O(1)
// S.C -> O(1)






// Unset/clear the kth bit
void  unsetKthBit(int &x, int k){
    x  = x & ~(1 << k);
    return;
}
// T.C -> O(1)
// S.C -> O(1)





// Toggle the kth bit
void  toggleKthBit(int &x, int k){
    x = x^(1<<k);
    return;
}
// T.C -> O(1)
// S.C -> O(1)




// Remove the last set bit (from left-to-right)
void removeLastSetBit(int x){
    x = x & (x-1);
    return;
}
// T.C -> O(1)
// S.C -> O(1)




// Count the no of set bits in 'n'------------------------------------------
// (1)
int setBits(int N) {
    // Write Your Code here
    int cnt=0;
    while(N){
        cnt += (N&1);
        N = N>>1;
    }
    return cnt;
}
// T.C -> O(Log2(N))
// S.C -> O(1)

// (2) - Better Approach
int setBits(int N) {
    // Write Your Code here
    int cnt=0;
    while(N!=0){
        N = N&(N-1);
        cnt++;
    }
    return cnt;
}
// T.C -> O(no. of set bits) = O(31) at worst
// S.C -> O(1)









//Set the right most unset bit only if it exists like don't consider leading zeroes of a number eg. 7 -> 111, 15-> 1111 no zeros there
// (1)
    int setBit(int N)
    {
        // Write Your Code here
        for(int i=0;i<=31;i++){
            if((1<<i) > N) break;
            if((N & (1<<i)) == 0){
                N = N | (1<<i);
                break;
                // return N;
            }
        }
        return N;
    }
// T.C -> O(31)
// S.C -> O(1)

// (2)
    int setBit(int N)
    {
        // Write Your Code here
        if(!(N&(N+1))) return N;    // eg 7-> 111 and 7+1 -> 1000 so 7&(7+1)==0 so return 7 in that case
        else return N | (N+1);
    }
// T.C -> O(1)
// S.C -> O(1)





int main(){
    return 0;
}