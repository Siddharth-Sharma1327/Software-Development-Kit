(i) My soln:-
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

    pair<int, bool> isSubtreeBalanced(TreeNode* root) {
        if(root == NULL) return {0, true};

        auto leftSubtree = isSubtreeBalanced(root->left);
        auto rightSubtree = isSubtreeBalanced(root->right);

        int leftSubtreeHt = leftSubtree.first + 1;
        int rightSubtreeHt = rightSubtree.first + 1;
        bool status = leftSubtree.second && rightSubtree.second && (abs(leftSubtreeHt - rightSubtreeHt) <= 1 ? true : false);
        return {max(leftSubtreeHt, rightSubtreeHt), status};

    }

    bool isBalanced(TreeNode* root) {
        return isSubtreeBalanced(root).second;
    }
};


(ii) Striver soln:-
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

    int dfshHeight(TreeNode* root) {
        if(root == NULL) return 0;

        int leftHt = dfshHeight(root->left);
        if(leftHt == -1) return -1;
        int rightHt = dfshHeight(root->right);
        if(rightHt == -1) return -1;

        if(abs(leftHt - rightHt) > 1) return -1;
        return max(leftHt, rightHt) + 1;;
    }

    bool isBalanced(TreeNode* root) {
        return dfshHeight(root) != -1;
    }
};