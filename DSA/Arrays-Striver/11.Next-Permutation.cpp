#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Using Recursion----------------------(BRUTE FORCE)
// (i) Brute force----In recursion
class Solution { 
private:
    void solve(vector<int> &ds, vector<int> &nums, vector<vector<int>> &ans, vector<int> freq){
        if(ds.size()==nums.size()){
            ans.push_back(ds);
            return;
        }
        
        for(int i=0;i<nums.size();i++){
            if(!freq[i]){
                ds.push_back(nums[i]);
                freq[i]=1;
                solve(ds, nums, ans, freq);
                freq[i]=0;
                ds.pop_back();
            }
        }
        return;
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        int n=nums.size();
        vector<vector<int>> ans;
        vector<int> ds;
        vector<int> freq(n, 0);
        solve(ds, nums, ans, freq);
        return ans;
    }
};

// T.C -> O(N!*N)
// S.C -> O(N) + O(N) + O(N) {A.S.S + DS + MAP}




// (ii) Optimal solution----In recursion

class Solution {  
private:
    void f(int index, vector<int> &nums, vector<vector<int>> &ans){
        if(index==nums.size()){
            ans.push_back(nums);
            return;
        }
        
        for(int i=index;i<nums.size();i++){
            swap(nums[i], nums[index]);
            f(index+1, nums, ans);
            swap(nums[i], nums[index]);
        }
        return;
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {

        int n=nums.size();
        vector<vector<int>> ans;
        f(0, nums, ans);
        return ans;
    }
};
// T.C -> O(N!*N)
// S.C -> O(N) {A.S.S}







// USING STL--------------------(BETTER SOLN)

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        int n=nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        ans.push_back(nums);
        while(next_permutation(nums.begin(), nums.end())){
            ans.push_back(nums);
        }
        return ans;
    }
};
// T.C -> O(NLogN) + O(N!*N)
// S.C -> O(1)     {NO A.S.S}




// OPTIMAL SOLN------OR--Implementation of STL(next_permutation( , ))--
vector<int> nextGreaterPermutation(vector<int> &A) {
    // Write your code here.
    int index=-1;
    int n = A.size();

    for(int i=n-2;i>=0;i--){
        if(A[i]<A[i+1]){
            index=i;
            break;
        }
    }

    if(index==-1){
        reverse(A.begin(), A.end());
        return A;
    }

    for(int i=n-1;i>index;i--){
        if(A[i]>A[index]){
            swap(A[i], A[index]);
            break;
        }
    }

    reverse(A.begin()+index+1, A.end());
    return A;
}
// T.C -> O(3N)
// S.C -> O(1)

int main(){
    return 0;
}