/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void markParents(TreeNode* root, unordered_map<TreeNode*, TreeNode*> &parentTrack, TreeNode* traget) {
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            if(node->left) {
                parentTrack[node->left] = node;
                q.push(node->left);
            }
            if(node->right) {
                parentTrack[node->right] = node;
                q.push(node->right);
            }
        }
    }
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        unordered_map<TreeNode*, TreeNode*> parentTrack; // node -> parent
        markParents(root, parentTrack, target);

        unordered_map<TreeNode*, bool> visited;
        queue<TreeNode*> q;
        q.push(target);
        visited[target] = true;
        int curLevel = 0;

        while(!q.empty()) { // second BFS to go upto K level from target node and using our hashtable info
            int size = q.size();
            if(curLevel++ == k) break;
            for(int i=0; i<size; i++){
                TreeNode* current = q.front();
                q.pop();

                if(current->left && !visited[current->left]) {
                    q.push(current->left);
                    visited[current->left] = true;
                }
                if(current->right && !visited[current->right]) {
                    q.push(current->right);
                    visited[current->right] = true;
                }
                TreeNode* parentNode = parentTrack[current];
                if(parentNode && !visited[parentNode]) {
                    q.push(parentNode);
                    visited[parentNode] = true;
                }
            }
        }

        vector<int> ans;
        while(!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            ans.push_back(node->val);
        }

        return ans;
    }
};



// T.C -> O(N) + O(N)
// S.C -> O(N) * 3 + O(H)

//Algo - break this tree into graph and use simple bfs then
// 1) first we will do BFS and store the parent of each node in a hashtable
// 2) then we will do BFS from target node and go upto K level and store all the nodes in a vector and return it
// 3) we will use a hashtable to keep track of visited nodes so that we don't go in a loop

// one more soln
class Solution {
public:
    void markParentOfNodes(TreeNode* root, unordered_map<TreeNode*, TreeNode*> &parentTrack, TreeNode* parent){
        if(root == NULL) return;
        parentTrack[root] = parent;
        if(root->left) markParentOfNodes(root->left, parentTrack, root);
        if(root->right) markParentOfNodes(root->right, parentTrack, root);
    }
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        vector<int> ans;
        if(root == NULL) return ans;
        unordered_map<TreeNode*, TreeNode*> parentTrack;
        unordered_map<TreeNode*, bool> visited;
        markParentOfNodes(root, parentTrack, NULL);
        queue<pair<TreeNode*, int>> q;
        q.push({target, 0});
        visited[target] = true;

        while(!q.empty()) {
            TreeNode* node = q.front().first;
            int dist = q.front().second;
            q.pop();

            if(dist == k){
                ans.push_back(node->val);
                continue;
            } 
            if(node->left && !visited[node->left]){
                q.push({node->left, dist + 1});
                visited[node->left] = true;
            } 
            if(node->right && !visited[node->right]){
                q.push({node->right, dist + 1});
                visited[node->right] = true;
            } 
            TreeNode* parent = parentTrack[node];
            if(parent && !visited[parent]){
                q.push({parent, dist + 1});
                visited[parent] = true;
            }
            
        }
        return ans;
    }
};