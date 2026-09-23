#include<bits/stdc++.h>
using namespace std;

// Queue using arrays
class Queue {
    private:
        int size = 10;
        int curSize = 0;
        int start = -1, end  = -1;
        int arr[size];

    public:
        void push(int x) {
            if(curSize == size) cout<<"queue is full";
            if(curSize == 0){
                start = 0;
                end = 0;
            }else{
                end = (end + 1) % size;
                arr[end] = x;
                curSize++;
            }
        }

        int pop() {
            if(cursize == 0) cout<<"queue is emptyt to pop";
            int ele = arr[start];
            if(curSize == 1){
                start = -1;
                end = -1;
            }else{
                start = (start + 1) % size;
            }
            curSize--;
            return ele;
        }

        int top() {
            if(curSize == 0) cout<<"queue is empty to top";
            return arr[start];
        }

        int size() {
            return curSize;
        }
};