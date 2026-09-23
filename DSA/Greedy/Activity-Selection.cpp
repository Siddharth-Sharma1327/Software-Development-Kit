#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Same problem with N meetings
class Solution
{
    public:
    static bool comp(pair<int, int> a, pair<int, int> b){
        return a.second<b.second;
    }
    //Function to find the maximum number of activities that can
    //be performed by a single person.
    int activitySelection(vector<int> start, vector<int> end, int n)
    {
        // Your code here
        vector<pair<int,int>> v;
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