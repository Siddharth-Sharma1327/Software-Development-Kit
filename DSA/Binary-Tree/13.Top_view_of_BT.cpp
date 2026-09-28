Level Order Traversal - (striver soln) :-
/*
class Node {
  public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};
*/

class Solution {
  public:
    
    vector<int> topView(Node *root) {
        // code here
        vector<int> ans;
        if(root == NULL) return ans;
        map<int, int> mp; //{col, val}
        queue<pair<Node*, int>> q; // {node, col}
        q.push({root, 0});
        
        while(!q.empty()) {
            auto it = q.front();
            q.pop();
            Node* node = it.first;
            int col = it.second;
            if(mp.find(col) == mp.end()) mp[col] = node->data;
            if(node->left) q.push({node->left, col - 1});
            if(node->right) q.push({node->right, col + 1});
        }
        
        for(auto &it : mp){
            ans.push_back(it.second);
        }
        return ans;
    }
};



Recursion - (my soln) :-
/*
class Node {
  public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};
*/

class Solution {
  public:
    
    void dfs(Node* root, map<int, pair<int,int>> &mp, int col, int level) {
        if(root == NULL) return;
        if(mp.find(col) == mp.end() || mp[col].second > level){
            mp[col] = {root->data, level};
        }
        if(root->left) dfs(root->left, mp, col - 1, level + 1);
        if(root->right) dfs(root->right, mp, col + 1, level + 1);
    }
    
    vector<int> topView(Node *root) {
        // code here
        vector<int> ans;
        if(root == NULL) return ans;
        map<int, pair<int, int>> mp; //{col, {val, level}}
        dfs(root, mp, 0, 0);
        for(auto &it : mp){
            ans.push_back(it.second.first);
        }
        return ans;
    }
};


// Algo
// 1) if use recursion then carry level as higher level value might have updated before the lower one
// 2) in level order traversal dont need to store level as we traverse level wise

// for level order soln
// T.C -> O(N)*O(Log(Col)) + O(Col)
// S.C -> O(N) + O(Col)

// for recursion soln
// T.C -> O(N)*O(Log(Col)) + O(Col)
// S.C -> O(H)=O(N) + O(Col)