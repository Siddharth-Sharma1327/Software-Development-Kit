#include<bits/stdc++.h>
using namespace std;

class Node {
    public:
    int data;
    Node* next;

    public:
    Node(int data1, Node* next1){
        data = data1;
        next = next1;
    }

    public:
    Node(int data1){
        data = data1;
        next = nullptr;
    }
};

Node* convertArray2LL(vector<int> &arr){
    Node* head = new Node(arr[0]);
    Node* mover = head;
    for(int i=1; i<arr.size(); i++){
        Node * temp =  new Node(arr[i]);
        mover->next = temp;
        mover = mover->next;
    }
    return head;
}

int lengthOfLL(Node* head){
    Node* temp = head;
    int cnt=0;
    while(temp){
        cnt++;
        temp = temp->next;
    }
    return cnt;
}

bool checkIfPresent(Node* head, int val){
    Node* temp = head;
    while(temp){
        if(temp->data == val) return true;
        temp = temp->next;
    }
    return false;
}

int main(){
    vector<int> arr = {1,2,3,4,5,6};

    //array2LL
    Node* head = convertArray2LL(arr);
    cout<<head->data;

    //traverse
    Node* temp = head;
    while(temp){
        cout<<temp->data<<" ";
        temp = temp->next;
    }

    //length of LL
    cout<<lengthOfLL(head);

    // serach in LL
    cout<<checkIfPresent(head, 0)<<" "<<checkIfPresent(head, 2);

    
    return 0;
}