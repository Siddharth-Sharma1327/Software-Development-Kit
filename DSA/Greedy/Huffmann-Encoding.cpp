#include<iostream> 
#include<bits/stdc++.h>
using namespace std;

// IMP Question-------------same idea of min heap of min. cost of ropes question is used...Node* are created for every data then filled into the min heap after that combined the top 2 roots of the min heap as left and right of the new root node as their root node with data = sum of left's data and right's data...tree generated after that simple preorder traversal is done

class Node{
    public:
        int data;
        Node* left;
        Node* right;
        
        Node(int val){
            data = val;
            left = NULL;
            right = NULL;
        }
};


class comp{                                                      //IMP Method to create comp for the min heap on the basis of  the node's data values..
    public:
        bool operator()(Node* a, Node* b){
        return a->data > b->data;
        }
};

class Solution
{
	public:
	
	
	void preorder(Node* root, string s, vector<string> &ans){
	    
	    if(root->left==NULL && root->right==NULL){
	        ans.push_back(s);
	        return;
	    }
	    
	    string x=s, y=s;
	    x+='0';
	    y+='1';
	    preorder(root->left, x, ans);
	    preorder(root->right, y, ans);
	    
	}
	
	
		vector<string> huffmanCodes(string S,vector<int> f,int N)
		{
		    // Code here
		    priority_queue<Node*, vector<Node*>, comp> minheap;
		    for(int i=0;i<N;i++){
		        Node* temp = new Node(f[i]);
		        minheap.push(temp);
		    }
		    
		    while(minheap.size()>1){
		        Node* left = minheap.top();
		        minheap.pop();
		        
		        Node* right = minheap.top();
		        minheap.pop();
		        
		        Node* newNode = new Node(left->data + right->data);
		        newNode->left = left;
		        newNode->right = right;
		        minheap.push(newNode);
		        
		    }
		    
		    Node* root = minheap.top();
		    minheap.pop();
		    vector<string> ans;
		    preorder(root,"", ans);
		    return ans;
		}
		
};


int main(){
    return 0;
}