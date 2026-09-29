/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool dfs(TreeNode* leftRoot, TreeNode* rightRoot) {
        if(leftRoot == NULL || rightRoot == NULL) return (leftRoot == rightRoot);
        return (leftRoot->val == rightRoot->val) &&
                dfs(leftRoot->left, rightRoot->right) &&
                dfs(leftRoot->right, rightRoot->left);

    }
    bool isSymmetric(TreeNode* root) {
        if(root == NULL) return true;
        return dfs(root->left, root->right);
    }
};

// Algo
// 1) start multi-source recursion for left and right nodes and compare vice versa for mirror image