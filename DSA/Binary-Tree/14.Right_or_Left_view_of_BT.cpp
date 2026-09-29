// using recursion
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
    void dfsRightSideView(TreeNode* root, int level, vector<int> &ans){
        if(root == NULL) return;
        if(level == ans.size()) ans.push_back(root->val);
        dfsRightSideView(root->right, level+1, ans);
        dfsRightSideView(root->left, level+1, ans);
    }
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        dfsRightSideView(root, 0, ans);
        return ans;
    }
};


// T.C -> O(N)
// S.C -> O(H) = O(N)



// using level orde traversal
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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        if(root == NULL) return ans;
        queue<TreeNode*> q;
        q.push(root);

        while(!q.empty()){
            int size = q.size();
            for(int i = 0; i < size; i++){
                TreeNode* node = q.front();
                q.pop();
                if(i == size-1) ans.push_back(node->val);

                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
        }
        return ans;
    }
};


// T.C -> O(N)
// S.C -> O(N)



// Algo
// 1) do recursion compare the level of each  node with ans size store onlyy for 1st time it came for that level
// 2) do level order traversal and check frist or last value of that level for left or rihgt view