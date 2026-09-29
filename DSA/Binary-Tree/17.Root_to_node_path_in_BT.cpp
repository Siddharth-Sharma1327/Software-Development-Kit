Q1 ->
  bool getPath(TreeNode* root, vector<int> &ans, int x) {
        if(root == NULL) return false;
        ans.push_back(root->val);
        if(root->val == x) return true;
        return getPath(root->left, ans, x) || getPath(root->right, ans, x);
        ans.pop_back();
        return false;

    }
    bool hasPath(TreeNode* A, int B) {
        vector<int> ans;
        if(A == NULL) return ans;
        getPath(A, ans, B);
        return ans;
    }

// T.C -> O(N)
// S.C -> O(H)= O(N)

Q2 ->
class Solution {
  public:
    void findRootToLeafPaths(Node* root, vector<vector<int>> &ans, vector<int> &temp) {
        if(root == NULL) return;
        temp.push_back(root->data);
        if(root->left == NULL && root->right == NULL){
            ans.push_back(temp);
            temp.pop_back();
            return;
        }
        findRootToLeafPaths(root->left, ans, temp);
        findRootToLeafPaths(root->right, ans, temp);
        temp.pop_back();
    }
        
    vector<vector<int>> Paths(Node* root) {
        // code here
        vector<vector<int>> ans;
        vector<int> temp;
        if(root == NULL) return ans;
        findRootToLeafPaths(root, ans, temp);
        return ans;
    }
};


// T.C -> o(N)
// S.C -> O(N) + O(H)= O(N)


// Algo
// 1) try all possible paths with backtracking 