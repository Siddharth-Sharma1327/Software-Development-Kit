#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// (i) Brute force-----
// Using three loops
// T.C -> O(N^3)
// S.C -> O(1)



// (ii) Better soln-----
// Using two loops
// T.C -> O(N^2)
// S.C -> O(1)


// (iii) Optimal Soln---------
int findAllSubarraysWithGivenSum(vector < int > & arr, int k) {
    // Write Your Code Here
    unordered_map<int,int> mp;  // O(1) OR O(N)
    //  map<int,int> mp;      // LogN
    mp[0]=1;
    int prefSum=0, cnt=0;

    for(int i=0;i<arr.size();i++){
        prefSum+=arr[i];
        int remain = prefSum - k;
        cnt += mp[remain];
        mp[prefSum]++;
    }

    return cnt;
}

// T.C -> O(N*LogN){if ordered map} OR O(N){if uordered_map but O(N*N) in its worst case }
// S.C -> O(N)
int main(){
    return 0;
}