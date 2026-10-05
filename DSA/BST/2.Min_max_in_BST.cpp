class Solution {
  public:
    int minValue(Node* root) {
        // code here
        if(root->left == NULL) return root->data; 
        return minValue(root->left);
    }
};


class Solution {
  public:
    int maxValue(Node* root) {
        // code here
        if(root->right == NULL) return root->data; 
        return maxValue(root->right);
    }
};

// T.C -> O(h) where h is the height of the tree = O(logn) for balanced BST and O(n) for skewed BST
// S.C -> O(h) for recursive stack space

