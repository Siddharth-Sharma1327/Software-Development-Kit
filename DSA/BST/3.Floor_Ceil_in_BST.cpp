Ceil :-
class Solution {
  public:
    int findCeil(Node* root, int key) {
        // code here
        int ceil = -1;
        while(root){
            
            if(root->data == key){
                ceil  = root->data;
                return ceil;
            }
            
            if(key > root->data){
                root = root->right;
            }
            
            else {
                ceil = root->data;
                root = root->left;
            }
        }
        return ceil;
    }
};


// check left or right proper for floor or ceil
// T.C -> O(log n)
// S.C -> O(1)