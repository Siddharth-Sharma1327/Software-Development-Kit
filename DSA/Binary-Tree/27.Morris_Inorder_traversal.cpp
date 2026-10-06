
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
    
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> inorder;
        if(root == NULL) return inorder;

        TreeNode* cur = root;

        while(cur != NULL) {

            // case 1
            if(cur->left == NULL) {              // reached the leftmost node so add it since LNR
                inorder.push_back(cur->val);
                cur = cur->right;               // now got to root via thread
            }

            // case 2
            else {                               // cur ->left != NULL means two cases when we form thread from rightmost node of left sub tree to root node OR when we have to remove thread
                TreeNode* prev = cur->left;
                while(prev->right && prev->right != cur) {  // this loop runs both time upto rightmost node when to form thread or remove it
                    prev = prev->right;
                }

                if(prev->right == NULL) {              // means we have to form thread
                    prev->right = cur;
                    cur = cur->left;                   // go into left subtree after forming thread
                }
                
                else {                     // means prev->right = cur -> rmeove the thread 
                    prev->right = NULL;     // remove thread
                    inorder.push_back(cur->val);    // add ROOT since Left portion processed and now ROOT as per LNR
                    cur = cur->right;         // after L, N go into right subtreee       
                }
            }
        }

        return inorder;
    }
};





// T.C -> O(N) (slghtly more since we compute rightmost node two times one at creating thread and other at deleting thread)
// S.C -> O(1) - advantage of morris