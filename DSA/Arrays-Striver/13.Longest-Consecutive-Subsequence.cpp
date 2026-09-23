#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// (i) Brute force-------

bool ls(vector<int> &a, int num){
    for(int i=0;i<a.size();i++){
        if(a[i]==num) return true;
    }
    return false;
}

int longestSuccessiveElements(vector<int>&a) {
    // Write your code here.
    int n = a.size();
    int longest=1;
    for(int i=0;i<n;i++){
        int x = a[i];
        int cnt = 1;
        while(ls(a, x+1)==true){
            x = x+1;
            cnt++;
        }
        longest = max(longest, cnt);
    }
    return longest;
}
// T.C -> O(N*N*N)
// S.C -> O(1)



// (ii) Better Soln-----------

int longestSuccessiveElements(vector<int>&a) {
    // Write your code here.
    int n = a.size();
    sort(a.begin(), a.end());

    int cntCurr=0;
    int lastSmaller=INT_MIN;
    int longest=1;

    for(int i=0;i<n;i++){
        if(a[i] - 1 == lastSmaller){
            cntCurr++;
            lastSmaller=a[i];
        }else if(a[i]==lastSmaller){
            // do nothing
        }else if(a[i]!=lastSmaller){
            cntCurr=1;
            lastSmaller=a[i];
        }

        longest = max(longest, cntCurr);
    }
    return longest;
   
}
// T.C -> O(NLogN) + O(N)
// S.C -> O(1);


// (iii) Optimal soln-------------(ONLY IF WE INGONRE THE WORST CASE OF UNORDERED_SET-->O(N))
int longestSuccessiveElements(vector<int>&a) {
    // Write your code here.
    int n = a.size();
    if(n==0) return 0;
    int longest=1;
    unordered_set<int> st;

    //O(N)
    for(int i=0;i<n;i++){
        st.insert(a[i]);
    }


    //O(2N) & not O(N*N) as we are not iterating through all elements of set for every element just do dry run
    for(auto it: st){

        if(st.find(it - 1) == st.end()){
            int cnt=1;
            int x=it;

            while(st.find(x+1) != st.end()){
                x = x+1;
                cnt++;
            }

            longest = max(longest, cnt);
        }
    }

    return longest;
   
}
// T.C -> O(N) + O(2N)   (ONLY IF WORST CASE OF UNORDERED_SET NOT CONSIDERED O/W T.C -> O(N^N) then previous soln is optimal)
// S.C -> O(N)
// EVEN IF WE USE ORDERED SET WE WILL HAVE T.C -> O(NLogN) & S.C -> O(N)
// ....so previous soln is optimal as it uses same t.c but s.c is o(1)
int main(){
    return 0;
}