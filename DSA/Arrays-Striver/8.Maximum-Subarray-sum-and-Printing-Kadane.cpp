#include<iostream>
#include<bits/stdc++.h>
using namespace std;




//Finding maximum subarray sum---
// (i) Brute force----

long long maxSubarraySum(vector<int> arr, int n)
{
    // Write your code here.
    long long ans=0;
    long long prefSum=0;
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            for(int k=i;k<=j;k++){

            }
        }
    }

    return ans;
}
// T.C -> O(N^3)
// S.C -> O(1)



// (ii) Better Soln--------

long long maxSubarraySum(vector<int> arr, int n)
{
    // Write your code here.
    long long ans=0;
    long long prefSum=0;
   for(int i=0;i<n;i++){
    int sum=0;
    for(int j=i;j<n;j++){
        sum+=arr[j];
        

    }
} 
    return ans;
}
// T.C -> O(N^2)
// S.C -> O(1)





// (iii) Optimal Soln------------Kadanes Alogo
long long maxSubarraySum(vector<int> arr, int n)
{
    // Write your code here.
    long long ans=0;
    long long prefSum=0;
    for(int i=0;i<n;i++){
        prefSum+=arr[i];
        if(prefSum<0) prefSum=0;
        ans=max(ans, prefSum);
    }
    return ans;
}
// T.C -> O(N)
// S.C -> O(1)




// Printing subarray with maximum sum using Kadanes Algorithm----------(IMP)
long long maxSubarraySum(vector<int> arr, int n)
{
    // Write your code here.
    long long ans=0;
    long long prefSum=0;
    int start=-1;          //3 pointers...start points to start of every new subarray..and startAns & endAns points to previous subarray with maximum sum...
    int startAns=-1;
    int endAns=-1;

    for(int i=0;i<n;i++){
        if(prefSum==0) start=i;
        prefSum+=arr[i];
        if(prefSum<0){
            prefSum=0;
        } 
        // ans=max(ans, prefSum);
        if(prefSum > ans){
            ans = prefSum;
            startAns=start;
            endAns=i;
        }
    }
    cout<<startAns<<" "<<endAns;
    return ans;
}

// T.C -> O(N)
// S.C -> O(1)
int main(){
    return 0;
}