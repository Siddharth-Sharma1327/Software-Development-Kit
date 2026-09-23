#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// (i) Using Map---------------------------
    int singleNumber(vector<int>& nums) {
        int n = nums.size();
        map<int,int> mp;
        
        for(int i=0;i<n;i++) mp[nums[i]]++;
        for(auto it: mp){
            if(it.second==1) return it.first;
        }
        return -1;
    }
// T.C -> O(N*LogM) + O(M)  M-> size of map M=n/3+1
// S.C -> O(M)




// (ii) Using Bit Manipulation---------------
    int singleNumber(vector<int>& nums) {
        int n = nums.size();
        int ans=0;
        for(int i=0;i<=31;i++){
            int cnt=0;
            for(int j=0;j<n;j++){
                if((nums[j]&(1<<i))) cnt++;
            }
            if(cnt%3!=0) ans = ans | (1<<i);
        }
        return ans;
    }
// T.C -> O(31)*O(N)
// S.C -> O(1)



// (iii) Using Sorting------------------------
    int singleNumber(vector<int>& nums) {
        int n = nums.size();                  // 0 1 2 3 4 5 6 7 8 9
        sort(nums.begin(), nums.end());       // 1 1 1 2 2 2 3 4 4 4 
        for(int i=1;i<n;i+=3){
            if(nums[i]!=nums[i-1]) return nums[i-1];
        }
        return nums[n-1];
    }
// T.C -> O(NLogN) + O(N/3)      (NLogN) < N*31----because LogN=31 for n=2^31 worst case, so worst case was used for all cases previously but here log(size)
// S.C -> O(1)




// (iv) Bucket Method-------------------------




int main(){
    return 0;
}