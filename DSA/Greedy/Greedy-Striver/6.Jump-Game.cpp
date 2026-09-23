#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// Brute force ----- Using Recursion/DP

// T.C -> O(N*N)
//  S.C -> O(N*N)





// Optimal Approch---------- Using Greedy

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int maxReach=0;
        for(int i=0;i<n;i++){
            if(i>maxReach) return false;
            
            maxReach = max(maxReach, i+nums[i]);
        }
        return true;
    }
};

// T.C -> O(N)
// S.C -> O(1)

int main(){
    return 0;
}