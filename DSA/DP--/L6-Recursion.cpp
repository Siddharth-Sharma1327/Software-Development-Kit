#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void printF(int ind, vector<int> &ds, int arr[], int n){

    if(ind==n){
        for(auto it: ds){
            cout<<it<<" ";
        }
        if(ds.size()==0){
            cout<<"{}";
        }
        cout<<endl;
        return;
    }

    //not pick, or not take condition, this element is not added to your susequence
    printF(ind+1,ds, arr, n);

    //take or pick the particular index into the subsequence
    ds.push_back(arr[ind]);
    printF(ind+1, ds, arr, n);
    ds.pop_back();
}

int main(){

    int arr[]= {3, 1, 2};
    int n = 3;
    vector<int> ds;
    printF(0, ds, arr, n);
    return 0;
}


//Time complexity---> 2^n X O(N)  (2^n take non take combinations and for loop for every sequence)
//Space Complexity---> O(N)  (for the recursion arrray)