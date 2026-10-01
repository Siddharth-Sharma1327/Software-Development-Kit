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
    int bfsToFindTimeToBurnTree(unordered_map<TreeNode*, TreeNode*> &mp, TreeNode* target){
        queue<TreeNode*> q;
        q.push(target);
        unordered_map<TreeNode*, bool> visited;
        visited[target] = true;
        int time = 0;
        while(!q.empty()){
            int size = q.size();
            int flag = 0;
            for(int i=0; i<size; i++){
                TreeNode* node = q.front();
                q.pop();

                if(node->left && !visited[node->left]){
                    flag = 1;
                    visited[node->left] = true;
                    q.push(node->left);
                }

                if(node->right && !visited[node->right]){
                    flag = true;
                    visited[node->right] = true;
                    q.push(node->right);
                }
                TreeNode* parentNode = mp[node];
                if(parentNode && !visited[parentNode]){
                    flag = true;
                    visited[parentNode] = true;
                    q.push(parentNode);
                }
            }

            if(flag) time++;
        }
        return time;
    }
    TreeNode* bfsToMapParents(TreeNode* root, unordered_map<TreeNode*, TreeNode*> &mp, int start) {
        queue<TreeNode*> q;
        q.push(root);
        TreeNode* target;
        while(!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            if(node->val == start) target = node;
            if(node->left){
                mp[node->left] = node;
                q.push(node->left);
            }
            if(node->right){
                mp[node->right] = node;
                q.push(node->right);
            }
        }
        return target;
    }

    int amountOfTime(TreeNode* root, int start) {
        unordered_map<TreeNode*, TreeNode*> mp;
        TreeNode* target = bfsToMapParents(root, mp, start);
        int time = bfsToFindTimeToBurnTree(mp, target);
        return time;
    }
};



// Algo
// 1) We will do a BFS traversal of the tree and map each node to its parent in a hash map. This will allow us to easily access the parent of any node during the burning process.
// 2) We will then perform another BFS traversal starting from the target node (the node
// where the fire starts) and keep track of the time taken to burn the entire tree. We will use a queue to keep track of the nodes that are currently burning and a visited set to avoid revisiting nodes.
// 3) For each node that is burning, we will check its left child, right child, and parent (if it exists) and add them to the queue if they haven't been visited yet. We will increment the time counter for each level of BFS until all nodes have been burned.


// T.C -> O(N) + O(N)
// S.C -> O(N) + O(N)*2
