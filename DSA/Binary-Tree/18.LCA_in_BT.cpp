/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == NULL || root == p || root == q) {
            return root;
        }
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        if(left == NULL) return right;
        else if(right == NULL) return left;
        else return root;          // both left and right not null, got our result
    }
};


// Algo
// 1) compute left and right for each node
// 2) when is a leaf node return null to up
// 3) as soon as you get any node from two just return that up
// 4) so at some point or node you will get these both nodes returned i.e left and right both are not null so that is the lca and return that up


// T.C -> O(N)
// S.C -> O(H)=O(N)