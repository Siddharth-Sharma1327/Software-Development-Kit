#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// (i)  Recursion----
class Solution {
public:
    
    void f(int i, vector<int> &nums, int n, vector<vector<int>> &ans, vector<int> &temp){
        
        if(i>=n){
            ans.push_back(temp);
            return;
        }
        
        f(i+1, nums, n, ans, temp);
        temp.push_back(nums[i]);
        f(i+1, nums, n, ans, temp);
        temp.pop_back();
        
        return;
    }
    
    vector<vector<int>> subsets(vector<int>& nums) {
        int n= nums.size();
        vector<vector<int>> ans;
        vector<int> temp;
        f(0, nums, n, ans, temp);
        return ans;
    }
};

// T.C -> O(2^N)
// S.C -> O(N) A.S.S





// (ii)  Iteration---------------
class Solution {
public:
    
    vector<vector<int>> subsets(vector<int>& nums) {
        int n= nums.size();
        vector<vector<int>> ans = {{}};
        
        for(int i=0;i<n;i++){
            int constSize = ans.size();
            for(int j=0;j<constSize;j++){
                // vector<int> temp=ans[j];
                ans.push_back(ans[j]);
                ans.back().push_back(nums[i]);
                // ans.push_back(temp);
            }
        }
        
        return ans;
    }
};
// T.C -> (2^N) i.e no of subsets (as at every iteration new subset is created)
// S.C -> O(1) except ans matrix




// (iii) Bit Manipulation-------------
class Solution {
public:
    
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        int p = 1<<n;
        vector<vector<int>> ans;
        for(int i=0;i<p;i++){
            vector<int> temp;
            for(int j=0;j<n;j++){
                if((i&(1<<j))!=0) temp.push_back(nums[j]);
            }
            ans.push_back(temp);
        }
        
        return ans;
    }
};
// T.C -> O(2^N)*O(N)
// S.C -> O(2^N)*O(N) -> temp array for every subset


int main(){
    return 0;
}