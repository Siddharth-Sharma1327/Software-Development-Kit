#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Through Recursion--
int f(int ind, vector<int> &heights, int k, int n){
    if(ind==0) return 0;

    int min_cost = INT_MAX;

    for(int j=1;j<=k;j++){
        if(ind>=j) min_cost = min(min_cost, f(ind-j, heights, k, n) + abs(heights[ind]-heights[ind-j]));
    }

    return min_cost;
}

int frogJump(int n, vector<int> &heights, int k)
{   
    // Write your code here.
    return f(n-1, heights, k, n);
}
// T.C -> O(k^N)
//  S.C -> O(N) a.s.s



// Through Memoisation-------
int f(int ind, vector<int> &heights, int k, int n, vector<int> &dp){
    if(ind==0) return 0;

    if(dp[ind]!=-1) return dp[ind];
    int min_cost = INT_MAX;

    for(int j=1;j<=k;j++){
        if(ind>=j) min_cost = min(min_cost, f(ind-j, heights, k, n, dp) + abs(heights[ind]-heights[ind-j]));
    }

    return dp[ind] = min_cost;
}

int frogJump(int n, vector<int> &heights, int k)
{   
    // Write your code here.
    vector<int> dp(n, -1);
    return f(n-1, heights, k, n, dp);
}

// T.C -> O(N*k)
//  S.C -> O(N) a.s.s + O(N)



// Through Tabulation----
int frogJump(int n, vector<int> &heights, int k)
{   
    // Write your code here.
    vector<int> dp(n, 0);
    // return f(n-1, heights, k, n, dp);

    dp[0]=0;

    for(int ind=1;ind<n;ind++){

        int min_cost = INT_MAX;
        for(int j=1;j<=k;j++){
            if(ind>=j) min_cost = min(min_cost, dp[ind-j] + abs(heights[ind]-heights[ind-j]));
        }

        dp[ind] = min_cost;
    }
    return dp[n-1];
}

// T.C -> O(N*k)
//  S.C -> O(N)


// Space Optimisation is not worth it as in worst case we have to store the complete n array length only so not better solution

int main(){
    return 0;
}


int frogJump(vector<int>& heights, int k) {
    int n = heights.size();
    deque<int> window; // stores dp values of last k indices
    window.push_back(0); // dp[0] = 0

    for(int i = 1; i < n; i++){
        int steps = INT_MAX;
        int wSize = window.size(); // at most k elements
        for(int j = 0; j < wSize; j++){
            int ind = i - wSize + j; // actual index in heights
            if(window[j] != INT_MAX)
                steps = min(steps, abs(heights[i] - heights[ind]) + window[j]);
        }
        window.push_back(steps);
        if((int)window.size() > k) window.pop_front();
    }
    return window.back();
}
// T.C -> O(N*k)
//  S.C -> O(k)