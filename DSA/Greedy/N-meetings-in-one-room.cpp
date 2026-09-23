#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Here the idea is that if we sort the meetings w.r.t their end time then after that counting meetings whose start pt is > prev counted meetings end pt... and doing this for whole array..and returning the final ans.

class Solution
{
    public:
    static bool comp(pair<int,int> a, pair<int,int> b){
        return a.second<b.second;
    }
    //Function to find the maximum number of meetings that can
    //be performed in a meeting room.
    int maxMeetings(int start[], int end[], int n)
    {
        // Your code here
        vector<pair<int, int>> v;
        for(int i=0;i<n;i++){
            v.push_back({start[i], end[i]});
        }
        
        sort(v.begin(), v.end(), comp);
        int cnt=1;
        int ep=v[0].second;
        for(int i=1;i<n;i++){
            if(v[i].first>ep){
                cnt++;
                ep=v[i].second;
            }
        }
        
        return cnt;
    }
};



int main(){
    return 0;
}