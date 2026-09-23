#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// APPROACH -> WE ARE SYROING INDICES OPOF ELEMENTS OF CURRENT WINDOW AND HAVING THE MAX ELEMENT IN FRONT OF THE DEQUE
// 

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        deque<int> dq;
        vector<int> ans;
        
        for(int i=0;i<n;i++){
            
            if(!dq.empty() && dq.front()<= i-k) dq.pop_front();      // IF WE GET FRONT ELEMENT OUTSIDE THE BOUNDARY OF CURRENT WINDOW WE WILL POP IT..
                                                                    // ...AT FIRST WINDOW CODE DOESN'T GO INSIDE THIS IF CONDITION SO NONE IS POPED
            
            while(!dq.empty() && nums[dq.back()]<= nums[i]){        // NOW WE WILL POP ALL ELMENTS FROM BACK WHICH ARE LESSER THAT THE CURRENT ELEMENT SO THAT MAX IS STORED AT FRONT
                dq.pop_back();
            }
            dq.push_back(i);                                        // NOW CURRENT ELEMENT IS PUSHED INTO THE DEQUE
            if(i>=k-1) ans.push_back(nums[dq.front()]);             // NOW MAX ELMENT FRO CURRENT WINDOW IS STORED...AND (i>=k-1) IS USED SO NOT PUSH FOR THE FILLING OF FIRST WINDOW
        }
        
        return ans;
    }
};
// T.C -> O(N) + O(N){
    /*
    Overall T.C -> 
        O(1) + O(k) + O(1) + O(k) + O(1) +....+ O(K) + O(1) + O(k)
        = O(N) + O(K) + O(K) + O(K)... + O(K)
        = O(N) + O(k + K+ K+ K...+k)
        = O(N) + O(N)------->k+k+k+k...+k=N(all elments)
    */
// }
// S.C -> O(K)....max size of deque + O(N)...for ans vector

int main(){
    return 0;
}
