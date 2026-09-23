#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// (i) Brute force-----------(Optimal for UNEQUAL +ve & -ve elements)

vector<int> alternateNumbers(vector<int>&a) {
    // Write your code here.
    int n = a.size();
    vector<int> pos, neg;

    for(int i=0;i<n;i++){
        if(a[i]<0) neg.push_back(a[i]);
        else pos.push_back(a[i]);
    }

    // for(int i=0;i<n/2;i++){              ONLY if no. of +ve & -ve are equal 
    //     a[2*i] = pos[i];
    //     a[2*i+1] = neg[i];
    // }

    if(pos.size() > neg.size()){
        for(int i=0;i<neg.size();i++){
            a[2*i] = pos[i];
            a[2*i+1] = neg[i];
        }
        int index = 2*neg.size();
        for(int i=neg.size();i<pos.size();i++){
            a[index] = pos[i];
            index++;
        }
    }else{
        for(int i=0;i<pos.size();i++){
            a[2*i] = pos[i];
            a[2*i+1] = neg[i];
        }
        int index = 2*pos.size();
        for(int i=pos.size();i<neg.size();i++){
            a[index] = neg[i];
            index++;
        }
    }

    return a;
}
// if(+ve & -ve are UNEQUAL) => T.C -> O(N) + O(N)---{min(pos.size(), neg.size()) + leftovers} = {max(pos.size(), neg.size())} = {O(N)}
// if(+ve & -ve are EQUAL) => T.C -> O(N) + O(N/2)
// S.C -> O(N)




// (ii) Optimised Soln---------(Only if array contains EQUAL +ve & -ve elements)
class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, 0);
        int posIndex=0, negIndex=1;
        
        for(int i=0;i<n;i++){
            if(nums[i] < 0){
                ans[negIndex] = nums[i];
                negIndex+=2;
            }else{
                ans[posIndex] = nums[i];
                posIndex+=2;
            }
        }
        return ans;
    }
};
// T.C -> O(N)
// S.C -> O(N)
int main(){
    return 0;
}