// Recursion--
class Solution {
public:
    int minPathSumHelper(int i, int j, vector<vector<int>> &grid){
        if(i==0 && j==0) return grid[0][0];

        int up = INT_MAX, left = INT_MAX;
        if(i >= 1) up = grid[i][j] + minPathSumHelper(i-1, j, grid);
        if(j >= 1) left = grid[i][j] + minPathSumHelper(i, j-1, grid);

        return min(left, up);
    }

    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        return minPathSumHelper(n-1, m-1, grid);
    }
};
// T.C  = O(2^(n*m)) & S.C = O(n+m) (Recursion Stack Space)


//Memoization--
class Solution {
public:
    int minPathSumHelper(int i, int j, vector<vector<int>> &grid, vector<vector<int>> &dp){
        if(i==0 && j==0) return grid[0][0];
        if(dp[i][j] != -1) return dp[i][j];

        int up = INT_MAX, left = INT_MAX;
        if(i >= 1) up = grid[i][j] + minPathSumHelper(i-1, j, grid, dp);
        if(j >= 1) left = grid[i][j] + minPathSumHelper(i, j-1, grid, dp);

        return dp[i][j] =  min(left, up);
    }


    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return minPathSumHelper(n-1, m-1, grid, dp);
    }
};
// T.C  = O(n*m) & S.C = O(n*m) + O(n+m) (Recursion Stack Space)


// Tabulation--
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));
        // return minPathSumHelper(n-1, m-1, grid, dp);
        dp[0][0] = grid[0][0];

        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(i==0 && j==0) continue;
                int up = INT_MAX, left = INT_MAX;
                if(i >= 1) up = grid[i][j] + dp[i-1][j];
                if(j >= 1) left = grid[i][j] + dp[i][j-1];
                dp[i][j] = min(left, up);
            }
        }
        return dp[n-1][m-1];
    }

};
// T.C  = O(n*m) & S.C = O(n*m)

// Space Optimization--
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<int> prev(m, 0);
        // return minPathSumHelper(n-1, m-1, grid, dp);
        prev[0] = grid[0][0];

        for(int i=0; i<n; i++){
            vector<int> cur(m, 0);
            for(int j=0; j<m; j++){
                if(i==0 && j==0){
                    cur[j] = grid[i][j];
                    continue;
                } 
                int up = INT_MAX, left = INT_MAX;
                if(i >= 1) up = grid[i][j] + prev[j];
                if(j >= 1) left = grid[i][j] + cur[j-1];
                cur[j] = min(left, up);
            }
            prev = cur;
        }
        return prev[m-1];
    }

};
// T.C  = O(n*m) & S.C = O(m)