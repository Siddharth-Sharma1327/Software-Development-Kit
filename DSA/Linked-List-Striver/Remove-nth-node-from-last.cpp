#include<iostream>
#include<bits/stdc++.h>
using namespace std;

struct ListNode {
      int val;
      ListNode *next;
    //   ListNode() : val(0), next(nullptr) {}
    //   ListNode(int x) : val(x), next(nullptr) {}
    //   ListNode(int x, ListNode *next) : val(x), next(next) {}
};



// Brute force----two pass
// find total elements of LL
// then delete N-n node from start


// Optimised  Approach--->One Pass

//1) Recursion
class Solution {
public:
    int cnt=0;
    
    ListNode* removeNthFromEnd(ListNode* head, int n) {
      
        if(head==NULL) return NULL;
        
        head->next = removeNthFromEnd(head->next, n);
        
        cnt++;
        if(cnt==n){
            return head->next;
        }
        
        return head;
        
    }
};

// 2)Two pointers
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
      
        
        ListNode* fast=head, *slow=head;
        
        for(int i=0;i<n;i++){
            fast = fast->next;
        }
        if(fast==NULL) return head->next;
            
        while(fast->next!=NULL){
            slow = slow->next;
            fast = fast->next;
        }
        
        ListNode* dummy=slow->next;
        slow->next = slow->next->next;
        delete dummy;
        return head;
        
    }
};

int main(){
    return 0;
}