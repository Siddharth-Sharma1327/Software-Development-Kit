#include<iostream>
#include<bits/stdc++.h>
using namespace std;

vector<long long> printFirstNegativeInteger(long long int A[],
                                             long long int N, long long int K) {
                                                 
    
    vector<long long> ans;
    queue<long long int> q;
    
    int i=0,j=0;
    while(j<N){
        if(A[j]<0) q.push(j);
        
        if(j-i+1 < K){
            j++;
        }else{
            if(q.empty()) ans.push_back(0);
            else ans.push_back(A[q.front()]);
            if(!q.empty() && A[q.front()]==A[i]) q.pop();
            i++;
            j++;
        }
    }
    return ans;
    
}


vector<long long> printFirstNegativeInteger(long long int A[],
                                             long long int N, long long int K) {
                                                 
    
    vector<long long> ans;
    queue<long long int> q;
    
    int i=0,j=0;
    while(j<N){
        if(A[j]<0) q.push(j);
        
        if(j-i+1 < K){
            j++;
        }else{
            if(q.empty()) ans.push_back(0);
            else ans.push_back(A[q.front()]);
            if(!q.empty() && A[q.front()]==A[i]) q.pop();
            i++;
            j++;
        }
    }
    return ans;
    
 }



//  T.C -> O(N)
//  S.C -> O(K)


