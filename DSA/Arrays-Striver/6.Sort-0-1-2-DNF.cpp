#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Brute force --- Using two loop
// T.C -> O(N^2)
// S.C -> O(1)


// (ii) Better Soln
void sortArray(vector<int>& arr, int n)
{
    // Write your code here
    int cnt0=0;
    int cnt1=0;
    int cnt2=0;
    for(int i=0;i<n;i++){
        if(arr[i]==0) cnt0++;
        if(arr[i]==1) cnt1++;
        if(arr[i]==2) cnt2++;
    }
    for(int i=0;i<n;i++){
        if(cnt0!=0){
            arr[i]=0;
            cnt0--;
        }else if(cnt1!=0){
            arr[i]=1;
            cnt1--;
        }else if(cnt2!=0){
            arr[i]=2;
            cnt2--;
        }
    }
    return;
}
// T.C -> O(2N)
// S.C -> O(1)


// (iii) Optimal Soln----DNF-Sort
void sortArray(vector<int>& arr, int n)
{
    // Write your code here
    int low=0;
    int mid=0;
    int high=n-1;

    while(mid<=high){
        if(arr[mid]==0){
            swap(arr[low], arr[mid]);
            low++;
            mid++;
        }else if(arr[mid]==1){
            mid++;
        }else if(arr[mid]==2){
            swap(arr[mid], arr[high]);
            high--;
        }
    }
    return;
}
// T.C -> O(N)
// S.C -> O(1)


int main(){
    return 0;
}