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

// Algo
// 1) store {node, index} in queue and find lastIndex - firstIndex for each level
// 2) now doing this for left/right skewed tree the indedx values will overflow, so we do shifting of index for each level
// 3) all nodes indices in each level start from 0 from left to right

// T.C -> O(N)
// S.C -> O(N)