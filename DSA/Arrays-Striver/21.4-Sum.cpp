#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Everthing is same 3-sum....just increase of one pointer


// (i) Brute force------------
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    // Write your code here
    int n = nums.size();
    set<vector<int>> st;

    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            for(int k=j+1;k<n;k++){
                for(int l=k+1;l<n;l++){
                    long long sum=nums[i];
                    sum+=nums[j];
                    sum+=nums[k];
                    sum+=nums[l];

                    if(sum == target){
                        vector<int> temp = {nums[i], nums[j], nums[k], nums[l]};
                        sort(temp.begin(), temp.end());
                        st.insert(temp);
                    }
                }
            }
        }
    }

    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}
// T.C -> O(N^4)*O(Log(no. of quadraples))
//  S.C -> 2*O(Log(No. of Quadrapels))





// (ii) Better soln------------
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    // Write your code here
    int n = nums.size();
    set<vector<int>> st;

    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            set<int> hashSet;
            for(int k=j+1;k<n;k++){
                long long sum=nums[i];
                sum+=nums[j];
                sum+=nums[k];
                long long fourth = target - sum;
                if(hashSet.find(fourth) != hashSet.end()){
                    vector<int> temp = {nums[i], nums[j], nums[k], (int)fourth};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }

                hashSet.insert(nums[k]);
            }
        }
    }
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}
// T.C -> O(N^3)*(O(Log(M) + O(Log(no. of quadraples)))   ...M=hashSet size
// S.C -> O(N) + 2*O(no. of quadraples)






// (iii) Optimal Soln------------
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    // Write your code here
    int n = nums.size();
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());

    for(int i=0;i<n;i++){
        if(i>0 && nums[i]==nums[i-1]) continue;

        for(int j=i+1;j<n;j++){
            if(j>i+1 && nums[j]==nums[j-1]) continue;

            int k = j+1;
            int l = n-1;

            while(k<l){
                long long sum=nums[i];
                sum+=nums[j];
                sum+=nums[k];
                sum+=nums[l];

                if(sum < target){
                    k++;
                }else if(sum > target){
                    l--;
                }else{
                    vector<int> temp = {nums[i], nums[j], nums[k], nums[l]};
                    ans.push_back(temp);

                    k++;
                    l--;

                    while(k<l && nums[k]==nums[k-1]) k++;
                    while(k<l && nums[l]==nums[l+1]) l--;
                }
            }
        }
    }
    return ans;
}

// T.C -> O(NLogN) + O(N^3)
// S.C -> O(no. of quadraples)


int main(){
    return 0;
}