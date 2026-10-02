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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> inMap;
        for(int i=0; i < inorder.size(); i++){
            inMap[inorder[i]] = i;
        }

        TreeNode* root = buildTree(preorder, 0, preorder.size()-1,
                                    inorder, 0, inorder.size()-1, inMap);

        return root;
    }

    TreeNode* buildTree(vector<int> &preorder, int preStart, int preEnd,
                        vector<int> &inorder, int inStart, int inEnd, unordered_map<int,int> &inMap) {
        
        if(preStart > preEnd || inStart > inEnd) return NULL;

        TreeNode* root = new TreeNode(preorder[preStart]);

        int inRoot = inMap[root->val];
        int numsLeft = inRoot - inStart;

        root->left = buildTree(preorder, preStart + 1, preStart + numsLeft,
                                inorder, inStart, inRoot - 1, inMap);

        root->right = buildTree(preorder, preStart + numsLeft + 1, preEnd,
                                inorder, inRoot + 1, inEnd, inMap);      

        return root;                          
    }
};



// Algo
// 1) store the map of inorder values with their index to get root in o(1)
// 2) find root from preorder, then split inorder into left and right halves which are left and right sub-trees inorder 
// 3) compute x elements on left of root in inorder - those many more after root node in preorder are preorder of left sub tree and remaining are preorder of right sub tree
// 4) repeat  this process in recursion to build tree

// T.C -> O(N) + O(N)
// S.C -> O(N) + O(H)