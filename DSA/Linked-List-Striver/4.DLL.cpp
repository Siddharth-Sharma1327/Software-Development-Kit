    #include<bits/stdc++.h>
    using namespace std;

    class Node {
        public:
        int data;
        Node* next;
        Node* prev;

        public:
        Node(int data1, Node* next1, Node* prev1){
            data = data1;
            next = next1;
            prev = prev1;
        }

        public:
        Node(int data1){
            data = data1;
            next = nullptr;
            prev = nullptr;
        }
    };

    Node* convertArr2DLL(vector<int> &arr){
        Node* head = new Node(arr[0]);
        Node* prev = head;
        for(int i=1; i<arr.size(); i++){
            Node* temp = new Node(arr[i], nullptr, prev);
            prev->next = temp;
            prev = temp;
        }
        return head;
    }

    void print(Node* head){
        while(head){
            cout<<head->data<<" ";
            head = head->next;
        }
        return;
    }

    Node* deleteHeadOfDLL(Node* head){
        if(head == NULL || head->next == NULL) return NULL;
        Node* temp = head;
        head = head->next;
        head->prev = NULL;
        temp->next = NULL;
        delete temp;
        return head;
    }

    Node* deleteTailOfDLL(Node* head){
        if(head == NULL || head->next == NULL) return NULL;
        Node* temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        Node* temp2 = temp->prev;
        temp2->next = NULL;
        temp->prev =  NULL;
        delete temp;
        return head;
    }

    Node* deletekthElementOfDLL(Node* head, int k){
        if(head == NULL) return NULL;
        int cnt = 0;
        Node* temp = head;
        while(temp){
            cnt++;
            if(cnt == k) break;
            temp = temp->next;   
        }
        Node* temp2 = temp->prev;
        Node* front = temp->next;

        // single element dll
        if(temp2 == NULL && front == NULL){
            delete temp;
            return NULL;
        }
        else if(temp2 == NULL){ // head of dll
            return deleteHeadOfDLL(head);
        }
        else if(front == NULL){ // tail of dll
            return deleteTailOfDLL(head);
        }
        else{
            temp2->next = front;
            front->prev = temp2;
            temp->next = NULL;
            temp-> prev = NULL;
            delete temp;
        }
        return head;
    }

    // below func just deletes node and not return head or anything
    Node* deleteNode(Node* temp){
        Node* temp2 = temp->prev;
        Node* front = temp->next;

        //tail
        if(front == NULL){
            temp2->next = NULL;
            temp->prev = NULL;
            delete temp;
        }
        //node somewhere in between
        temp2->next = front;
        front->prev = temp2;
        temp->next = NULL;
        temp->prev = NULL;
        delete temp;
    }


    Node* insertBeforeHeadOfDLL(Node* head, int ele){
        Node* temp = new Node(ele, head, nullptr);
        head->prev = temp;
        return temp;
    }

    Node* insertBeforeTailOfDLL(Node* head, int ele){

        if(head->next ==  NULL){
            return insertBeforeHeadOfDLL(head, ele);
        }

        Node* temp = head;
        while(temp->next){
            temp = temp->next;
        }
        Node* back = temp->prev;
        Node* temp2 = new Node(ele, temp, back);
        back->next = temp2;
        temp->prev = temp2;
        return head;
    }

    Node* insertBeforekthNodeOfDLL(Node* head, int ele, int k){
        if(k == 1) return insertBeforeHeadOfDLL(head, ele);
        Node* temp = head;
        int cnt=0;
        while(temp->next){
            cnt++;
            if(cnt == k) break;
        temp = temp->next;
        }
        Node* back = temp->prev;
        Node* newNode = new Node(ele, temp, back);
        back->next = newNode;
        temp->prev = newNode;
        return head;


    }

    void insertBeforeNode(Node* temp, int ele){
        Node* back = temp->prev;
        Node* newNode = new Node(ele, temp, back);
        back->next = newNode;
        temp->prev = newNode;
    }
    int main(){
        vector<int> arr = {1,2,3,4,5,6};
        Node* head = convertArr2DLL(arr);
        deleteHeadOfDLL(head);
        print(head);
        deleteTailOfDLL(head);
        print(head);
        return 0;
    }
