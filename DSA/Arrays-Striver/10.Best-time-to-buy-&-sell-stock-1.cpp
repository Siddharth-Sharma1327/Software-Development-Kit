#include<iostream>
#include<bits/stdc++.h>
using namespace std;
// int maxProfit(vector<int>& prices) {
//         int n = prices.size();
       
//        int mn = INT_MAX;
//        int ans = INT_MIN;
       
//        for(int i=0;i<n;i++){
//            mn = min(mn, prices[i]);
//            ans = max(ans, prices[i]-mn);
//        }
//        return ans;
// }
// // T.C -> O(N)
// // S.C -> O(1)




int gcd(int a, int b) {
    return a % b == 0 ? b : gcd(b, a % b);
}

int minLength(vector<int>& nums) {
    // Step 1: Sort the array
    sort(nums.begin(), nums.end());

    // Step 2: Merge adjacent elements
    int i = 0;
    while (i < nums.size() - 1) {
        int a = nums[i];
        int b = nums[i+1];
        int gcd_ab = gcd(a, b);
        int lcm_ab = (a * b) / gcd_ab;
        nums[i] = gcd_ab;
        nums[i+1] = lcm_ab;
        i++;
    }

    // Step 3: Repeat step 2 until all adjacent elements are relatively prime
    while (true) {
        bool changed = false;
        i = 0;
        while (i < nums.size() - 1) {
            int a = nums[i];
            int b = nums[i+1];
            if (gcd(a, b) > 1) {
                int gcd_ab = gcd(a, b);
                int lcm_ab = (a * b) / gcd_ab;
                nums[i] = gcd_ab;
                nums[i+1] = lcm_ab;
                changed = true;
            }
            i++;
        }
        if (!changed) {
            break;
        }
    }

    // Step 4: Return the length of the resulting array
    return nums.size();
}

int main() {
    vector<int> nums = {1, 4, 3, 1};
    cout << minLength(nums) << endl;
    return 0;
}

// int main(){
//     return 0;
// }