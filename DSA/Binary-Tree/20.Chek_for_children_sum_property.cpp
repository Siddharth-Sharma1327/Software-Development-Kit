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
    void changeTree(Node *root) {
        // code here
        if(root == nullptr) return;
        int child = 0;
        if(root->left) {
            child += root->left->data;
        }
        if(root->right) {
            child += root->right->data;
        }
        
        if(child >= root->data) root->data = child;
        else {
            if(root->left) root->left->data = root->data;
            else if(root->right) root->right->data = root->data;
        }
        
        changeTree(root->left);
        changeTree(root->right);
        
        int tot = 0;
        if(root->left) tot += root->left->data;
        if(root->right) tot += root->right->data;
        if(root->left || root->right) root->data = tot;
    }
    /* Structure of a Tree Node
class Node {
public:
    int data;
    Node* left, *right;
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
}; */

    bool isSumProperty(Node *root) {
        // code here
        if(root == nullptr || (root->left == nullptr && root->right == nullptr)) return true;

        int leftNodeVal = 0, rightNodeVal = 0;
        if(root->left) leftNodeVal = root->left->data;
        if(root->right) rightNodeVal = root->right->data;
        return ((leftNodeVal + rightNodeVal == root->data) && 
                isSumProperty(root->left) && isSumProperty(root->right));
    }
};


// Algo
// 1) if leaf node then its valid 
// 2) compute leftNode and rightNode val and cechk sum = root->val and then check for same left and right tree


// T.C -> o(N)
// S.C -> O(H)=O(N)