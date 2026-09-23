#include<iostream>
#include<bits/stdc++.h>
using namespace std;

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
    vector<int> nums = {10, 12, 15, 18};
    cout << minLength(nums) << endl;
    return 0;
}