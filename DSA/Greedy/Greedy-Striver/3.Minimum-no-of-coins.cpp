#include<iostream>
#include<bits/stdc++.h>
using namespace std;
// Given an infinite supply of each denomination of Indian currency { 1, 2, 5, 10, 20, 50, 100, 200, 500, 2000 } and a target value N.
// Find the minimum number of coins and/or notes needed to make the change for Rs N. You must return the list containing the value of coins required.




// Optimal Soln------ Greedy
class Solution{
public:
    vector<int> minPartition(int N)
    {
        // code here
        int deno[] = {1,2,5,10,20,50,100,200,500,2000};
        vector<int> ans;
        for(int i=9;i>=0;i--){
            int coins = N/deno[i];
            if(coins){
                while(coins){
                    ans.push_back(deno[i]);
                    coins--;
                    N-=deno[i];
                }
            }
        }
        return ans;
    }
};
// T.C -> O(N)
// S.C -> O(N){ans array}

int main(){
    return 0;
}