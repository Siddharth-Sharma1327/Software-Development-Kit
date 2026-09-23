template <typename T>
class Node{
    public:
    T data;
    Node<T> *next;

    Node(){
        this->data = 0;
        this->next = NULL;
    }

    Node(T data){
        this->data = data;
        this->next = NULL;
    }

    Node(T data, T* next){
        this->data = data;
        this->next = next;
    }
};

// specify like this :-
// Node<int> *temp = head;
// Node<string> *temp = head;