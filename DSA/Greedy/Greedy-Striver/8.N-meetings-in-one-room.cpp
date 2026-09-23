#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// Brute force --- Recursion
// T.C -> O(2^N)
// S.C -> O(N)



// Better -----(Memoisation - Tabulation)
// T.C -> O(N^2)
// S.C -> O(N)




// Optimsed ----- (Greedy)
class Solution
{
    public:

    struct Data{
        int s;
        int e;
        int pos;      // this is stored if asked to print the jobs which were scheduled
    };
    
    static bool comp(Data a, Data b){
        return (a.e < b.e);
    }
    
    int maxMeetings(int start[], int end[], int n)
    {
        // Your code here
        vector<Data> meetings;
        for(int i = 0; i < n; i++){
            Data d;
            d.s = start[i];
            d.e = end[i];
            d.pos = i;
            meetings.push_back(d);
        }
        sort(meetings.begin(), meetings.end(), comp);
        vector<int> meetOrder;
        int prev = 0;
        
        int cnt = 1;
        for(int i = 1; i < n; i++){
            
            if( meetings[i].s > meetings[prev].e){
                cnt++;
                prev = i;
                meetOrder.push_back(meetings[i].pos);
            }
        }
        
        return cnt;
    }
};

// T.C -> O(N*LogN) + O(N)
// S.C -> O(N)


int main(){
    return 0;
}