#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Simple idea to rdeuce cost everytime add the two lowest ones--
class Solution
{
    public:
    //Function to return the minimum cost of connecting the ropes.
    unsigned long long minCost(long long arr[], long long n) {
        // Your code here
        unsigned long long ans=0;
        if(n==1) return 0;
        priority_queue<long long, vector<long long>, greater<long long>> minheap;
        for(long long i=0;i<n;i++) minheap.push(arr[i]);
        while(!minheap.empty()){
            long long x,y;
            x=minheap.top();
            minheap.pop();
            y=minheap.top();
            minheap.pop();
            ans+=x+y;
            if(minheap.empty()) return ans;
            minheap.push(x+y);
        }
    }
};

int main(){
    return 0;
}