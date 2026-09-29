Level order traversal :-
/*
class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = right = NULL;
    }
};
*/

class Solution {
  public:
    
    vector<int> bottomView(Node *root) {
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
            mp[col] = node->data;
            if(node->left) q.push({node->left, col - 1});
            if(node->right) q.push({node->right, col + 1});
        }
        
        for(auto &it : mp){
            ans.push_back(it.second);
        }
        return ans;
    }
};


Recursion:-
/*
class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = right = NULL;
    }
};
*/

class Solution {
  public:
     void dfs(Node* root, map<int, pair<int,int>> &mp, int col, int level) {
        if(root == NULL) return;
        if(mp.find(col) == mp.end() || mp[col].second <= level){
            mp[col] = {root->data, level};
        }
        if(root->left) dfs(root->left, mp, col - 1, level + 1);
        if(root->right) dfs(root->right, mp, col + 1, level + 1);
    }
    
    vector<int> bottomView(Node *root) {
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


// level order traversal
// T.C -> O(N)*O(Log(Col)) + O(Col)
// S.C -> O(N) + O(Col)


// recursion
// T.C -> O(N)*O(Log(Col)) + O(Col)
// S.C -> O(H)=O(N) + O(Col)


// Algo
// 1) store a map by going on left first and then to right and update val for each col in it with checking levels
// 2) need to store levels as well beacuse lower level for same column might update higher level val for same col which ietrated earlier