#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// (i) Brute force ----- Using Dp -> Recursion - Memoisation - Tabulation
class Solution {
public:
    
//     int f(int i, vector<int> &nums, int n, vector<int> &dp){
        
//         if(i>=n-1) return 0;
//         if(dp[i]!=-1) return dp[i];
//         int mini=1e9;
//         for(int j=1;j<=nums[i];j++){
//             if(i+j<n){
//                 int jump = 1 + f(i+j, nums, n, dp);
//                 mini = min(mini, jump);
//             }
            
//         }
//         return dp[i] = mini;
//     }
    
    int jump(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 0);
        // return f(0, nums, n, dp);
        dp[n-1]=0;
        
        for(int i=n-2;i>=0;i--){
            int mini=1e9;
            for(int j=1;j<=nums[i];j++){
                        if(i+j<n && nums[i+j]!=0){
                        int jump = 1 + dp[i+j];
                        mini = min(mini, jump);
                        dp[i] = mini;
                    }
                }
                
            }
        return dp[0];
    }
};
// T.C -> O(N*N)
// S.C -> O(N)








// (ii) Optimal Approach - 1------ Using Greedy (My Way)
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        // int maxReach=nums[0];
        int steps=nums[0];
        int maxIndex=0;
        int cnt=0;
        
        for(int i=1;i<n;i++){
            if(i+nums[i]>maxIndex + nums[maxIndex]){
                // maxReach = i+nums[i];
                maxIndex = i;
            }
            steps--;
            
            if(steps==0 || i==n-1){
                steps = nums[maxIndex]- (i - maxIndex);
                cnt++;
            }
        }
        return cnt;
    }
};

// T.C -> O(N)
// S.C -> O(1)


// (iii) OPtimal Approach - 2------ Using Greedy (Striver Way)

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        
        int jumps = 0;
        int l = 0;
        int r = 0;
        
        while( r < n - 1 ){
            int farthest = 0;
            
            for( int i = l; i <= r; i++ ){           // here u are iterating the range of maxIndex and finding the next 'maxIndex' to jump on
                farthest = max( farthest, i + nums[i] );
            }
            
            l = r + 1;
            jumps++;
            r = farthest;
        }
        
        return jumps;
    }
};


// T.C -> O(N)
// S.C -> O(1)
int main(){
    return 0;
}