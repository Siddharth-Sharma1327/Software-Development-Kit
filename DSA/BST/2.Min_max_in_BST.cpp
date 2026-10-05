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