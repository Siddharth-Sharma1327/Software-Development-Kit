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
    int kthSmallest(TreeNode* root, int k) {
        int cnt = 0, ans = -1;
        if(root == NULL) return ans;

        TreeNode* cur = root;
        while(cur != NULL) {
            // case 1
            if(cur->left == NULL){
                cnt++;
                if(cnt == k) ans = cur->val;   
                cur = cur->right;
            }
            // case 2
            else{
                TreeNode* prev = cur->left;
                while(prev->right && prev->right != cur){
                    prev = prev->right;
                }

                if(prev->right == NULL){
                    prev->right = cur;
                    cur = cur->left;
                }else{
                    prev->right = NULL;
                    cnt++;
                    if(cnt == k) ans = cur->val;
                    cur = cur->right;
                }
            }
        }

        return ans;
    }
};

// Algo
// 1) Inorder traversal of BST is sorted order of elements in BST
// 2) So we did morris traversal with cnt

// T.C -> O(n) where n is number of nodes in BST
// S.C -> O(1) 