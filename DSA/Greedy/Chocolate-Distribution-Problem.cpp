#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Idea is sort the vector and then check for the groups by iterating vector
class Solution{
    public:
    long long findMinDiff(vector<long long> a, long long n, long long m){
    //code
        long long ans=INT_MAX;
        long long i=0,j=m-1;
        sort(a.begin(), a.end());
        while(j<n){
            ans = min(ans, a[j]-a[i]);
            i++,j++;
        }
        return ans;
    }   
};

int main(){
    return 0;
}