#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// Optimised Approach------------
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int cnt=0;
        int n = g.size();
        int m = s.size();
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        
        int i=0, j=0;
        
        while(i<n && j<m){
            if(s[j]>=g[i]){
                cnt++;
                i++;
                j++;
            }else{
                j++;
            }
        }
        return cnt;
    }
};
// T.C -> O(N*LogN)
// S.C -> O(LogN)  -- {The space complexity of the sort() function in C++ is O(log N) in the average and best cases, and O(N) in the worst case.
//                     The sort() function uses a hybrid sorting algorithm called Introsort, which is a combination of quicksort, heapsort, and 
//                     insertion sort. Introsort is designed to be efficient in both time and space, and it typically has a space complexity of O(log N). 
//                     However, in the worst case, Introsort can degenerate to quicksort, which has a space complexity of O(N).}

int main(){
    return 0;
}