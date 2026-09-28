/*
class Node {
  public:
    int data;
    Node* left;
    Node* right;

    // Constructor to initialize a new node
    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};
*/

class Solution {
  public:
    bool isLeaf(Node* root){
        return (root->left == NULL && root->right == NULL);
    }
    void addLeftBoundary(Node* root, vector<int> &ans){
        Node* cur = root->left;
        while(cur){
            if(!isLeaf(cur)) ans.push_back(cur->data);
            if(cur->left) cur = cur->left;
            else cur = cur->right;
        }
    }
    
    void addLeafNodes(Node* root, vector<int> &ans){
        
        if(isLeaf(root)){
            ans.push_back(root->data);
            return;
        }
        
        if(root->left) addLeafNodes(root->left, ans);
        if(root->right) addLeafNodes(root->right, ans);
        
    }
    
    void addRightBoundary(Node* root, vector<int> &ans){
        Node* cur = root->right;
        vector<int> temp;
        while(cur){
            if(!isLeaf(cur)) temp.push_back(cur->data);
            if(cur->right) cur = cur->right;
            else cur = cur->left;
        }
        
        for(int i=temp.size()-1; i>=0; i--){
            ans.push_back(temp[i]);
        }
    }
    vector<int> boundaryTraversal(Node *root) {
        // code here
        vector<int> ans;
        if (!root) return ans;
        if (!isLeaf(root)) ans.push_back(root->data);
        addLeftBoundary(root, ans);
        addLeafNodes(root, ans);
        addRightBoundary(root, ans);
        return ans;
    }
};