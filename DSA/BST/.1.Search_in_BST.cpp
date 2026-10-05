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
    TreeNode* searchBST(TreeNode* root, int val) {
        if(root == NULL) return root;
        if(root->val == val) return root;
        return ((val < root->val) ? searchBST(root->left, val) : searchBST(root->right, val));
    }
};

// Node->val < root->val => left subtree
// Node->val > root->val => right subtree

// T.C -> O(h) where h is the height of the tree = O(logn) for balanced BST and O(n) for skewed BST
// S.C -> O(h) for recursive stack space