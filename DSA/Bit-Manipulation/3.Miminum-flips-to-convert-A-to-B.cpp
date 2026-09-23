#include<iostream> 
#include<bits/stdc++.h>

using namespace std;

// Approach -1
    int minBitFlips(int start, int goal) {
        int cnt=0;
        for(int i=0;i<=31;i++){
            int bit1=0, bit2=0;
            if(start&(1<<i)) bit1=1;
            if(goal&(1<<i)) bit2=1;
            if(bit1!=bit2) cnt++;
        }
        return cnt;
    }
// T.C -> O(31)
// S.C -> (1)


// Approach -2
    int minBitFlips(int start, int goal) {
        int num = start^goal;
        
        int cnt=0;
        for(int i=0;i<=31;i++){
            if(num&(1<<i)) cnt++;
        }
        return cnt;
    }
// T.C -> O(31)
// S.C -> (1)






// Q2 - Given a non-empty array of integers nums, every element appears twice except for one. Find that single one.
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans=0;
        for(int i=0;i<nums.size();i++) ans = ans^nums[i];
        return ans;
    }
};
// T.C -> O(n)
// S.C -> O(1)


int main(){
    return 0;
}