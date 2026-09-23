#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// (i) Brute force---------
int longestSubarrayWithSumK(vector<int> a, long long k) {
    // Write your code here
    int n = a.size();
    int l=0;
    for(int i=0;i<n;i++){
        long long sum=0;
        for(int j=i;j<n;j++){
            sum+=a[j];
            if(sum==k){
                l=max(l, j-i+1);
            }
        }
    }
    return l;
}
// T.C -> O(N^2)
// S.C -> O(1)



// (ii) Better Soln------------(Optimal if array has +ve, 0's, '-ve' elements)
int longestSubarrayWithSumK(vector<int> a, long long k) {
    // Write your code here
    int n = a.size();
    map<long long, int> preSumMap;
    long long sum=0;
    int maxLen=0;
    
    for(int i=0;i<n;i++){
        sum+=a[i];

        //if current subarray has sum=k
        if(sum==k){
            maxLen = max(maxLen, i+1);
        }

        //checking if removing some elements from left makes remaining sum=k
        long long rem = sum-k;
        if(preSumMap.find(rem)!=preSumMap.end()){
            int len = i - preSumMap[rem];
            maxLen = max(maxLen, len);
        }


        //handling the case when array contains '0's...here we update index of any 'sum' 
        // ....only if it is not there already...and after that we don't as we try take
        //.....the longest subarray so we take left part as left as possible
        if(preSumMap.find(sum)==preSumMap.end()){
            preSumMap[sum] = i;
        }

    }

    return maxLen;
}

// T.C -> O(NLogN)
// S.C -> O(N)

// (iii) Optimal Soln------(Two Pointer)  (Only if array have +ve, 0's elements & NO -ve's)

int longestSubarrayWithSumK(vector<int> a, long long k) {
    // Write your code here
    int n = a.size();
    long long sum=a[0];
    int maxLen=0;
    int left=0;
    int right=0;

    while(right<n){
        while(left<=right && sum>k){
            sum-=a[left];
            left++;
        }

        if(sum==k){
            maxLen = max(maxLen, right-left+1);
        }

        right++;
        if(right<n) sum+=a[right];
    }

    return maxLen;
}
// T.C -> O(2N)
// S.C -> O(1)

int main(){
    return 0;
}