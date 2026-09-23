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

Node* deleteHead(Node* head){
    if(head == nullptr) return head;
    Node* temp = head;
    head = head->next;
    delete temp;
    return head;
}

Node* deleteTail(Node* head){
    if(head == nullptr || head->next == nullptr) return head;
    Node* temp = head;
    while(temp->next->next != nullptr){
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
    
    return head;
}

Node* deletekthNode(Node* head, int k){
    if(head == nullptr || k == 0) return head;

    if(k == 1){
        Node* temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    int cnt = 0;
    Node *temp = head, *prev = NULL;
    while(temp != nullptr){
        cnt++;
        if(cnt == k){
            prev->next = prev->next->next;
            delete temp;
            break;
        }
        prev = temp;
        temp = temp->next;
    }
    return head;

}
// deleteNodeWithVal -. same as above;


Node* inserAtHead(Node* head, int val){
    Node* temp = new Node(val, head);
    return temp;
}

Node* insertAtLast(Node* head, int val){
    if( head == NULL) return new Node(val);

    Node* temp = head;
    while(temp->next != nullptr){
        temp = temp->next;
    }
    Node *temp2 = new Node(val);
    temp->next = temp2;
    return head;
}

Node* insertAtkthPosition(Node* head, int ele, int k){
    if(head == NULL){
        if(k==1) return new Node(ele);
        else return head;
    }

    if(k == 1){
        return new Node(ele, head);
    }

    int cnt = 0;
    Node* temp = head;
    while(temp){
        cnt++;
        if(cnt == k-1){
            Node* newNode = new Node(ele);
            newNode->next = temp->next;
            temp->next = newNode;
            break;
        }
    }
    return head;
}

Node* insertBeforeValue(Node* head, int ele, int val){
    if(head == NULL){
       return NULL;
    }

    if(head->data == val){
        return new Node(ele, head);
    }

    Node* temp = head;
    while(temp->next != NULL){
        if(temp->next->data == val){
            Node* newNode = new Node(ele);
            newNode->next = temp->next;
            temp->next = newNode;
            break;
        }
    }
    return head;
}

int main(){
    return 0;
}