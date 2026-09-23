#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Idea is that simply sort the candies array then and iterate from beginning for min-amount and from back for max-amount----------
class Solution
{
public:
    vector<int> candyStore(int candies[], int N, int K)
    {
        // Write Your Code here
        vector<int> ans(2, 0);
        vector<int> cand;
        int cnt=0;
        for(int i=0;i<N;i++) cand.push_back(candies[i]);
        sort(cand.begin(), cand.end());
        int i=0;
        while(cnt<N && i<N){
            cnt+=(1+K);
            ans[0]+=cand[i];
            ans[1]+=cand[N-1-i];
            i++;
        }
        return ans;
    }
};


int main(){
    return 0;
}