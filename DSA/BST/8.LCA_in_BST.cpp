(i) Recursive:-
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
        if(root == NULL) return NULL;
        int curVal = root->val;

        // both lies to the left
        if(p->val < curVal && q->val < curVal){
            return lowestCommonAncestor(root->left, p, q);
        }
        // both lies to the right
        else if(p->val > curVal && q->val > curVal){
            return lowestCommonAncestor(root->right, p, q);
        }

        // one to left and other to right so root = lca
        return root;
    }
};

(ii) Iterative:-
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
        if(root == NULL) return NULL;
        TreeNode* cur = root;

        while(cur != NULL){
            int curVal = cur->val;

            // both lies to the left
            if(p->val < curVal && q->val < curVal){
                cur = cur->left;
            }
            // both lies to the right
            else if(p->val > curVal && q->val > curVal){
                cur = cur->right;
            }
            else{
                return cur;
            }

        }
        return root;
    }
};



// Algo
// 1) If both p and q are smaller than root, then LCA lies in left subtree.
// 2) If both p and q are greater than root, then LCA lies in right subtree.
// 3) If one of p or q is smaller than root and the other is greater than root, then root is the LCA.

// T.C -> O(h) where h is height of tree
// S.C -> O(h) where h is height of tree for recursive and O(1) for iterative