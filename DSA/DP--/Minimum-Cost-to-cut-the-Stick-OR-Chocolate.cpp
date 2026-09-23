#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Through my method by storing the nxt cut and prev cut of any partition-----But through this method we have four variables changing so tabulation is not possible 
int main(){
    return 0;
}


// Throught Recursion/Memoisation----------------------
class Solution {
public:
    int minCostHelper(int i, int j, vector<int> &cuts, vector<vector<int>> &dp){
        if(i > j) return 0;
        if(dp[i][j] != -1) return dp[i][j];

        int mini = 1e9;
        for(int k=i; k<=j; k++){
            int cost = cuts[j+1] - cuts[i-1] + minCostHelper(i, k-1, cuts, dp) + minCostHelper(k+1, j, cuts, dp);
            if (cost < mini) {
                mini = cost;
            }
            
        }
        return dp[i][j] =  mini == 1e9 ? 0 : mini;
    }
    int minCost(int n, vector<int>& cuts) {
        int c = cuts.size();
        cuts.push_back(n);
        cuts.insert(cuts.begin(), 0);
        sort(cuts.begin(), cuts.end());
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return minCostHelper(1, c, cuts, dp);
    }
};
// Recursion -- T.C = O(4^c)(Catalan numbers) & S.C = O(c^2) + O(c) (Recursion Stack Space)
// Memoisation -- T.C = O(c^3) & S.C = O(c^2) + O(c) (Recursion Stack Space)


// Tabulation----------------------
class Solution {
public:
    int minCostHelper(int i, int j, vector<int> &cuts, vector<vector<int>> &dp){
        if(i > j) return 0;
        if(dp[i][j] != -1) return dp[i][j];

        int mini = 1e9;
        for(int k=i; k<=j; k++){
            int cost = cuts[j+1] - cuts[i-1] + minCostHelper(i, k-1, cuts, dp) + minCostHelper(k+1, j, cuts, dp);
            if (cost < mini) {
                mini = cost;
            }
            
        }
        return dp[i][j] =  mini == 1e9 ? 0 : mini;
    }
    int minCost(int n, vector<int>& cuts) {
        int c = cuts.size();
        cuts.push_back(n);
        cuts.insert(cuts.begin(), 0);
        sort(cuts.begin(), cuts.end());
        vector<vector<int>> dp(c+2, vector<int>(c+2, 0));
        // return minCostHelper(1, c, cuts, dp);

        for(int i=0; i<=c; i++){
            for(int j=0; j<i; j++){
                dp[i][j] = 0;
            }
        }

        for(int i=c; i>=1; i--){
            for(int j=i; j<=c; j++){
                int mini = 1e9;
                for(int k=i; k<=j; k++){
                    int cost = cuts[j+1] - cuts[i-1] + dp[i][k-1] + dp[k+1][j];
                    if (cost < mini) {
                        mini = cost;
                    }
                    
                }
                dp[i][j] =  mini == 1e9 ? 0 : mini;
            }
        }
        return dp[1][c];
    }
};

// Tabulation ---------
// T.C = O(C^3)  + CLOGC
// S.C = O(C^2)