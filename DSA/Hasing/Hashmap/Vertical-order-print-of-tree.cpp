#include<iostream>
#include<bits/stdc++.h>
using namespace std;


struct Node{
    int data;
    Node *left, *right;

    Node(int val){
        data=val;
        left = NULL;
        right = NULL;
    }
};

void getverticalOrder(Node *root, int hdis, map<int, vector<int>> &mp){
    if(root==NULL){
        return;
    }

    mp[hdis].push_back(root->data);
    getverticalOrder(root->left, hdis-1, mp);
    getverticalOrder(root->right, hdis+1, mp);

}

int main(){
    Node *root= new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left= new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    root->right->left->right = new Node(8);
    root->right->right->right= new Node(9);

    int hdis=0;
    map<int , vector<int>> mp;
    getverticalOrder(root, hdis, mp);

    map<int,vector<int>> :: iterator it;
    for(it=mp.begin(); it!=mp.end(); it++){
        for(int i=0;i<(it->second).size();i++){
            cout<<(it->second)[i]<<" ";
        }
        cout<<endl;
    }
    return 0;
}