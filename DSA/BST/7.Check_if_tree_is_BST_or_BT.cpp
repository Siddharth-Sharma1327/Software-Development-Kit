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
    bool isValidBSTHelper(TreeNode* root, long maxi, long mini) {
        if(root == NULL) return true;

        if(root->val <= mini || root->val >= maxi) return false;
        
        return isValidBSTHelper(root->left, root->val, mini) &&
                isValidBSTHelper(root->right, maxi, root->val);
    }
    bool isValidBST(TreeNode* root) {
        if(root == NULL) return false;
        return isValidBSTHelper(root, LONG_MAX, LONG_MIN);
    }
};



// Algo
// 1) compute the range for each node in between which its value should lie i.e max and min for each  node
// send these upto the bottom of tree and check

// T.C -> O(n) where n is number of nodes in BST
// S.C -> O(h) where h is height of tree


// can alsoe be done by bottom-up approach where we can return the min and max of each subtree and check if the current node is in between them or not
// but for this we need to create struct for each node ciontianing min and max of subtree and also a bool to check if the subtree is valid or not