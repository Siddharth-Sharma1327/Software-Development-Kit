MY SOLN :-
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
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        vector<vector<int>> ans;
        map<int, vector<int>> mp;
        if( root == NULL ) return ans;
        queue<pair<TreeNode*, int>> q;
        q.push({root, 0});

        while(!q.empty()){
            int size = q.size();
            map<int, multiset<int>> levelToColWiseMap;

            for(int i=0; i<size; i++){
                TreeNode* node = q.front().first;   
                int curCol = q.front().second;
                q.pop();

                levelToColWiseMap[curCol].insert(node->val);
                if(node->left) q.push({node->left, curCol - 1});
                if(node->right) q.push({node->right, curCol + 1});
            }

            for(auto &it : levelToColWiseMap){
                int col = it.first;
                multiset<int> elements = it.second;
                // sort(elements.begin(), elements.end());
                mp[col].insert(mp[col].end(), elements.begin(), elements.end());
            }
        }
        for (auto &it : mp) {
            ans.push_back(it.second);
        }
        return ans;
    }
};


STRIVER SOLN:-
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
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        vector<vector<int>> ans;
        map<int, map<int, multiset<int>>> mp; // {col, {level, set}}
        queue<pair<TreeNode*, pair<int,int>>> q; // {node, {col, level}}
        q.push({root, {0, 0}});
        
        while(!q.empty()){
            auto p = q.front();
            q.pop();
            TreeNode* node = p.first;
            int x = p.second.first, y = p.second.second;
            mp[x][y].insert(node->val);
            if(node->left) q.push({node->left, {x-1, y+1}});
            if(node->right) q.push({node->right, {x+1, y+1}});
        }
        for(auto p : mp) {
            vector<int> col;
            for(auto q : p.second) {
                col.insert(col.end(), q.second.begin(), q.second.end());
            }
            ans.push_back(col);
        }
        return ans;
    }
};


// Algo
// 1) Recursion is tricky here as values will get stored in mismatch order for any level
// 2) we use level order traversal, but cant use 'ans' directly inside it as we dont know the number of levels before
// 3) we store col wise level wise multisets (sorts value auto and also keeps duplicates if there)
// 4) later we comine all mutlisets for each level 

// T.C -> O(N) + O(Col * level)
// S.C -> O(3*N) + O(col * Level + O(N))