// Heap -> 1) Complete Binary Tree,
        // 2) follows Heap order property


/*
class Node {
   public:
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};
*/

class Solution {
  public:
    int countTotalNodesInBinaryTree(Node* root){
        if(root == NULL) return 0;

        return 1 + countTotalNodesInBinaryTree(root->left) + countTotalNodesInBinaryTree(root->right);
    }
    bool isCBT(Node* root, int index, int cnt){
        if(root == NULL) return true;
        if(index > cnt) return false;

        bool left = isCBT(root->left, 2 * index, cnt);
        bool right = isCBT(root->right, 2 * index + 1, cnt);

        return left && right;
    }
    bool isCompleteTree(Node* root) {
        int cnt = countTotalNodesInBinaryTree(root);
        return isCBT(root, 1, cnt);
    }
    
    bool isMaxOrder(Node* root){
        // 1) leaf node
        if(root == NULL || (root->left == NULL && root->right == NULL)) return true;
        
        // 2) node with only left child
        if(root->right == NULL){
            return root->data > root->left->data && isMaxOrder(root->left);
        }
        
        // 3) node with two children
        return root->data > root->left->data && root->data > root->right->data &&
               isMaxOrder(root->left) && isMaxOrder(root->right);
    }
    
    bool isHeap(Node* tree) {
        // code here
        return isCompleteTree(tree) && isMaxOrder(tree);      
    }
}; 

// T.C = O(N)*3
// S.C = O(H)
 