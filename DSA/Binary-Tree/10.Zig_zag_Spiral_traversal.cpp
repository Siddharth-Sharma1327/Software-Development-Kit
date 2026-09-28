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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(root == NULL) return ans;

        queue<TreeNode*> nodesQueue;
        nodesQueue.push(root);
        bool leftToRight = true;

        while(!nodesQueue.empty()){

            int size = nodesQueue.size();
            vector<int> level(size);
            for(int i = 0; i < size; i++){
                TreeNode* node = nodesQueue.front();
                nodesQueue.pop();
                
                // find position to fill node's value
                int index = (leftToRight) ? i : (size - 1 - i);
                level[index] = node->val;
                if(node->left) nodesQueue.push(node->left);
                if(node->right) nodesQueue.push(node->right);
            }
            //level complete
            leftToRight = !leftToRight;
            ans.push_back(level);
        }
        return ans;
    }
};



// Algo
// 1) we push nodes into queue from left to right only normal way
// 2) we just compute the index of poped node to be pushed intot level array

// T.C -> O(N)
// S.S -> O(N)