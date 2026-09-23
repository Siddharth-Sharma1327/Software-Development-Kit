#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void printS(int ind, vector<int> &ds, int s, int sum, int arr[], int n){

    if(ind==n){
        if(s==sum){
            for(auto it: ds){
                cout<<it<<" ";
            }cout<<endl;
        }
        return;
    }

    ds.push_back(arr[ind]);
    s+=arr[ind];

    printS(ind+1, ds, s, sum, arr, n);

    s-=arr[ind];
    ds.pop_back();

    //not pick
    printS(ind+1, ds, s, sum, arr, n);
}




//Print any One subsequence with sum 'sum'
bool print1S(int ind, vector<int> &ds, int s, int sum, int arr[], int n){

    if(ind==n){
        if(s==sum){
            for(auto it: ds){
                cout<<it<<" ";
            }cout<<endl;
            return true;
        }
        //condition not satisfied
        else return false;
    }

    ds.push_back(arr[ind]);
    s+=arr[ind];

    if(print1S(ind+1, ds, s, sum, arr, n)==true){
        return true;
    } 

    s-=arr[ind];
    ds.pop_back();

    //not pick
    if(print1S(ind+1, ds, s, sum, arr, n)==true){
        return true;
    }

    return false;
}



//Count the subsequences with sum k
int print2S(int ind, int s, int sum, int arr[], int n){

    if(s > sum) return 0;   //saving additional calls
    if(ind==n){
        if(s==sum){
            return 1;
        }
        //condition not satisfied
        else return 0;
    }

    
    s+=arr[ind];

    int l = print2S(ind+1, s, sum, arr, n);
    s-=arr[ind];

    //not pick
    int r = print2S(ind+1, s, sum, arr, n);

    return l + r;
}
int main(){
    int arr[] = {1, 2, 1};
    int n = 3;
    int sum = 2;
    vector<int> ds;
    printS(0, ds, 0, sum, arr, n);
    print1S(0, ds, 0, sum, arr, n);
    cout<<print2S(0, 0, sum, arr, n);
    return 0;
}