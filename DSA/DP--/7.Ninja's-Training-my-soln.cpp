#include<iostream>
#include<bits/stdc++.h>
using namespace std;

//Through Recursion-------------
int f(int ind, int i, vector<vector<int>> &points){
    
     if(ind==0) return points[0][i];

     if(i==0){
        int take0 = points[ind][0] + max(f(ind-1, 1, points), f(ind-1, 2, points));

        return take0;
     } 
     if(i==1){
       int take1 = points[ind][1] + max(f(ind-1, 0, points), f(ind-1, 2, points));

       return take1;
     } 
     if(i==2){
       int take2 = points[ind][2] + max(f(ind-1, 0, points), f(ind-1, 1, points));

       return take2;
     } 

}

int ninjaTraining(int n, vector<vector<int>> &points)
{
//     Write your code here.
    if(n==1) return max(points[0][0], max(points[0][1], points[0][2]));
    
    return max(f(n-1, 0, points), max(f(n-1, 1, points), f(n-1, 2, points)));
    
}



//Through memoization-----------
int f(int ind, int i, vector<vector<int>> &points, vector<vector<int>> &dp){
    
     if(ind==0) return points[0][i];
     if(dp[ind][i]!=-1){
        return dp[ind][i]; 
     } 
     if(i==0){
        int take0 = points[ind][0] + max(f(ind-1, 1, points, dp), f(ind-1, 2, points, dp));
        dp[ind][i]=take0;
        return take0;
     } 
     if(i==1){
       int take1 = points[ind][1] + max(f(ind-1, 0, points, dp), f(ind-1, 2, points, dp));
       dp[ind][i]=take1;
       return take1;
     } 
     if(i==2){
       int take2 = points[ind][2] + max(f(ind-1, 0, points, dp), f(ind-1, 1, points, dp));
       dp[ind][i]=take2;
       return take2;
     } 

}

int ninjaTraining(int n, vector<vector<int>> &points)
{
    // Write your code here.
    if(n==1) return max(points[0][0], max(points[0][1], points[0][2]));
    vector<vector<int>> dp(n, vector<int>(3, -1));
    
    return max(f(n-1, 0, points, dp), max(f(n-1, 1, points, dp), f(n-1, 2, points, dp)));
    
}



//Through Tabulation------------
int ninjaTraining(int n, vector<vector<int>> &points)
{
   
    vector<vector<int>> dp(n, vector<int>(3, 0));
    
    for(int i=0;i<3;i++){
        dp[0][i]=points[0][i];
    }
    for(int ind=1;ind<n;ind++){
        for(int i=0;i<3;i++){
              if(i==0){
                int take0 = points[ind][0] + max(dp[ind-1][1], dp[ind-1][2]);
                dp[ind][i]=take0;
                
             } 
             if(i==1){
               int take1 = points[ind][1] + max(dp[ind-1][0], dp[ind-1][2]);
               dp[ind][i]=take1;
               
             } 
             if(i==2){
               int take2 = points[ind][2] + max(dp[ind-1][0], dp[ind-1][1]);
               dp[ind][i]=take2;
               
             } 
        }
    }
    
    return max(dp[n-1][0], max(dp[n-1][1], dp[n-1][2]));
    
}



//Through Space Optimisation----------
int ninjaTraining(int n, vector<vector<int>> &points)
{

    
    int prev = points[0][0];
    int prev1 = points[0][1];
    int prev2 = points[0][2];
    for(int ind=1;ind<n;ind++){
        int take0=0;
        int take1=0;
        int take2=0;
        for(int i=0;i<3;i++){
              if(i==0){
                 take0 = points[ind][0] + max(prev1, prev2);

        
                
             } 
             if(i==1){
                take1 = points[ind][1] + max(prev, prev2);

               
             } 
             if(i==2){
                take2 = points[ind][2] + max(prev, prev1);

               
             } 
        }
        
        prev=take0;
        prev1=take1;
        prev2=take2;
    }
    
        return max(prev, max(prev1, prev2));
    
}



// Actual Approach:-
//Recursion
class Solution {
  public:
    int maximumPointsHelper(int i, vector<vector<int>> &mat, int lastDaySkill){
        if(i < 0) return 0;
        
        int points = 0;
        for(int j=0; j<3; j++){
            if( j != lastDaySkill){
                points = max(points, mat[i][j] + maximumPointsHelper(i-1, mat, j));
            }
        }
        return points;
    }
    int maximumPoints(vector<vector<int>>& mat) {
        // code here
        int n = mat.size();
        // 0 - running
        // 1 - fighting
        // 2 - learning
        
        return maximumPointsHelper(n-1, mat, -1);
    }
};

// T.C = O(2^N)*3
// S.C = O(N)

// Memoisation:-
class Solution {
  public:
    int maximumPointsHelper(int i, vector<vector<int>> &mat, int lastDaySkill, vector<vector<int>> &dp){
        if(i < 0) return 0;
        
        if(lastDaySkill !=-1 && dp[i][lastDaySkill] != -1) return dp[i][lastDaySkill];
        int points = 0;
        for(int j=0; j<3; j++){
            if( j != lastDaySkill){
                points = max(points, mat[i][j] + maximumPointsHelper(i-1, mat, j, dp));
            }
        }
        if(lastDaySkill == -1) return points;
        return dp[i][lastDaySkill] = points;
    }
    int maximumPoints(vector<vector<int>>& mat) {
        // code here
        int n = mat.size();
        // 0 - running
        // 1 - fighting
        // 2 - learning
        vector<vector<int>> dp(n, vector<int>(3, -1));
        
        return maximumPointsHelper(n-1, mat, -1, dp);
    }
};
// T.C = O(N)*3
// S.C = O(N) + O(NX3)


// Tabulation:-
class Solution {
  public:

    int maximumPoints(vector<vector<int>>& mat) {
        // code here
        int n = mat.size();
        // 0 - running
        // 1 - fighting
        // 2 - learning
        // 3 - no skill
        vector<vector<int>> dp(n, vector<int>(3, 0));
        
        dp[0][0] = max(mat[0][1], mat[0][2]);
        dp[0][1] = max(mat[0][0], mat[0][2]);
        dp[0][2] = max(mat[0][0], mat[0][1]);
        
        for(int i=1; i<n; i++){
            for(int last=0; last<3; last++){
                int points = 0;
                for(int j = 0; j<3; j++){
                    if(last != j){
                        points = max(points, mat[i][j] + dp[i-1][j]);
                    }  
                }
                dp[i][last] = points;
            }
        }
        
        return max(dp[n-1][0], max(dp[n-1][1], dp[n-1][2]));
    }
};

// T.C = O(NX3X3) = O(N)
// S.C = O(NX3)


// Space Optimisation:-
class Solution {
  public:

    int maximumPoints(vector<vector<int>>& mat) {
        // code here
        int n = mat.size();
        // 0 - running
        // 1 - fighting
        // 2 - learning
        // 3 - no skill
        vector<int> prev(3, 0);
        
        prev[0] = max(mat[0][1], mat[0][2]);
        prev[1] = max(mat[0][0], mat[0][2]);
        prev[2] = max(mat[0][0], mat[0][1]);
        
        for(int i=1; i<n; i++){
            vector<int> cur(3, 0);
            for(int last=0; last<3; last++){
                int points = 0;
                for(int j = 0; j<3; j++){
                    if(last != j){
                        points = max(points, mat[i][j] + prev[j]);
                    }  
                }
                cur[last] = points;
            }
            prev = cur;
        }
        
        return max(prev[0], max(prev[1], prev[2]));
    }
};

// T.C = O(NX3X3) = O(N)
// S.C = O(3) = O(1)