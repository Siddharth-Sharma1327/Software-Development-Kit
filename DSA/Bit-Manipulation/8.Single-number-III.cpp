#include<iostream>
#include<bits/stdc++.h>
using namespace std;


//(i) Brute force------Using Hashing
// using maps
// T.C -> O(MLogM) + O(M)  === M = N/2 + 1
// S.C -> O(M)





// (ii) Better approach-----------Using Sorting
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<int> ans;
        
        for(int i = 0; i < n; i++){
            
            if(i == 0){
                if(nums[i] != nums[i + 1]) ans.push_back(nums[0]);
            }else if( i == n-1){
                if(nums[i] != nums[i - 1]) ans.push_back(nums[n - 1]);
            }else{
                if( nums[i] != nums[i - 1] && nums[i] !=  nums[i + 1]) ans.push_back(nums[i]);
            }
        }
        
        return ans;
        
    }
};
// T.C -> O(NLogN) + O(N)
// S.C -> O(1)







// (iii) Optimal Solution ------ Bit Manipulation Bucket concept
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int n = nums.size();
        
        long xorr = 0;
        
        for(int i = 0; i < n; i++){
            xorr = xorr^nums[i];
        }
        
        long rightMost = (xorr & (xorr - 1))^xorr;     // (xorr & (~(xorr-1)))----rightmost set bit value
        
        int bucket1 = 0;
        int bucket2 = 0;
        
        for(int i = 0; i < n; i++){
            
            if( (nums[i] & rightMost) != 0){
                bucket1 = bucket1^nums[i];
            }else{
                bucket2 = bucket2^nums[i];
            }
        }
        
        return {bucket1, bucket2};
        
    }
};
// T.C -> O(N)
// S.C -> O(1)

int main(){
    return 0;
}