#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Same idea as that of N meetings problem just here we have to store the index of meetings

class Solution{
public:
    static bool comp(pair<int, pair<int,int>> a, pair<int, pair<int,int>> b){
        return a.second.first<b.second.first;
    }
    vector<int> maxMeetings(int N,vector<int> &S,vector<int> &F){
        
        vector<int> ans;
        vector<pair<int, pair<int,int>>> v;
        for(int i=0;i<N;i++){
            v.push_back({S[i], {F[i], i+1}});
        }
        
        sort(v.begin(), v.end(), comp);
        ans.push_back(v[0].second.second);
        int cnt=1;
        int ep=v[0].second.first;
        for(int i=1;i<N;i++){
            if(v[i].first>ep){
                ans.push_back(v[i].second.second);
                cnt++;
                ep=v[i].second.first;
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};

int main(){
    return 0;
}