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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root == NULL) return NULL;

        if(root->val < key) {
            root->right = deleteNode(root->right, key);
        }
        if(root->val > key) {
            root->left = deleteNode(root->left, key);
        }
        if(root->val == key) {
            TreeNode* leftTreeNode = root->left;
            TreeNode* rightTreeNode = root->right;
            if(rightTreeNode == NULL) return leftTreeNode;
            else {
                TreeNode* leftMostOfRightTree = rightTreeNode;
                while(leftMostOfRightTree->left) {
                    leftMostOfRightTree = leftMostOfRightTree->left;
                }
                leftMostOfRightTree->left = leftTreeNode;
                root = rightTreeNode;
            }
        }

        return root;
    }
};


// Algo
// 1) cases -> node to delete -> root node, leaf node, node with one child, or normal any node
// 2) after deletion BST should hold so join th left and right sub trees properly 
// 3) if node withv left child null return right child, if right child null return left child and
// 3) if both child != null then find the left most node in right sub tree and attach whole left subtree to the left of that node

// T.C. O(n) in worst case when tree is skewed, O(log n) in average case, recursion can also be oprtimised to iteration here
// S.C -> O(h) where h is the height of the tree, in worst case h = n, in average case h = log n
// S.C -> O(1) if we use iteration instead of recursion