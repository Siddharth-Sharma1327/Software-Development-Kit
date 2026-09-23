#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// (i) Brute force----
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> ans;
        int n = nums.size();
        for(int i=0;i<n;i++){
            if(ans.size()==0 || ans[0]!=nums[i]){
                int cnt=0;
                for(int j=0;j<n;j++){
                    if(nums[j]==nums[i]) cnt++;
                }
                if(cnt > n/3) ans.push_back(nums[i]);
            }
            if(ans.size()==2) break;
        }
        return ans;
    }
};
// T.C -> O(N^2)
// S.C -> O(1)


// (ii) Better Soln------
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> ans;
        int n = nums.size();
        int maxElementsPossible= (int)n/3 + 1; 
        
        map<int,int> mp;
        for(int i=0;i<n;i++){
            mp[nums[i]]++;
            
            if(mp[nums[i]]==maxElementsPossible){
                ans.push_back(nums[i]);
            }
            if(ans.size()==2) break;
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};
// T.C -> O(NLogN){map} Or O(N)/O(N^2){unordered_map}
// S.C -> O(N)



// (iii) OPtimal Soln------------
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {

        //No O(n) space as ans vector is of size 2 only so O(1)
        vector<int> ans;
        
        int n = nums.size();
        int cnt1=0, cnt2=0;
        int ele1=INT_MIN;
        int ele2=INT_MIN;
        
        for(int i=0;i<n;i++){
            
            if(cnt1==0 && ele2!=nums[i]){
                cnt1=1;
                ele1=nums[i];
            }else if(cnt2==0 && ele1!=nums[i]){
                cnt2=1;
                ele2=nums[i];
            }else if(ele1==nums[i]) cnt1++;
            else if(ele2==nums[i]) cnt2++;
            else{
                cnt1--;
                cnt2--;
            }
            
        }
        
        cnt1=0;
        cnt2=0;
        for(int i=0;i<n;i++){
            if(nums[i]==ele1) cnt1++;
            if(nums[i]==ele2) cnt2++;
        }
        int mini = (int)n/3 + 1;
        
        if(cnt1>= mini) ans.push_back(ele1);
        if(cnt2>= mini) ans.push_back(ele2);

        // No nlogn as sorting of only two elements
        sort(ans.begin(), ans.end());
        
        return ans;
    }
};
// T.C -> O(N) + O(N)
//  S.C -> O(1)

int main(){
    return 0;
}