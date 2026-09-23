#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class Solution{   
public:
    long maximumSumSubarray(int K, vector<int> &Arr , int N){
        // code here 
        long sum=0;
        long ans=INT_MIN;
        
        int i=0,j=0;
        while(j<N){
            sum+=Arr[j];
            if(j-i+1 < K){
                j++;
            }else{
               ans=max(ans, sum);
               sum-=Arr[i];
               i++;
               j++;
            }
        }
        return ans;
    }
};

//{ Driver Code Starts.
int main() 
{ 
    int t;
    cin>>t;
    while(t--)
    {
        int N,K;
        cin >> N >> K;;
        vector<int>Arr;
        for(int i=0;i<N;++i){
            int x;
            cin>>x;
            Arr.push_back(x);
        }
        Solution ob;
        cout << ob.maximumSumSubarray(K,Arr,N) << endl;
    }
    return 0; 
} 


// T.C -> O(N)
// S.C -> O(1)
