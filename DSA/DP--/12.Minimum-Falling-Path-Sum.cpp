// Recursion--
class Solution {
public:
    int minFallingPathSumHelper(int i, int j, int n, vector<vector<int>>& matrix){
        if(i < 0) return 0;

        int sum = INT_MAX;
        for(int k=-1; k<=1; k++){
            if(j+k >= 0 && j+k < n) sum = min(sum, matrix[i][j] + minFallingPathSumHelper(i-1, j+k, n, matrix));
        }
        return sum;
    }
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int ans = INT_MAX;

        for(int j=0; j<n; j++){
            ans = min(ans, minFallingPathSumHelper(n-1, j, n, matrix));
        }
        return ans;
    }
};
// T.C  = O(3^(n*n)) & S.C = O(n) (Recursion Stack Space)


// Memoization--
class Solution {
public:
    int minFallingPathSumHelper(int i, int j, int n, vector<vector<int>>& matrix, vector<vector<int>> &dp){
        if(i < 0) return 0;

        if(dp[i][j] != -1) return dp[i][j];
        int sum = INT_MAX;
        for(int k=-1; k<=1; k++){
            if(j+k >= 0 && j+k < n) sum = min(sum, matrix[i][j] + minFallingPathSumHelper(i-1, j+k, n, matrix, dp));
        }
        return dp[i][j] = sum;
    }
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int ans = INT_MAX;
        vector<vector<int>> dp(n, vector<int>(n, -1));

        for(int j=0; j<n; j++){
            ans = min(ans, minFallingPathSumHelper(n-1, j, n, matrix, dp));
        }
        return ans;
    }
};
// T.C  = O(n*n)*3 & S.C = O(n*n) + O(n) (Recursion Stack Space)

// Tabulation--
class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int ans = INT_MAX;
        // dp[0][0,1,2,....n] = 0
        
        vector<int> prev(n, 0);
        for(int i=1; i<=n; i++){
            vector<int> cur(n, 0);
            for(int j=0; j<n; j++){
                int sum = INT_MAX;
                for(int k=-1; k<=1; k++){
                    if(j+k >= 0 && j+k < n){
                        sum = min(sum, matrix[i-1][j] + prev[j+k]);
                    } 
                }
                cur[j] = sum;
            }
            prev = cur;
        }
        for(int col=0; col<n; col++){
            ans = min(ans, prev[col]);
        }
        return ans;
    }
};
// T.C  = O(n*n)*3 + O(n) & S.C = O(n*n)

// Space Optimization--
class Solution {
public:
    int minFallingPathSumHelper(int i, int j, int n, vector<vector<int>>& matrix, vector<vector<int>> &dp){
        if(i < 0) return 0;

        if(dp[i][j] != -1) return dp[i][j];
        int sum = INT_MAX;
        for(int k=-1; k<=1; k++){
            if(j+k >= 0 && j+k < n) sum = min(sum, matrix[i][j] + minFallingPathSumHelper(i-1, j+k, n, matrix, dp));
        }
        return dp[i][j] = sum;
    }
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int ans = INT_MAX;
        // dp[0][0,1,2,....n] = 0

        vector<int> prev(n, 0);
        for(int i=1; i<=n; i++){
            vector<int> cur(n, 0);
            for(int j=0; j<n; j++){
                int sum = INT_MAX;
                for(int k=-1; k<=1; k++){
                    if(j+k >= 0 && j+k < n){
                        sum = min(sum, matrix[i-1][j] + prev[j+k]);
                    } 
                }
                cur[j] = sum;
            }
            prev = cur;
        }

        for(int col=0; col<n; col++){
            ans = min(ans, prev[col]);
        }
        return ans;
    }
};
// T.C  = O(n*n)*3 + O(n) & S.C = O(n)



