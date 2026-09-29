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
    int widthOfBinaryTree(TreeNode* root) {
        if(!root) return 0;
        int ans = 0;
        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});

        while(!q.empty()){
            int size = q.size();
            int minIndex = q.front().second; //to make the index start from zero
            int first, last;
            for(int i=0; i<size; i++){
                int curIndex = q.front().second - minIndex;
                TreeNode* node = q.front().first;
                q.pop();
                if(i == 0) first = curIndex;
                if(i == size-1) last = curIndex;
                if(node->left) q.push({node->left, (long long)curIndex*2 + 1});
                if(node->right) q.push({node->right, (long long)curIndex*2 + 2});
            }
            ans = max(ans, last - first + 1);
        } 
        return ans;
    }
};