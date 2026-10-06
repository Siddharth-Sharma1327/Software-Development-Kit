class Solution {
public:
    TreeNode* buildBST(vector<int> &preorder, int i, int uBound) {
        if(i == preorder.size() || preorder[i] > uBound) return NULL;

        TreeNode* root = new TreeNode(preorder[i++]);
        root->left = buildBST(preorder, i, root->val);
        root->right = buildBST(preorder, i, uBound);
        return root;

    }
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int i = 0;
        return buildBST(preorder, i, INT_MAX);
    }
};



// Algo 
