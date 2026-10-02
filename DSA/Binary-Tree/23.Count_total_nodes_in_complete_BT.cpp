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

    int findLeftHeight(TreeNode* root){
        int height = 0;
        while(root){
            height++;
            root = root->left;
        }
        return height;
    }  

    int findRightHeight(TreeNode* root){
        int height = 0;
        while(root){
            height++;
            root = root->right;
        }
        return height;
    }   

    int countNodes(TreeNode* root) {
        if(root == NULL) return 0;

        int lh = findLeftHeight(root);
        int rh = findRightHeight(root);

        if(lh == rh) return (1 << lh) - 1;

        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};


// Algo
// 1) compute left tree height and right tree height
// 2) if they are same then tree is fully complete BT return 2^h - 1
// 3) if not then do same for left and right sub-trees
// 4) remember tree is CBT, so at any point in recursion we only go to left OR right as either one of them will be CBT, so we traverse half side only at any node
// 5) so we only go in depth to the side of tree which is not CBT

// T.C -> O(LogN) * 2 (for height calculations at each level) * LogN (numbe rof levels = height) = O(LogN)*O(LognN)
// S.C -> O(H) = O(LogN)=O(N)(worst)