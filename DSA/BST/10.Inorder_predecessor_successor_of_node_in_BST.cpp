/* Structure of a Binary Search Tree node
class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = nullptr;
        right = nullptr;
    }
}; */

class Solution {
  public:
    vector<Node*> findPreSuc(Node* root, int key) {
        // code here
                vector<Node*> ans;
                Node* pred = NULL, *succ = NULL;
                Node* cur = root;

                // find succ
                while(cur) {
                    if(cur->data <= key) {
                        cur = cur->right;
                    }else{
                        succ = cur;
                        cur = cur->left;
                    }
                }

                // find pred
                cur = root;
                while(cur) {
                    if(cur->data >= key) {
                        cur = cur->left;
                    }else {
                        pred = cur;
                        cur = cur->right;
                    }
                }
                ans.push_back(pred);
                ans.push_back(succ);
                return ans;
        
    }
};


// Algo 
// 1) In BST, for a node with value key, the inorder successor is the node with the smallest value greater than key, and the inorder predecessor is the node with the largest value smaller than key.
// 2) To find the inorder successor, we can start from the root and traverse the tree. If the current node's value is less than or equal to key, we move to the
    // right subtree. If the current node's value is greater than key, we update the successor to the current node and move to the left subtree. We continue this process until we reach a null node.
// 3) To find the inorder predecessor, we can start from the root and traverse the tree. If the current node's value is greater than or equal to key, we move to the
    // left subtree. If the current node's value is less than key, we update the predecessor to the current node and move to the right subtree. We continue this process until we reach a null node.
// 4) Finally, we return the predecessor and successor as a vector of Node pointers

// T.C -> O(h) where h is height of BST
// S.C -> O(1)
